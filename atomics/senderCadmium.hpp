/**
* Cristina Ruiz Martin
* ARSLab - Carleton University
*/

#ifndef BOOST_SIMULATION_PDEVS_SENDER_HPP
#define BOOST_SIMULATION_PDEVS_SENDER_HPP

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include <limits>
#include <math.h> 
#include <assert.h>
#include <memory>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <limits>
#include <random>

#include "../data_structures/message.hpp"

using namespace cadmium;
using namespace std;

//Port definition
    struct Sender_defs{
        struct packetSentOut : public out_port<Message_t> {
        };
        struct ackReceivedOut : public out_port<Message_t> {
        };
        struct dataOut : public out_port<Message_t> {
        };
        struct controlIn : public in_port<Message_t> {
        };
        struct ackIn : public in_port<Message_t> {
        };
    };

    template<typename TIME>
    class Sender{
        using defs=Sender_defs; // putting definitions in context
        public:
            //Parameters to be overwriten when instantiating the atomic model
            TIME   preparationTime;
            TIME   timeout;
            // default constructor
            Sender() noexcept{
              preparationTime  = TIME("00:00:10");
              timeout          = TIME("00:00:20");
              state.alt_bit    = 0;
              state.next_internal    = std::numeric_limits<TIME>::infinity();
              state.model_active     = false;
            }
            
            // state definition
            struct state_type{
              bool ack;
              int packetNum;
              int totalPacketNum;
              int alt_bit;
              bool sending;
              bool model_active;
              TIME next_internal;
            }; 
            state_type state;
            // ports definition
            using input_ports=std::tuple<typename defs::controlIn, typename defs::ackIn>;
            using output_ports=std::tuple<typename defs::packetSentOut, typename defs::ackReceivedOut, typename defs::dataOut>;

            // internal transition
            void internal_transition() {
              if (state.ack){
                if (state.packetNum < state.totalPacketNum){
                  state.packetNum ++;
                  state.ack = false;
                  state.alt_bit = (state.alt_bit + 1) % 2;
                  state.sending = true;
                  state.model_active = true; 
                  state.next_internal = preparationTime;   
                } else {
                  state.model_active = false;
                  state.next_internal = std::numeric_limits<TIME>::infinity();
                }
              } else{
                if (state.sending){
                  state.sending = false;
                  state.model_active = true;
                  state.next_internal = timeout;
                } else {
                  state.sending = true;
                  state.model_active = true;
                  state.next_internal = preparationTime;    
                } 
              }   
            }

            // external transition
            void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) { 
              if((get_messages<typename defs::controlIn>(mbs).size()+get_messages<typename defs::ackIn>(mbs).size())>1) assert(false && "one message per time uniti");
              for(const auto &x : get_messages<typename defs::controlIn>(mbs)){
                if(state.model_active == false){
                  state.totalPacketNum = static_cast < int > (x.value);
                  if (state.totalPacketNum > 0){
                    state.packetNum = 1;
                    state.ack = false;
                    state.sending = true;
                    state.alt_bit = state.packetNum % 2;  //set initial alt_bit
                    state.model_active = true;
                    state.next_internal = preparationTime;
                  }else{
                    if(state.next_internal != std::numeric_limits<TIME>::infinity()){
                      state.next_internal = state.next_internal - e;
                    }
                  }
                }
              }
              for(const auto &x : get_messages<typename defs::ackIn>(mbs)){
                if(state.model_active == true) { 
                  if (state.alt_bit == static_cast < int > (x.value)) {
                    state.ack = true;
                    state.sending = false;
                    state.next_internal = TIME("00:00:00");
                  }else{
                    if(state.next_internal != std::numeric_limits<TIME>::infinity()){
                      state.next_internal = state.next_internal - e;
                    }
                  }
                }
              }  
                           
            }

            // confluence transition
            void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
                internal_transition();
                external_transition(TIME(), std::move(mbs));
            }

            // output function
            typename make_message_bags<output_ports>::type output() const {
              typename make_message_bags<output_ports>::type bags;
              Message_t out;
              if (state.sending){
                out.value = state.packetNum * 10 + state.alt_bit;
                get_messages<typename defs::dataOut>(bags).push_back(out);
                out.value = state.packetNum;
                get_messages<typename defs::packetSentOut>(bags).push_back(out);
              }else{
                if (state.ack){
                  out.value = state.alt_bit;
                  get_messages<typename defs::ackReceivedOut>(bags).push_back(out);
                }
              }   
              return bags;

            }

            // time_advance function
            TIME time_advance() const {  
              return state.next_internal;
            }

            friend std::ostringstream& operator<<(std::ostringstream& os, const typename Sender<TIME>::state_type& i) {
                os << "packetNum: " << i.packetNum << " & totalPacketNum: " << i.totalPacketNum; 
            return os;
            }
        };     


#endif // BOOST_SIMULATION_PDEVS_SENDER_HPP
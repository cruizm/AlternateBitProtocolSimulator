/**
* Cristina Ruiz Martin
* ARSLab - Carleton University
*/

#ifndef _BOOST_SIMULATION_PDEVS_SENDER_HPP_
#define _BOOST_SIMULATION_PDEVS_SENDER_HPP_

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

#include "../include/data_structures/message.hpp"

using namespace cadmium;
using namespace std;

//Port definition
struct sender_defs{
    struct packetSentOut : public out_port<message_t> {};
    struct ackReceivedOut : public out_port<message_t> {};
    struct dataOut : public out_port<message_t> {};
    struct controlIn : public in_port<message_t> {};
    struct ackIn : public in_port<message_t> {};
};

template<typename TIME>
class Sender{
    using defs = sender_defs; // putting definitions in context
    public:
        //Parameters to be overwriten when instantiating the atomic model
        TIME   PREPARATION_TIME;
        TIME   timeout;
        // default constructor
        Sender() noexcept{
            PREPARATION_TIME  = TIME("00:00:10");
            timeout           = TIME("00:00:20");
            state.alt_bit     = 0;
            state.next_internal    = std::numeric_limits<TIME>::infinity();
            state.model_active     = false;
        }
        
        // state definition
        struct state_type{
            bool ack;
            int packet_num;
            int total_packet_num;
            int alt_bit;
            bool sending;
            bool model_active;
            TIME next_internal;
        }; 
        state_type state;
        // ports definition
        using input_ports=std::tuple<typename defs::controlIn,
                                     typename defs::ackIn>;
        using output_ports=std::tuple<typename defs::packetSentOut,
                                      typename defs::ackReceivedOut,
                                      typename defs::dataOut>;

        // internal transition
        void internal_transition() {
            if (state.ack){
                if (state.packet_num < state.total_packet_num){
                    state.packet_num ++;
                    state.ack = false;
                    state.alt_bit = (state.alt_bit + 1) % 2;
                    state.sending = true;
                    state.model_active = true; 
                    state.next_internal = PREPARATION_TIME;   
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
                    state.next_internal = PREPARATION_TIME;    
                } 
            }   
        }

        // external transition
        void external_transition(TIME e, 
                                 typename make_message_bags<input_ports>::type mbs) { 
          
            if((get_messages<typename defs::controlIn>(mbs).size()+
                get_messages<typename defs::ackIn>(mbs).size())>1){
                assert(false && "one message per time uniti");
            }

            for(const auto &x : get_messages<typename defs::controlIn>(mbs)){
                if(state.model_active == false){
                    state.total_packet_num = static_cast < int > (x.value);
                    if (state.total_packet_num > 0){
                        state.packet_num = 1;
                        state.ack = false;
                        state.sending = true;
                        state.alt_bit = state.packet_num % 2;  //set initial alt_bit
                        state.model_active = true;
                        state.next_internal = PREPARATION_TIME;
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
        void confluence_transition(TIME e, 
                                   typename make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(TIME(), std::move(mbs));
        }

        // output function
        typename make_message_bags<output_ports>::type output() const {
            typename make_message_bags<output_ports>::type bags;
            message_t out;
            if (state.sending){
                out.value = state.packet_num * 10 + state.alt_bit;
                get_messages<typename defs::dataOut>(bags).push_back(out);
                out.value = state.packet_num;
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

        friend std::ostringstream& operator<<(std::ostringstream& os, 
                                              const typename Sender<TIME>::state_type& i) {
            os << "packet_num: " << i.packet_num << " & total_packet_num: " << i.total_packet_num; 
            return os;
        }
    };     


#endif // _BOOST_SIMULATION_PDEVS_SENDER_HPP_
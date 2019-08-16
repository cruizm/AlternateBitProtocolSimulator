/** \brief Subnet Class is implemented in this header file
 * 
 * The subnet after receiving the message packets sends them after
 * some delay. The probability of subnet is set to 95%, it means that
 * there is a 5% chance of packet loss.
 * 
 * It has two phases namely, active state and passive state.
 * When the subnet's status is idle, it is in a passive state. 
 * The status changes to the active state, when it receives the packet, and 
 * reverts the status to the passive state when no data is being send or acknowledged
 */
/**
* Cristina Ruiz Martin
* ARSLab - Carleton University
*
*/

#ifndef __SUBNET_CADMIUM_HPP__
#define __SUBNET_CADMIUM_HPP__

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


/**
 * @brief      Port Definition
 * Structure holds the input and output messages using the input and
 * output port.
 */
struct subnet_defs{
    struct out : public out_port<message_t> {};
    struct in : public in_port<message_t> {};
};

//This is a meta-model, it should be overloaded for declaring the "id" parameter
/**
 * @brief      Class for subnet.
 * The Subnet class receives message and transmits them out with some delay.
 */
template<typename TIME>
class Subnet{
    /** putting definitions in context */
    using defs = subnet_defs; 
    public:
        /**Parameters to be overwriten when instantiating the atomic model
        */

        /**
         * @brief      Constructor of Subnet Class
         * Initializes state structure of transmiting  to false
         * and index to zero
         */
        Subnet() noexcept{
            state.transmiting     = false;
            state.index           = 0;
        }

        /**
         * Structure that holds the
         * state type variables for transmitting
         */
        struct state_type{
            bool transmiting;
            int packet;
            int index;
        }; 
        state_type state;
        
        /** Intitialized the input and output porst */
        using input_ports=std::tuple<typename defs::in>;
        using output_ports=std::tuple<typename defs::out>;

        /**
         * Function that performs the internal transition for the Subnet
         * It takes no input as parameter and resets the subnet transmitting state.
        */
        void internal_transition() {
            state.transmiting = false;  
        }
        
        /**
         * @brief      External Transition Function
         * Function fetches the message and checks if the number of messages 
         * is more than 1, then asserts by sending the stated message and 
         * changes the state to false. It then sets the message value to the packet that is
         * going to be send and sets the transmitting state to true.
         * @param[in]  e     type time variable
         * @param[in]  mbs   message bags
         */
        void external_transition(TIME e, 
                                 typename make_message_bags<input_ports>::type mbs) { 
            state.index ++;
            if(get_messages<typename defs::in>(mbs).size()>1){
                assert(false && "One message at a time");
            }                
            for (const auto &x : get_messages<typename defs::in>(mbs)) {
                state.packet = static_cast < int > (x.value);
                state.transmiting = true; 
            }               
        }

        
        /**
         * @brief      Confluence Transition
         * It initially calls the internal transtion function followed
         * by external transition
         * @param[in]  e     type time variable
         * @param[in]  mbs   message bags
         */
        void confluence_transition(TIME e, 
                                   typename make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(TIME(), std::move(mbs));
        }

        /**
         * @brief      Messge bag fucntion
         * Function that transmits the message to the output port
         * The funtion transmits with the probability of 95%. It
         * implies that the packet loss is 5%. 
         * @return     Message bags
         */
        typename make_message_bags<output_ports>::type output() const {
            typename make_message_bags<output_ports>::type bags;
            message_t out;
            if ((double)rand() / (double) RAND_MAX  < 0.95){
                out.value = state.packet;
                get_messages<typename defs::out>(bags).push_back(out);
            }
            return bags;
        }

        
        /**
         * @brief      Time Advance Function
         * Function sets the next internal transition time.
         * If the current sending state is  true then the next internal 
         * time is set to value generated by distribution function
         * that provides mean of 3.0 and standard deviation of 1.0, 
         * otherwise it is set to infinity.      
         * @return     next internal time
         */
        TIME time_advance() const {
            std::default_random_engine generator;
            std::normal_distribution<double> distribution(3.0, 1.0); 
            TIME next_internal;
            if (state.transmiting) {
                std::initializer_list<int> time = {0, 0, 
                                                   static_cast < int > (round(distribution(generator)))};
                /** Time is in hour min and second */
                next_internal = TIME(time);
            }else {
                next_internal = std::numeric_limits<TIME>::infinity();
            }    
            return next_internal;
        }

        /**
         * @brief      Friend function
         * Function that transmits the message to the ostring stream
         * @param os ostring stream
         * @param i state type
         * @return os ostring stream
         */ 
        friend std::ostringstream& operator<<(std::ostringstream& os, 
                                              const typename Subnet<TIME>::state_type& i) {
            os << "index: " << i.index << " & transmiting: " << i.transmiting; 
            return os;
        }
};    
#endif /** __SUBNET_CADMIUM_HPP__ */
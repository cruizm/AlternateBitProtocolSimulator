/** \brief Receiver Class is implemented in this header file.
 * 
 * The receiver implemented here receives message from the input port
 * and sends acknowldgement after fixed delay on output port.
 * 
 * It has two phases namely, active state and passive state.
 * When the receiver's status is idle, it is in a passive state. 
 * The status changes to the active state, when it receives the packet, and 
 * reverts the status to the passive state after sending an acknowledgment.
 * 
 */
/**
* Cristina Ruiz Martin
* ARSLab - Carleton University
*
*/

#ifndef __RECEIVER_CADMIUM_HPP__
#define __RECEIVER_CADMIUM_HPP__


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
 * Structure definition for Input and Output messages.     
 */
struct receiver_defs{
    struct out : public out_port<message_t> {};
    struct in : public in_port<message_t> {};
};
   
/**
 * @brief      Class for Receiver
 * The Receiver class receives message and answers with acknowledgement.
 */
template<typename TIME>
class Receiver{
    /** Putting definitions in context*/
    using defs = receiver_defs; 
    public:
        
        TIME PREPARATION_TIME; /**<Time delay constant holder from acknowledgement to output. */
                               /**< Time constant delay */
        /**
         * @brief      Constructs the object.
         * It it initializes the delay constant, sets the state acknowledgement
         * number and state's sending state to false.
         */
        Receiver() noexcept{
            PREPARATION_TIME  = TIME("00:00:10");
            state.ack_num      = 0;
            state.sending     = false;
        }
        
        /**
         * Structure state definition that holds acknowledge number and receiver state.
         */
        struct state_type{
            int ack_num;    /**< Alternating bit fetched from the message and acknowledgement number. */
                            /**< Acknowledgement number */
            bool sending;   /**< State of the receiver, passive(false) or active(true) */
                            /**< Sending State */
        }; 
        state_type state;

        /** ports definition*/
        using input_ports = std::tuple<typename defs::in>;
        using output_ports = std::tuple<typename defs::out>;

        /**
         * Internal Transition function that resets the state sending state.
         */
        void internal_transition() {
            state.sending = false; 
        }

        /**
         * @brief      Function handles exteral transition.
         * It fetches the message and checks if the number of messages 
         * is more than 1, then asserts by sending the stated message and 
         * changes the state to false. It then sets the acknowledge to the 
         * message value and sets the sending state to true.
         * @param[in]  e     type time variable
         * @param[in]  mbs   message bags
         */
        void external_transition(TIME e, 
                                 typename make_message_bags<input_ports>::type mbs){ 

            if(get_messages<typename defs::in>(mbs).size()>1){ 
                assert(false && "one message per time uniti");
            }
            for(const auto &x : get_messages<typename defs::in>(mbs)){
              state.ack_num = static_cast < int > (x.value);
              state.sending = true;
            }  
                       
        }

        /**
         * @brief      Confluence transition function
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
         * It is responsible for sending acknowledge number to the ouput
         * port. Which is the remainder, when the acknowledge number is divided
         * by 10.
         * @return     Message bags
         */
        typename make_message_bags<output_ports>::type output() const {
            typename make_message_bags<output_ports>::type bags;
            message_t out;              
            out.value = state.ack_num % 10;
            get_messages<typename defs::out>(bags).push_back(out);     
            return bags;
        }

        /**
         * @brief      Time Advance Function
         * Function sets the next internal transition time.
         * If the current state of sending is true, then the internatl
         * time is set to PREPARATION_TIME. Otherwise, it is set to infinity.
         * @return     Next internal time
         */
        TIME time_advance() const {  
            TIME next_internal;
            if (state.sending) {
                next_internal = PREPARATION_TIME;
            } else {
                next_internal = std::numeric_limits<TIME>::infinity();
            }    
            return next_internal;
        }
        /**
         * @brief      Friend function
         * Function outputs acknowledge number to ostring stream.
         * @param      os    the ostring stream
         * @param[in]  i     structure state_type
         *
         * @return     the ostring stream
         */
        friend std::ostringstream& operator<<(std::ostringstream& os,
                                              const typename Receiver<TIME>::state_type& i) {
            os << "ack_num: " << i.ack_num; 
            return os;
        }
};     
  

#endif /** __RECEIVER_CADMIUM_HPP__ */
/** \brief This header file implements the Receiver class.
*
* The receiver receives the message on input port
* and sends acknowledge after fixed delay on output port.
*
* The receiver has two phases: passive and active.
* It is in passive phase initially. When it receives
* a packet, it will go to active phase, send out
* the acknowledgement and will go to passive state again.
*
* Cristina Ruiz Martin
* ARSLab - Carleton University
*
*/

#ifndef __BOOST_SIMULATION_PDEVS_RECEIVER_HPP__
#define __BOOST_SIMULATION_PDEVS_RECEIVER_HPP__


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

/** 
* Structure that holds input and output messages.
*/
struct receiver_defs{
    struct out : public out_port<Message_t> {
    };
    struct in : public in_port<Message_t> {
    };
};

/** 
* The Receiver class receives message and sends out acknowledge.
*/   
template<typename TIME>
class Receiver{
    using defs=receiver_defs; // putting definitions in context
    public:
        //Parameters to be overwriten when instantiating the atomic model
        TIME   PREPARATION_TIME;
        
	/** 
	* Constructor for Receiver class.
	* Initializes the delay constant and state structure.
	*/
        Receiver() noexcept{
            PREPARATION_TIME  = TIME("00:00:10");
            state.ack_num      = 0;
            state.sending     = false;
        }
            
        /**
	* Structure that holds acknowledge number and receiver state.
	*/
        struct state_type{
            int ack_num;
            bool sending;
        }; 
        state_type state;
            
	// definition of different ports
        using input_ports=std::tuple<typename defs::in>;
        using output_ports=std::tuple<typename defs::out>;

        /**
	* Function that performs the internal transition.
        * It turns off the receiver sending state.
	*/
        void internal_transition() {
            state.sending = false; 
        }

        /**
	* Function that performs external transition.
	* Retrieves the messages: if the number of messages
	* is more than 1, it asserts that only one message is
        * expected per time unit. It then sets the acknowledge
	* to the message value and state to sending.
	* @param e time variable
	* @param mbs message bags
	*/
        void external_transition(TIME e, 
		                         typename make_message_bags<input_ports>::type mbs) { 
            if(get_messages<typename defs::in>(mbs).size()>1){ 
		        assert(false && "one message per time uniti");
			}
			for(const auto &x : get_messages<typename defs::in>(mbs)){
                state.ack_num = static_cast < int > (x.value);
                state.sending = true;
            }  
                           
        }

        /** 
	* Function that calls internal transition
	* followed by external transition.
	* @param e the first argument
	* @param mbs the second argument
	*/
        void confluence_transition(TIME e, 
		                           typename make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(TIME(), std::move(mbs));
        }

        /**
	* Function that sends the acknowledge to the output port.
	* The acknowledge is calculated as remainder of message value
	* divided by 10. 
	* @return Message bags
	*/
        typename make_message_bags<output_ports>::type output() const {
            typename make_message_bags<output_ports>::type bags;
            Message_t out;              
            out.value = state.ack_num % 10;
            get_messages<typename defs::out>(bags).push_back(out);
            return bags;
        }

        /**
	* Function that sets the next internal transition time.
	* If the current state is sending then the next internal 
	* time is set to PREPARATION_TIME. Otherwise it is set
	* to infinity.		
	* @return Next internal time
	*/
        TIME time_advance() const {  
            TIME next_internal;
            if (state.sending) {
                next_internal = PREPARATION_TIME;
            }else {
                next_internal = std::numeric_limits<TIME>::infinity();
            }    
            return next_internal;
        }
        
	/**
	* Function that outputs acknowledge number to ostring stream.
	* @param os the ostring stream
	* @param i structure state_type
	* @return os the ostring stream
	*/
        friend std::ostringstream& operator<<(std::ostringstream& os, 
		                                      const typename Receiver<TIME>::state_type& i) {
            os << "ack_num: " << i.ack_num; 
            return os;
        }
};     
  

#endif // __BOOST_SIMULATION_PDEVS_RECEIVER_HPP__

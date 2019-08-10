/**
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

//Port definition
struct receiver_defs{
    struct out : public out_port<message_t> {
    };
    struct in : public in_port<message_t> {
    };
};
   
template<typename TIME>
class Receiver{
    using defs=receiver_defs; // putting definitions in context
    public:
        //Parameters to be overwriten when instantiating the atomic model
        TIME   PREPARATION_TIME;
        // default constructor
        Receiver() noexcept{
            PREPARATION_TIME  = TIME("00:00:10");
            state.ack_num      = 0;
            state.sending     = false;
        }
            
        // state definition
        struct state_type{
            int ack_num;
            bool sending;
        }; 
        state_type state;
            
	    // ports definition
        using input_ports=std::tuple<typename defs::in>;
        using output_ports=std::tuple<typename defs::out>;

        // internal transition
        void internal_transition() {
            state.sending = false; 
        }

        // external transition
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
            out.value = state.ack_num % 10;
            get_messages<typename defs::out>(bags).push_back(out);
            return bags;
        }

        // time_advance function
        TIME time_advance() const {  
            TIME next_internal;
            if (state.sending) {
                next_internal = PREPARATION_TIME;
            }else {
                next_internal = std::numeric_limits<TIME>::infinity();
            }    
            return next_internal;
        }

        friend std::ostringstream& operator<<(std::ostringstream& os, 
		                                      const typename Receiver<TIME>::state_type& i) {
            os << "ack_num: " << i.ack_num; 
            return os;
        }
};     
  

#endif // __BOOST_SIMULATION_PDEVS_RECEIVER_HPP__

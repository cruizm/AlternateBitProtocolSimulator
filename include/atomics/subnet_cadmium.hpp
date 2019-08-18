/** \brief This header file implements the Subnet Class
* 
* The subnets pass the packets after a time delay. But to simulate
* the unreliability of the network, only 95% of the packets will be passed
* in each of the subnet and the remaining data will be lost through the subnet.
*
* The subnets have two phases: passive and active. They are in passive phase initially.
* Whenever they receive a packet, they will be in active phase, and send out the packet
* with a probability of 95% after a time duration. Once the packet are sent, they go back
* to the passive phase.
*
* Cristina Ruiz Martin
* ARSLab - Carleton University
*
*/

#ifndef __BOOST_SIMULATION_PDEVS_SUBNET_HPP__
#define __BOOST_SIMULATION_PDEVS_SUBNET_HPP__

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

//updated the relative path
#include "../data_structures/message.hpp"

using namespace cadmium;
using namespace std;

/**
* Structure Port definition for input and output messages.
*/
struct subnet_defs{
    struct out : public out_port<Message_t> {
    };
    struct in : public in_port<Message_t> {
    };
};
//This is a meta-model, it should be overloaded for declaring the "id" parameter
template<typename TIME>
class Subnet{
    using defs=subnet_defs; // putting definitions in context
    public:
    //Parameters to be overwriten when instantiating the atomic model
           
    /**
    * Default constructor for the subnet class.
    * Initializes state structure of transmiting to false
    * and index to zero
    */
    Subnet() noexcept{
        state.transmiting     = false;
        state.index           = 0;
    }
            
    /**
    * Structure state definition which contains the state
    * type variables.
    */
    struct state_type{
        bool transmiting;
        int packet;
        int index;
    }; 
    state_type state;
    // Initializing input/output ports
    using input_ports=std::tuple<typename defs::in>;
    using output_ports=std::tuple<typename defs::out>;

    /** 
    * Internatl transition function that set transmitting state
    * to state
    */
    void internal_transition() {
        state.transmiting = false;  
    }

    /**
    * Externatl transition function that extract the messages:
    * if the number of messages is greater than 1
    * it asserts transmitting state to false and concatenate the message
    * that only one message is expected per time unit.
    * It then sets the packet to the message value and
    * sets the transmitting state to true.
    * @param e of type time
    * @param mbs of type message bags
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
    * Confluence transition function that calls internal 
    * transition fucntion followed by external transition functions.
    * @param e of type time 
    * @param mbs of type message bags
    */
    void confluence_transition(TIME e, 
			       typename make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
    }

     /**
    * Output function sends the packet number to the output port,
    * if the division of a random number with RAND_MAX is less thab 0.95.
    * Then push the out value to message bags.
    * @return message bags
    */
    typename make_message_bags<output_ports>::type output() const {
        typename make_message_bags<output_ports>::type bags;
        Message_t out;
        if ((double)rand() / (double) RAND_MAX  < 0.95){
            out.value = state.packet;
            get_messages<typename defs::out>(bags).push_back(out);
        }
        return bags;
    }

     /**
    * time_advance function that sets the next internal transition time.
    * If the current sending state is  true then the next internal 
    * time is set to time. Otherwise it is set
    * to infinity.      
    * @return Next internal time
    */
    TIME time_advance() const {
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(3.0, 1.0); 
        TIME next_internal;
        if (state.transmiting) {
            std::initializer_list<int> time = {0, 0, 
					       static_cast < int > (round(distribution(generator)))};
            // time is hour min and second
            next_internal = TIME(time);
        }else {
            next_internal = std::numeric_limits<TIME>::infinity();
        }    
        return next_internal;
    }

    friend std::ostringstream& operator<<(std::ostringstream& os, 
			                  const typename Subnet<TIME>::state_type& i) {
        os << "index: " << i.index << " & transmiting: " << i.transmiting; 
        return os;
    }
};    
#endif // __BOOST_SIMULATION_PDEVS_SUBNET_HPP__

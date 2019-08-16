/** \brief header file which is containing headers for the messages
 * 
 * Defines a message_t structure
 */

#ifndef __BOOST_SIMULATION_MESSAGE_HPP__
#define __BOOST_SIMULATION_MESSAGE_HPP__

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

/** Structure of message is defined by declaring the word message_t
 *  message_t is taking the float type of variable as a parameter
 */
struct message_t{

    message_t(){}
    message_t(float i_value)
    :value(i_value){}

  	    float   value;

    void clear() {
        message_t(); 
  	}
};

istream& operator>> (istream& is, message_t& msg);

ostream& operator<<(ostream& os, const message_t& msg);


#endif // < BOOST_SIMULATION_MESSAGE_HPP - ifndef macro end
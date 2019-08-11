#ifndef __BOOST_SIMULATION_MESSAGE_HPP__
#define __BOOST_SIMULATION_MESSAGE_HPP__

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

/*******************************************/
/**************** Message_t ****************/
/*******************************************/
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


#endif // BOOST_SIMULATION_MESSAGE_HPP
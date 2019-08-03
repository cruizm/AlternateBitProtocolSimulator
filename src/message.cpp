#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "../include/data_structures/message.hpp"

/***************************************************/
/************* Output stream ************************/
/***************************************************/

ostream& operator<<(ostream& os, const message_t& msg) {
	os << msg.value;
	return os;
}

/***************************************************/
/************* Input stream ************************/
/***************************************************/

istream& operator>> (istream& is, message_t& msg) {
	is >> msg.value;
    return is;
}

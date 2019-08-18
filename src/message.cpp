/** \brief Source file implemented for message source code
 * 
 * It has input and output stream methods coming from the header file
 * which is returning type of float in the form of message structure
 */

#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "../include/data_structures/message.hpp"

/** Output stream
 * It is an operator used to apply on an output stream  which is called insertion operator and
 * performing output character sequence in a proper format
 * @param[out] os reference to an output stream named as ostream.
 * @param[in] msg constant which is a reference to a message named as struct message_t.
 */
ostream& operator<<(ostream& os, const message_t& msg) {
	os << msg.value;
	return os;
}

/** Input stream
 * It is an operator used to apply on an input stream  which is called insertion operator and
 * performing input character sequence in a proper format
 * @param[out] os reference to an input stream named as istream.
 * @param[in] msg constant which is a reference to a message named as to struct message_t.
 */
istream& operator>> (istream& is, message_t& msg) {
	is >> msg.value;
    return is;
}

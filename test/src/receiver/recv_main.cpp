/** \brief This main file has the Receiver operation
 *
 * The file is creating the application generator where 
 * as a input it takes filepath and the data stored as a output.
 * After that it generated all the log data using the cadmium and
 * destimes library. It runs according to input provided
 * in the input file and it ends the simulation at 04:00:00:000 time.
 */

#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>

#include <cadmium/modeling/coupling.hpp>
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/concept/coupled_model_assert.hpp>
#include <cadmium/modeling/dynamic_coupled.hpp>
#include <cadmium/modeling/dynamic_atomic.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/tuple_to_ostream.hpp>
#include <cadmium/logger/common_loggers.hpp>

#include "../../../lib/DESTimes/include/NDTime.hpp"
#include "../../../lib/vendor/iestream.hpp"
#include "../../../include/data_structures/message.hpp"
#include "../../../include/atomics/receiver_cadmium.hpp"

using namespace std;
using hclock=chrono::high_resolution_clock;
using TIME = NDTime;


/**
  * SETING INPUT PORTS FOR messages 
*/

struct inp : public cadmium::in_port<Message_t>{};

/** 
  * SETING OUTPUT PORTS FOR messages 
*/


struct outp : public cadmium::out_port<Message_t>{};

/**
* This is application generator class 
* that take parameter as a file path
* and wait  for @tparam[in] T messsage input
*/

template<typename T>
class ApplicationGen : public iestream_input<Message_t,T> {
    public:
    ApplicationGen() = default;
	/**
	* It is a parameterized constructor for application generator class in which
	* from file path it takes input of the path of the file that has input 
	* for application to run
	* @param[in] file_path
	*/
    ApplicationGen(const char* file_path) : 
    iestream_input<Message_t,T>(file_path){}
};


int main(){
    //to measure simulation execution time
    auto start = hclock::now(); 
  
/**
* It produce log files of all the operation that cross 
* through during the execution of this application and 
* as a file type out_data it store all the log.    
*/
    static std::ofstream out_data("../test/data/receiver/receiver_test_output.txt");
/**
* The structure invoke the ostream which is the output stream and
* as a return the data store in the file
*/
    struct oss_sink_provider{
       static std::ostream& sink(){          
          return out_data;
        }
};
/**
* cadmium and Destimes library functions are used 
* It generates the log files and as a variable it stores
* and afte that log them all to the file
*/
	
using info=cadmium::logger::logger
    <cadmium::logger::logger_info, 
    cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
	
using debug=cadmium::logger::logger
    <cadmium::logger::logger_debug, 
    cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
	
using state=cadmium::logger::logger
    <cadmium::logger::logger_state, 
	cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
	
using log_messages=cadmium::logger::logger
    <cadmium::logger::logger_messages, 
	cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
	
using routing=cadmium::logger::logger
    <cadmium::logger::logger_message_routing, 
	cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
	
using global_time=cadmium::logger::logger
    <cadmium::logger::logger_global_time, 
	cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
	
using local_time=cadmium::logger::logger
    <cadmium::logger::logger_local_time, 
	cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
	
using log_all=cadmium::logger::multilogger
    <info, debug, state, log_messages, routing, global_time, local_time>;
	
using logger_top=cadmium::logger::multilogger<log_messages, global_time>;

/**
* For the receiver execution it get input file and
* runs the execution for number of time based on input
*/

string input_data_control = "../test/data/receiver/receiver_input_test.txt";
const char * i_input_data_control = input_data_control.c_str();
	
/**
* In here application generator initialization occur and 
* take output file, Time and based on input genrate output
*/
	
std::shared_ptr<cadmium::dynamic::modeling::model> 
generator = cadmium::dynamic::translate::make_dynamic_atomic_model
<ApplicationGen, TIME, const char* >
("generator" , std::move(i_input_data_control));

/**
* This detect the output data comming from receiver1
*/
	
std::shared_ptr<cadmium::dynamic::modeling::model> receiver1 = cadmium::
dynamic::translate::make_dynamic_atomic_model<Receiver, TIME>("receiver1");

/**
* In below all these are to store the value for 
* simulation that will be run for a timme frame and 
* and then store output accordingly
*/
	
cadmium::dynamic::modeling::Ports iports_TOP = {};

cadmium::dynamic::modeling::Ports oports_TOP = {typeid(outp)};

cadmium::dynamic::modeling::Models submodels_TOP = {generator, receiver1};

cadmium::dynamic::modeling::EICs eics_TOP = {};

cadmium::dynamic::modeling::EOCs eocs_TOP = {
    cadmium::dynamic::translate::
    make_EOC<receiver_defs::out,outp>("receiver1")
};

cadmium::dynamic::modeling::ICs ics_TOP = {
    cadmium::dynamic::translate::make_IC<iestream_input_defs<Message_t>::
    out,receiver_defs::in>("generator","receiver1")
};

std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> 
TOP = std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>( "TOP", 
                                                                    submodels_TOP, 
                                                                    iports_TOP, 
                                                                    oports_TOP, 
                                                                    eics_TOP, 
                                                                    eocs_TOP, 
                                                                    ics_TOP 
                                                                 );

/**
* In here runner are created and  duration to 
* generate runner time also measured in seconds. 
*/
auto elapsed1 = std::chrono::duration_cast<std::chrono::duration<double, 
std::ratio<1>>>(hclock::now() - start).count();
	
cout << "Model Created. Elapsed time: " << elapsed1 << "sec" << endl;
    
cadmium::dynamic::engine::runner<NDTime, logger_top> r(TOP, {0});
	
elapsed1 = std::chrono::duration_cast<std::chrono::duration<double, 
std::ratio<1>>>(hclock::now() - start).count();
	
cout << "Runner Created. Elapsed time: " << elapsed1 << "sec" << endl;
	
cout << "Simulation starts" << endl;
    
r.run_until(NDTime("04:00:00:000"));
	
auto elapsed = std::chrono::duration_cast<std::chrono::duration<double, 
std::ratio<1>>>(hclock::now() - start).count();
	
cout << "Simulation took:" << elapsed << "sec" << endl;
	
return 0;
}

/** \brief Main file is implemented in the source file
 * 
 * First we initializes COUPLEDs with help of setting the input and output ports.
 * To start the ABP simulation, it has main function which is called.
 * Different submodules of the ABP Simulator initializes which are as follows:
 *      - Application Generator
 *      - Sender
 *      - Receiver
 *      - Subnet
 *      - Network
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


#include "../lib/NDTime.hpp"
#include "../lib/iestream.hpp"

#include "../include/data_structures/message.hpp"

#include "../include/sender_cadmium.hpp"
#include "../include/receiver_cadmium.hpp"
#include "../include/subnet_cadmium.hpp"


using namespace std;

using hclock=chrono::high_resolution_clock;
using TIME = NDTime;


/**
 * Setting input ports for messages
 */
struct inp_control : public cadmium::in_port<message_t> {};
struct inp_1 : public cadmium::in_port<message_t> {};
struct inp_2 : public cadmium::in_port<message_t> {};

/**
 * Setting output ports for messages 
 */
struct outp_ack : public cadmium::out_port<message_t> {};
struct outp_1 : public cadmium::out_port<message_t> {};
struct outp_2 : public cadmium::out_port<message_t> {};
struct outp_pack : public cadmium::out_port<message_t> {};


/**
 * Now we declare the application generator class which is taking file path.
 * It is taking parameter and waits for input.
 * @tParam message T
 */
template<typename T>
class ApplicationGen : public iestream_input<message_t,T>{
    public:
    ApplicationGen() = default;
    /**
     * For class application generator , a parameterized constructor created.
     * It takes input path of the file that has the input for ruuning the application.
     * @param file_path
     */
    ApplicationGen(const char* file_path) : iestream_input<message_t,T>(file_path) {}

};



/**\brief  main function
 * 
 * Different submodules of the ABP Simulator initializes which are as follows:
 *      - Application Generator
 *      - Sender
 *      - Receiver
 *      - Subnet
 *      - Network
 * It takes input from file then run ABP Simulator and then generate output file.
 * Simulator's time metric information prints
 * @param argc Integer argument - These are counting the command line arguments
 * @param argv Argument vector - which are the command line argumenets
 */
int main(int argc, char ** argv){

    if (argc < 2){
        cout << "you are using this program with wrong parameters. Te program should be invoked as follow:";
        cout << argv[0] << " path to the input file " << endl;
        return 1; 
    }

    auto start = hclock::now(); //to measure simulation execution time

    /**
     * It is used To produce messages and operation logs which are passed through it.
     * It is storing them during execution time.
     * The file named as abp_output file showing the output data.
     */
    static std::ofstream out_data("data/abp_output.txt");

     /**
     * The structure which is a common sink provider structure 
     * It is calling the output stream which is ostream and is returning the data stored in the file.
     */
    struct oss_sink_provider{
        static std::ostream& sink(){          
            return out_data;

        }

    };

    /**
     * To call source loggers structure by using the word logger , a definition of cadmium.
     * It is producing the log files in a proper format and storing them in variables and the file to be logged.
     */
    using info=cadmium::logger::logger<cadmium::logger::logger_info,
          cadmium::dynamic::logger::formatter<TIME>,
          oss_sink_provider>;
    using debug=cadmium::logger::logger<cadmium::logger::logger_debug,
          cadmium::dynamic::logger::formatter<TIME>,
          oss_sink_provider>;
    using state=cadmium::logger::logger<cadmium::logger::logger_state,
          cadmium::dynamic::logger::formatter<TIME>,
          oss_sink_provider>;
    using log_messages=cadmium::logger::logger<cadmium::logger::logger_messages,
          cadmium::dynamic::logger::formatter<TIME>,
          oss_sink_provider>;
    using routing=cadmium::logger::logger<cadmium::logger::logger_message_routing,
          cadmium::dynamic::logger::formatter<TIME>,
          oss_sink_provider>;
    using global_time=cadmium::logger::logger<cadmium::logger::logger_global_time,
          cadmium::dynamic::logger::formatter<TIME>,
          oss_sink_provider>;
    using local_time=cadmium::logger::logger<cadmium::logger::logger_local_time,
          cadmium::dynamic::logger::formatter<TIME>,
          oss_sink_provider>;
    using log_all=cadmium::logger::multilogger<info,
                                               debug,
                                               state,
                                               log_messages,
                                               routing,
                                               global_time,
                                               local_time>;

    using logger_top=cadmium::logger::multilogger<log_messages,
                                                 global_time>;


    /**
     * For the application to control input data, Passing first argument value to input.
     * It is creating generator file to execute and for number of input times , it runs the execution.
     */
    string input_data_control = argv[1];
    const char * i_input_data_control = input_data_control.c_str();

    /**
     * The generator which is initialized contain has output file path, time and producing 
     * the output by passing given inputs
     */
    std::shared_ptr<cadmium::dynamic::modeling::model> generator_con =
                                                                       cadmium::dynamic::translate::make_dynamic_atomic_model<ApplicationGen,
                                                                       TIME,
                                                                       const char* >("generator_con" ,
                                                                       std::move(i_input_data_control));


    /**
     * Recognizing output data which is sent from sender1
     */
    std::shared_ptr<cadmium::dynamic::modeling::model> sender1 =
                                                                 cadmium::dynamic::translate::make_dynamic_atomic_model<Sender,
                                                                 TIME>("sender1");


    /**
     * Recognizing output data which is received from receiver1
     */
    std::shared_ptr<cadmium::dynamic::modeling::model> receiver1 = 
                                                                   cadmium::dynamic::translate::make_dynamic_atomic_model<Receiver,
                                                                   TIME>("receiver1");



    /**
     * Recognizing output data which is received from subnet1 and also from subnet2
     */
    std::shared_ptr<cadmium::dynamic::modeling::model> subnet1 =
                                                                 cadmium::dynamic::translate::make_dynamic_atomic_model<Subnet,
                                                                 TIME>("subnet1");
    std::shared_ptr<cadmium::dynamic::modeling::model> subnet2 = 
                                                                 cadmium::dynamic::translate::make_dynamic_atomic_model<Subnet,
                                                                 TIME>("subnet2");

    /**
     * The operations of network input and output ports which are used for each time frame is going to be stored
     * as a value and after that it is storing in the output file.
     */
    cadmium::dynamic::modeling::Ports iports_Network = {typeid(inp_1),typeid(inp_2)};
    cadmium::dynamic::modeling::Ports oports_Network = {typeid(outp_1),typeid(outp_2)};
    cadmium::dynamic::modeling::Models submodels_Network = {subnet1, subnet2};
    cadmium::dynamic::modeling::EICs eics_Network = {
        cadmium::dynamic::translate::make_EIC<inp_1, subnet_defs::in>("subnet1"),
        cadmium::dynamic::translate::make_EIC<inp_2, subnet_defs::in>("subnet2")
    };
    cadmium::dynamic::modeling::EOCs eocs_Network = {
        cadmium::dynamic::translate::make_EOC<subnet_defs::out,outp_1>("subnet1"),
        cadmium::dynamic::translate::make_EOC<subnet_defs::out,outp_2>("subnet2")
    };
    cadmium::dynamic::modeling::ICs ics_Network = {};
    std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> NETWORK =
                                                                         std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>(
                                                                         "Network", 
                                                                         submodels_Network, 
                                                                         iports_Network, 
                                                                         oports_Network, 
                                                                         eics_Network, 
                                                                         eocs_Network, 
                                                                         ics_Network 
                                                                         );

    /**
     * The operations of network input and output control packet acknowledgement of ABP simulator input and output ports
     * which are used for each time frame is going to be stored as a value and after that it is storing in the output file.
     */
    cadmium::dynamic::modeling::Ports iports_ABPSimulator = {typeid(inp_control)};
    cadmium::dynamic::modeling::Ports oports_ABPSimulator = {typeid(outp_ack),typeid(outp_pack)};
    cadmium::dynamic::modeling::Models submodels_ABPSimulator = {sender1, receiver1,NETWORK};
    cadmium::dynamic::modeling::EICs eics_ABPSimulator = {
        cadmium::dynamic::translate::make_EIC<inp_control, sender_defs::controlIn>("sender1")
    };
    cadmium::dynamic::modeling::EOCs eocs_ABPSimulator = {
        cadmium::dynamic::translate::make_EOC<sender_defs::packetSentOut,outp_pack>("sender1"),
        cadmium::dynamic::translate::make_EOC<sender_defs::ackReceivedOut,outp_ack>("sender1")
    };
    cadmium::dynamic::modeling::ICs ics_ABPSimulator = {
        cadmium::dynamic::translate::make_IC<sender_defs::dataOut, inp_1>("sender1","Network"),
        cadmium::dynamic::translate::make_IC<outp_2, sender_defs::ackIn>("Network","sender1"),
        cadmium::dynamic::translate::make_IC<receiver_defs::out, inp_2>("receiver1","Network"),
        cadmium::dynamic::translate::make_IC<outp_1, receiver_defs::in>("Network","receiver1")
    };
    std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> ABPSimulator =
                                                                              std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>(
                                                                              "ABPSimulator", 
                                                                              submodels_ABPSimulator, 
                                                                              iports_ABPSimulator, 
                                                                              oports_ABPSimulator, 
                                                                              eics_ABPSimulator, 
                                                                              eocs_ABPSimulator, 
                                                                              ics_ABPSimulator 
                                                                              );


    /**
     * It is storing top values of top model operations which is used for each time frame and 
     * then storing in output file
     */
    cadmium::dynamic::modeling::Ports iports_TOP = {};
    cadmium::dynamic::modeling::Ports oports_TOP = {typeid(outp_pack),typeid(outp_ack)};
    cadmium::dynamic::modeling::Models submodels_TOP = {generator_con, ABPSimulator};
    cadmium::dynamic::modeling::EICs eics_TOP = {};
    cadmium::dynamic::modeling::EOCs eocs_TOP = {
        cadmium::dynamic::translate::make_EOC<outp_pack,outp_pack>("ABPSimulator"),
        cadmium::dynamic::translate::make_EOC<outp_pack,outp_ack>("ABPSimulator")
    };
    cadmium::dynamic::modeling::ICs ics_TOP = {
        cadmium::dynamic::translate::make_IC<iestream_input_defs<message_t>::out,inp_control>("generator_con","ABPSimulator")
    };
    std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> TOP =
                                                                     std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>(
                                                                     "TOP", 
                                                                     submodels_TOP, 
                                                                     iports_TOP, 
                                                                     oports_TOP, 
                                                                     eics_TOP, 
                                                                     eocs_TOP, 
                                                                     ics_TOP 
                                                                     );

    /**
     * Create a model which is measuring elapsed time form creations in seconds during run time. Then create runner and measuring elapsed 
     * time in seconds. Simulation starts and Also shows the time used to finish th simulation
     * time took to complete the simulation which is run 04:00:00:000 time period.
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
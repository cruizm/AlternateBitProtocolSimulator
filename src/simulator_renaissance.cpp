/** /brief This source file contains function definition for simulator output modifications.
 * 
 * Function output_file_evolution modifies ABP simulator or test sets output file
 * to a user-friendly readable csv format. 
 * 
 * The format of ouput file generated from the function is in csv.
 * Sample output from file is shown below:
 * 
 * Time,Value,Port,Component
 * 00:00:10:000,5,out,generator_con
 * 00:00:20:000,1,packetSentOut,sender1
 * 00:00:20:000,11,dataOut,sender1
 * 00:00:23:000,11,out,subnet1
 * 00:00:33:000,1,out,receiver1
 * 
 */
/**
 * Hamza Sadruddin
 * Saad Hasan
 * Carleton University
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <vector>
#include <unistd.h>

#include "../include/simulator_renaissance.hpp"

using namespace std;

/**
 * @brief          Function modifies the input file to more readable format 
 *
 * @param[in]      input_file   The input file is the ouput file of ABP or test sets
 * @param[in]      output_file  The output file is modified to more readable format
 */
void output_file_evolution(char input_file[], char output_file[]) {
	/**
	 * String variables to store the parsed sub-strings
	 */
    string line, time, component, comma = ",";
    int arr[5] = { 0 }, /**< arr array stores the position of comma occured in string */
     	counter = 0, val_pos = 0, scope_resl_op = 0;  /**<  Different variables initialized for later use */

    /**
     * @brief      if block to check file existence
     * If the file doesn't exist then the stat function returns -1 in the if condition,
     * making the condition true. The nested if condition checks for EOENT(Non-extstent)
     * condition and upon having true state, prints the stated message. The conditional
     * block, if it's true, then termintes the current funtion by executing return statement.
     */
    struct stat statBuff; /**< To get file statistics */
    if (stat(input_file, &statBuff) < 0) {
        if (errno == ENOENT) {
        cout << input_file << " doesn't exist: " << -ENOENT << endl;
        }
        return;
    }

    /**
     * @brief      Subclasses of istream
     * ifstream class creates an object i_d_stream to the input file
     * ofstream class creates an object o_d_stream to the output file. The 
     * addtional parameters in oftsream statement create the file(ofstream::out)
     * and also clear(ofstream::trunc) any data residing in it. 
     */

    ifstream i_d_stream(input_file); /**<  Input data stream */
    ofstream o_d_stream(output_file, ofstream::out | ofstream::trunc); /**< Output data stream */

    /**
     * The following if block checks whether the access to the output file is
     * permitted or not. The access function checks for file existence (F_OK) and 
     * write permission (W_OK). If the access returns 0, then the block executes and
     * prints the stated message. In the end, block termintes the current function by 
     * executing return statement.
     */
    if(access(output_file, F_OK | W_OK)) {
		cout << output_file << " access violation: " << errno << endl;
		return;
	} 

	/**
	 * This if block checks whether both (&&), input and output files are
	 * opened or not. If the condition is true, then the block executes,
	 * otherwise it prints the stated message in else statement.
	 */
    if (i_d_stream.is_open() && o_d_stream.is_open()) {
        cout << "Resident Evil 8" << endl;

        /** Writes the strings on the first line of the output file */
        o_d_stream << "Time" << "," << "Value" << "," << "Port" << "," << "Component" << endl; 

        /**
         * While loop runs until the End-of-File is encounterd. i_d_stream.eof() returns true 
         * when the End-of-File has been reached by the last input operation.
         */
        while (!i_d_stream.eof()) {
        	/**
        	 * getline reads the first line via the i_d_stream, and stores it in string line.
        	 */
            getline(i_d_stream, line);
            /**
             * If the length of the line read from the previous command equals 12(if statement),
             * it means that the string is time. This is what is checked in the if statement
             * and the line is copied to the time string.
             * Otherwise if the length of the line is greater than 12(else if statement),
             * then the block parses the string for the required pattern.
             */
            if (line.length() == 12) {
               time = line;
            }else if (line.length() > 12) {
                string payload = line; /**<  string line is copied to string payload */
                 /** 
                  * .find() returns the index of the first occurrence of the substring("[]")
                  *  in the string (payload) from the start.
                  *  If the substring is found it returns std::string::npos which means -1. The
                  *  following if conditional block checks for it, and if the statement becomes true,
                  *  then the "continue", statement executes, and the code handle returns to while block.
                  *  Otherwise, the block tries to parse the string for the required pattern.
                  */
                size_t mes_status = payload.find("[]");
                if (mes_status != std::string::npos) {
                    continue;
                }else{
                    std::fill_n(arr, 5, 0); 		  /**<  Resets the arr elements with 0 */
                    counter = 0;                      /**<  counter is reset */
                    size_t pos = payload.find(comma); /**<  Finds the first occurence of comma in payload */
                    while (pos != std::string::npos)  /**<  Keep running until there is no comma */
                    {
                        arr[counter + 1] = pos;       /**<  Store the location of first comma at position 1 in arr */
                        ++counter; 				      /**< Increment the counter by 1 */
                        pos = payload.find(comma, pos + comma.size()); /** Look for the next occurrence of comma starting after the 
                                                                        * first occurrence of the previous comma*/
                    }
                    /**
                     * The following line finds the position of model (payload.find("model")) in
                     * the payload, and that position is added to (6) to include the length of model
                     * and space. This becomes the parameter of (.substr()) which returns the substring
                     * starting from this parameter position till the end-of-line.
                     */
                    string component_check = payload.substr(payload.find("model") + 6);
                    counter = 0;				      /**<  counter is reset */
                    /**
                     * The following do-while loop works until the first 0 is encountered in arr
                     * starting after the 0th element position*/
                    do {
                        val_pos = payload.find("{", arr[counter]); /**< Find the first "{" position starting from arr value position */
                        string value = payload.substr(val_pos + 1, payload.find("}", /**< Returns the substring between {} */ 
                        								  arr[counter]) - val_pos - 1);	 /**< and stores it in string value*/	
                        if (value == "") {	/**< If the previous line returns "" (meaning no message value), then the if condition*/
                            continue;		/**< becomes true and the "continue", statement executes, returning the code handle to while block.*/
                        }else{				/**< Otherwise code continues with the task of parsing.*/	
                        	scope_resl_op = payload.find("::", arr[counter]); /**< Find the first "::" position starting from arr value position */
                            /** The following line returns the substring between "::" and ":". 
                             * It then stores it in string port*/
                            string port = payload.substr(scope_resl_op + 2,
                            								   ((payload.find(":", scope_resl_op + 2) - scope_resl_op) - 2));
                            /**The following line writes parsed strings to the output via o_d_stream object*/
                            o_d_stream << time << "," << value << "," << port << "," << component_check << endl;
                        }
                    } while (arr[++counter] != 0); /**< Keep running till 0 is encountered */

                }
            }
        }

    }else{
    	cout << "Files are not opened" << endl;
    }

    i_d_stream.close(); /**< Closes the input file */
    o_d_stream.close(); /**< Closes the output file */

}
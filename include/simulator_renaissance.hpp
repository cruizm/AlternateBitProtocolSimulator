/** /brief This header file contains functional prototypes for simulator output modifications.
 * 
 * Function output_file_evolution modifies ABP simulator or test sets output file
 * to a user-friendly readable. 
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
#ifndef __SIMULATOR_RENAISSANCE_HPP_
#define __SIMULATOR_RENAISSANCE_HPP_

/**
 * @brief          Function modifies the input file to more readable format 
 *
 * @param[in]      input_file   (type string) The input file is the ouput file of ABP or test sets
 * @param[in]      output_file  (type string) The output file is modified to more readable format
 */
void output_file_evolution(char *, char *);


#endif /**< __SIMULATOR_RENAISSANCE_HPP_ */

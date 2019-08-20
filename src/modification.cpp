/** \brief This modification file calculates the percentage of packets lost
*
* This file defines a function filter2 which takes two files as parameters
* 
* The first parameter is the input file which it reads
* The second parameter is the output file where it writes the modified output
*
* Cristina Ruiz Martin
* ARSLab - Carleton University
*
*/

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

void filter2(FILE *input2, FILE *output2){
    FILE * fp;
	FILE * fp_out;
    fp = input2;
	fp_out = output2;
	
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *pData = new char[size+1];
    fread(pData, sizeof(char),size,fp);
    fclose(fp);
    
    /**
	* Parsing the read data from csv file
	*/
    char* pch;
    pch = strtok(pData, ",");
    float counter = 0.0, counter1 = 0.0, counter2 = 0.0, pkt_loss = 0.0, pkt_loss_percnt = 0.0;
	int rounding = 0;
	
    while(pch != NULL){
	    /** 
		* Incrementing the counter everytime string matches with "dataOut"
		*/
        if (strcmp(pch,"dataOut")==0){
        counter++;
		}
	    /** 
		* Incrementing the counter1 everytime string matches with "ackReceivedOut"
		*/
        if (strcmp(pch,"ackReceivedOut")==0){
            counter1++;
		}
		/** 
		* Incrementing the counter2 everytime string matches with "packetSentOut"
		*/
        if (strcmp(pch,"packetSentOut")==0){
            counter2++;
        }
        pch = strtok(NULL, ",");
    }
    
	fprintf(fp_out,"\nThe total number of packets sent, dataOut = %f\n",counter);
    fprintf(fp_out,"\nThe total number of acknowledgements received, ackReceivedOut = %f\n",counter1);
    fprintf(fp_out,"\nThe total number of packets generated, packetSentOut= %f\n",counter2);
	/** 
	* Calculating the total number of packet loss
	*/
	pkt_loss = counter - counter1;
	fprintf(fp_out,"\nThe total number of packets lost = %f\n",pkt_loss);
	/**
	* Calculating the percentage of packet loss
	*/
	pkt_loss_percnt = (pkt_loss/counter2)*100;
	rounding = round(pkt_loss_percnt);
	fprintf(fp_out,"\nThe percentage of packets that are lost = %d%%\n",rounding);
	
fclose(fp_out);   
}

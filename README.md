# **ALTERNATE BIT PROTOCOL IMPLEMENTATION IN CADMIUM**
---
### FILES ORGANIZATION
---
### Carleton University
#### Authors
---
**Main Developer**: Cristina Ruiz Martin
**Modified by**: Tarim Islam & Navid Hossain
### Introduction
---
### Alternate Bit Protocol (ABP) is a protocol which is connectionless for transfering pair of protocol entities. It is a simple form of sliding window protocol.Interation of two pairs in a message is based on sequence of 0 & 1. 
#### **Receiver**- It receives the data and sends back acknowledgement after certain perios of time.
#### **Subnets**- It just transmits the packets to next node after a time delay.
#### **Sender**-  It sends the packet and then waits for acknowledgement from the receiver but if it does not receive the acknowledgement within time window it will resend the packet with alternating bit attached to it so that it can differentiate between the two packets. Once it receives the acknowledgement it will send the next packet until it has no more packets to send.
---
### File Management
1. src [This folder contains the source code for the message and top model]
2. data_structures [Contains the source code for the top message]
3. top_model [Contains the source code for the top_model]
4. lib [This folder contains the third party header files]
5. vendor[This folder contains 3rd party header files needed in the project]
   5.1 iestream.hpp
   5.2 NDTime.hpp
   5.3 cadmium-master[contains cadmium files]
   5.4 DESTimes-master[contains destimes files]
	
### include [This folder contains the header files used]
	1. atomics
		1.1 receiverCadmium.hpp
		1.2 senderCadmium.hpp
		1.3 subnetCadmium.hpp
	2. data_structures [contains message header file]
		2.1 message.hpp
		
### test [This folder the unit test for the different include files]
1. data [This folder contains test input output files]
		
		1.1 receiver [This folder contains the input output files foe the unit test of the receiver]
		1.2 sender [This folder contains the input output files foe the unit test of the sender]
		1.3 subnet [This folder contains the input output files foe the unit test of the subnet]
		
2. src [This folder contains the source code for the sender,receiver and subnet]
		
		2.1 receiver[This folder contains the source code for the receiver]
			main.cpp
			
		2.2 sender[This folder contains the source code for the sender]
			main.cpp
			
		2.3 subnet[This folder contains the source code for the subnet]
			main.cpp
			
3. doc [contains documents related to the project]

#### data [contains input/output files required/generated by the ABP simulator]
	1. input_abp_0.txt
	2. input_abp_1.txt
	3. abp_output_0.txt
	4. abp_output_1.txt
### makefile [make file to compile the project]
	
### Steps to Run Simulations
---
**alternatebitprotocol.doc contains the explanation of this simulator**
       
 1.  Run the unit test
       
2.1  Run subnet test

 2.1.1 Open the terminal. Press in your keyboard Ctrl+Alt+t
 
 2.1.2 Set the command prompt in the project folder. To do so, type in the terminal the path to this folder.
>			Example: cd Documents/AlternateBitProtocol

 2.1.3. To compile the test, type in the terminal:
>			make clean; make all

 2.1.4. To run the test, change directory to bin folder where the executables are located. For example: cd bin. type in the terminal                        
>     "./NAME_OF_THE_COMPILED_FILE". For this specific test you need to type:     ./SUBNET_TEST

 2.1.5.  To check the output of the test, open               
>                      "test/data/subnet/subnet_test_output.txt"

2.2  To run receiver and sender tests, the steps are analogous to 2.1, just select the appropriate path

3. Run the simulator
   1. Open the terminal. Press in your keyboard Ctrl+Alt+t
   
   2. Set the command prompt in the project folder. To do so, type in the terminal the path to this folder.
>		          Example: cd Documents/AlternateBitProtocol
4. To run the simulation, type in the terminal "./NAME_OF_THE_COMPILED_FILE NAME_OF_THE_INPUT_FILE". For this test you need to type:
>	              ./bin/ABP ../data/input_abp_0.txt

5. To check the output of the simulation, open  "data/abp_output.txt"

6. To execute the simulator with different inputs

 6.1. Create new .txt files with the same structure as input_abp_0.txt or input_abp_1.txt
 
 6.2. Run the simulator using the instructions in step 4
 
 6.3. If you want to keep the output, rename abp_output.txt. To do so, type in the terminal: "mv abp_output.txt NEW_NAME"
>		         Example: mv abp_output.txt abp_output_0.txt

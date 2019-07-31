This folder contains a simulator for an ALTERNATE BIT PROTOCOL implemented in Cadmium

/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt	

bin - It contains all the executable(.exe) files and is created during the execution phase.

build - It contains all the object(.o) files and is also created during the execution phase.

data - This folder has the input and output files for the simulator.
		abp_output_0.txt
		abp_output_1.txt
		input_abp_0.txt
		input_abp_1.txt
	

doc - This folder contains extra documentation other than README.txt
		alternatebitprot.pdf
		Cadmium_Documentation_Ubuntu.pdf
		Cadmium_Windows.pdf

include - This folder consists of various header(.hpp) files used in the code.
		- atomics
			receiverCadmium.hpp
			senderCadmium.hpp
			subnetCadmium.hpp
		-data_structures
			message.hpp	

lib - Folder where third-party library files are stored.
		- cadmium (This folder contains the cadmium (third party) library files)
		- DESTimes (This folder contains the DESTimes (third party) library files0
		- vendor (This folder contains vendor (third party) header files)
			iestream.hpp
			NDTime.hpp
	
src - This folder contains the source files used for the simualator
		- data_structures (This folder contains the source files for structure of the data)
			message.cpp
		- top_model (This folder contains the source files from top_model)
			main.cpp

test - This folder contains files realted to the unit tests]
		- data (This folder contains the input and output files for the unit tests)
			
			- receiver (This folder contains some data for receiver testing and simulator outputs)
				receiver_input_test.txt
				receiver_test_output.txt

			- sender (This folder contains some data for sender testing and simulator outputs)
				sender_input_test_ack_In.txt
				sender_input_test_control_In.txt
				sender_test_output.txt

			- subnet (This folder contains some data for subnet testing and simulator outputs)
				subnet_input_test.txt
				subnet_test_output.txt

		- src (This folder contains the source code files for the unit tests)
			- receiver (This folder contains source code for the receiver)
				main.cpp

			- sender (This folder contains source code for the sender)
				main.cpp

			- subnet (This folder contains source code for the subnet)
				main.cpp
	
/*************/
/****STEPS****/
/*************/

0 - alternatebitprotocol.doc contains the explanation of this simulator

1 - Update include paths in all the makefiles in this folder and subfolders. You need to update the following lines:
	INCLUDECADMIUM=-I ../../cadmium/include
    Update the relative path to cadmium/include from the folder where the makefile is. You need to take into account where you copied the folder during the installation process
	Example: INCLUDECADMIUM=-I ../../cadmium/include
    
2 - Run the unit tests
	2.1. Run subnet test
		1 - Open the terminal. Press in your keyboard Ctrl+Alt+t
		2 - Set the command prompt in the test/subnet folder. To do so, type in the terminal the path to this folder.
			Example: cd Documents/AlternateBitProtocol/test/subnet
		3 - To compile the test, type in the terminal:
			make clean; make all
		4 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE". For this specific test you need to type:
			./SUBNET
		5 - To check the output of the test, open  "subnet_test_output.txt"
	2.2. To run receiver and sender tests, the steps are analogous to 2.1
			
3 - Run the simulator
	1 - Open the terminal. Press in your keyboard Ctrl+Alt+t
	2 - Set the command prompt in the top_model folder. To do so, type in the terminal the path to this folder.
		Example: cd ../../top_model
	3 - To compile the project, type in the terminal:
		make clean; make all
	4 - To run the simulation, type in the terminal "./NAME_OF_THE_COMPILED_FILE NAME_OF_THE_INPUT_FILE". For this test you need to type:
		./ABP input_abp_1.txt
	5 - To check the output of the simulation, open  "abp_output.txt"
	6 - To execute the simulator with different inputs
		6.1. Create new .txt files with the same structure as input_abp_0.txt or input_abp_1.txt
		6.2. Run the simulator using the instructions in step 4
		6.3. If you want to keep the output, rename abp_output.txt. To do so, type in the terminal: "mv abp_output.txt NEW_NAME"
			Example: mv abp_output.txt abp_output_0.txt

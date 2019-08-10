This folder contains a simulator for an ALTERNATE BIT PROTOCOL implemented in Cadmium

/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt	

bin   [for executables]

build [for object files]

data  [Data files for testing and some simulator outputs]

doc   [Contains documents related to ABP and Cadmium]

include [This folder contains the header files and data structures used in the project]
	message.hpp
	receiverCadmium.hpp
	senderCadmium.hpp
	subnetCadmium.hpp


lib [This folder contains 3rd party header files needed in the project]
	cadmium
	DESTimes
	iestream.hpp
	NDTime.hpp

src [This folder contains source code for the Alternate Bit Protocol simulator]

test [This folder the unit test for the different include files]
	data  [Data files used by receiver, sender and subnet]
		receiver_input_test.txt
		receiver_test_output.txt
		sender_input_test_ack_In.txt
		sender_input_test_control_In.txt
		sender_test_output.txt
		subnet_input_test.txt
		subnet_test_output.txt
	src [Contains the source code]
		receiver [This folder contains the unit test of the receiver]
			receiver.cpp
		sender [This folder contains the unit test of the sender]
			sender.cpp
		subnet [This folder contains the unit test of the subnet]
			subnet.cpp

	
/*************/
/****STEPS****/
/*************/

1 - doc/alternatebitprot.pdf contains the explanation of this simulator1
    
2 - Run the unit tests
	2.1. Run subnet test
		1 - Open the terminal. Press in your keyboard Ctrl+Alt+t
		2 - To compile the test, type in the terminal:
			make clean_all; make sender
		3 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE". For this specific test you need to type:
			./bin/SENDER_TEST
		4 - To check the output of the test, open  "test/data/sender_test_output.txt"
	2.2. To run receiver and subnet tests, the steps are analogous to 2.1
			
3 - Run the simulator
	1 - Open the terminal. Press in your keyboard Ctrl+Alt+t
	2 - To compile the project, type in the terminal:
		make clean_all; make all
	3 - To run the simulation, type in the terminal "./NAME_OF_THE_COMPILED_FILE NAME_OF_THE_INPUT_FILE". For this test you need to type:
		./bin/ABP data/input_abp_1.txt
	4 - To check the output of the simulation, open  "abp_output.txt"
	5 - To execute the simulator with different inputs
		5.1. Create new .txt files with the same structure as input_abp_0.txt or input_abp_1.txt
		5.2. Run the simulator using the instructions in step 3
		5.3. If you want to keep the output, rename abp_output.txt. To do so, type in the terminal: "mv abp_output.txt NEW_NAME"
			Example: mv abp_output.txt abp_output_0.txt

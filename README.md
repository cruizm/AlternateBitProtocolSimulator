# *Alternate Bit Protocol Simulator*
---
## Organization: Carleton University
---
### *Authors:*
### Originally Developed By: [Dr. Cristina Ruiz Martin](https://github.com/cruizm)
### Modified By: [Saad Hasan](https://github.com/khanyousefzai) and [Hamza Sadruddin](https://github.com/hamza-sadruddin)
---
# Introduction

#### Alternate Bit Protocol (ABP) simulator is a communication protocol to ensure reliable transmission through an unreliable network. It consists of three components: sender, network (decomposed further into two subnets) and receiver. The sender sends a packet and waits for an acknowledgement. If the acknowledgement doesn't arrive within a predefined time, the sender re-sends this packet until it receives an expected acknowledgement and then sends the next packet. In order to distinguish two consecutive packets, the sender adds an additional bit on each packet (called alternating bit because the sender uses 0 and 1 alternatively).
#### The behavior of receiver is to receive the data and send back an acknowledgement extracted from the received data after a time period. The subnets just pass the packets after a time delay. However, in order to simulate the unreliability of the network, only 95% of the packets will be passed in each of the subnet, i.e. 5% of the data will be lost through the subnet.
#### There is good ducumentation for the installation of Cadmium as it is developed in Cadmium installation on differnet platforms like windows and Linux and about ALternate Bit Protocol Simulator. Following the link for more guide [Installation Guide and Documentation](https://github.com/hamza-sadruddin/AlternateBitProtocolSimulator/tree/master/doc). We are focusing on the proper documentation, reviewing the code , following software documentation , conventions and proper code standards along with the optimization of the new feature to imporve the simulator. 
---
# Files Organization
**bin [This folder has files for executables genrated after running the Simulator]**
- ABP.exe
- RECEIVER_TEST.exe
- SENDER_TEST.exe
- SUBNET_TEST.exe

**build [This Folder has all object generated after after runnung the simulator]**
- main.o
- main_receiver.o
- main_sender.o
- main_subnet.o
- message.o

**data  [Data files for testing and some simulator outputs]**
- receiver_input_test.txt
- receiver_test_output.txt
- sender_input_test_ack_In.txt
- sender_input_test_control_In.txt
- sender_test_output.txt
- subnet_input_test.txt
- subnet_test_output.txt

**doc [This folder contains documents related to ABP and Cadmium including installation guide in winddows and Linux]**
- alternatebitprot.pdf
- Cadmium_Documentation_Ubuntu.pdf
- Cadmium_Windows.pdf

**include [This folder contains the header files and data structures used in the project]**
1. data_structures [This folder has message.hpp file]
    - message.hpp
- receiverCadmium.hpp
- senderCadmium.hpp
- subnetCadmium.hpp

**lib [This folder contains 3rd party header files needed in the project]**
1. cadmium [[This folder contains cadmium functionalities]
2. DESTimes[[This folder contains DESTimes functionalities]
-	iestream.hpp
-	NDTime.hpp

**src [This folder contains source code for the Alternate Bit Protocol simulator]**
- main.cpp
- message.cpp

**test [This folder the unit test for the different include files]**
1. 	data  [Data files used by receiver, sender and subnet]**
    -  receiver_input_test.txt
	- receiver_test_output.txt
	- sender_input_test_ack_In.txt
	- sender_input_test_control_In.txt
	- sender_test_output.txt
	- subnet_input_test.txt
	-   subnet_test_output.txt
2. 	src [Contains the source code]
	i. receiver [This folder contains the unit test of the receiver]
     - receiver.cpp
     
    ii. sender [This folder contains the unit test of the sender]
	 - sender.cpp

	iii. subnet [This folder contains the unit test of the subnet]
	- subnet.cpp
---
# Installation Guide
Below are the instructions to install dependencies on Windows operating system and tLnux is available in the section [Installation Guide and Documentation](https://github.com/hamza-sadruddin/AlternateBitProtocolSimulator/tree/master/doc).

**apt-cyg installations: Open Cygwin in administrator mode and type the below commands,**
```
wget rawgit.com/transcode-open/apt-cyg/master/apt-cyg
install apt-cyg/bin
apt-cyg install git
```
Please use these commands if you don't have git pre-installed in your system.
** Cadmium dependencies installations. **
- Open the Cygwin terminal in the location where you have downloaded the setup (.exe) file for cygwin. Type
 ``` ./setup-x86_64.exe -q -P libboost-devel or apt-cyg install libboost-devel. ``` 
- This will install boost library.
- Select a folder to download the Cadmium and DESTimes files for the project.
- Open the Cygwin terminal inside this folder location and Type ``` git clone https://github.com/SimulationEverywhere/cadmium ```
- To download the Cadmium dependencies.Type ``` git clone https://github.com/Laouen/DESTimes.git ``` to download the DESTimes dependencies.
---
#  Steps to Run the Simulator

**1.  Run the unit tests**
The same steps should be followed for receiver and subnet tests as we are showing the steps for the sender. 
   - Open the terminal. Press in your keyboard Ctrl+Alt+t
   - To compile the test, type in the terminal:
        ``` make clean_all; make sender```
   - To run the test, type in the terminal
    ``` ./NAME_OF_THE_COMPILED_FILE ```
   - For this specific test you need to type:
    ```	./bin/SENDER_TEST ```
   - To check the output of the test,  open  "test/data/sender_test_output.txt"
			
**2.  - Run the simulator**
   - Open the terminal. Press in your keyboard Ctrl+Alt+t
   - To compile the project, type in the terminal:
		```make clean_all; make all```
   - To run the simulation, type in the terminal
   ```./NAME_OF_THE_COMPILED_FILE NAME_OF_THE_INPUT_FILE. ```
   For this test you need to type:
		```./bin/ABP ../data/input_abp_1.txt```
   - To check the output of the simulation, open  "abp_output.txt"
   - To execute the simulator with different inputs
		- Create new .txt files with the same structure as input_abp_0.txt or input_abp_1.txt
		- Run the simulator using the instructions in step 3
		- If you want to keep the output, rename abp_output.txt. To do so, type in the terminal: "mv abp_output.txt NEW_NAME"
			```Example: mv abp_output.txt abp_output_0.txt```

CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I lib/cadmium/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin/src bin/test)
build_folder := $(shell mkdir -p build/src build/test/subnet build/test/sender build/test/receiver)

#TARGET TO RUN EVERYTHING (BIT SIMULATOR + TESTS TOGETHER)
all: simulator tests

#TARGET TO RUN ONLY BIT SIMULATOR
simulator: main.o message.o
	$(CC) -g -o bin/src/ABP build/src/main.o build/src/message.o
	
#TARGET TO RUN ALL THE TESTS TOGETHER (NOT SIMULATOR)
tests: test_subnet_main.o test_sender_main.o test_receiver_main.o message.o
		$(CC) -g -o bin/test/SUBNET_TEST build/test/subnet/main.o build/src/message.o
		$(CC) -g -o bin/test/SENDER_TEST build/test/sender/main.o build/src/message.o 
		$(CC) -g -o bin/test/RECEIVER_TEST build/test/receiver/main.o build/src/message.o  

main.o: src/top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/top_model/main.cpp -o build/src/main.o
	
test_subnet_main.o: test/src/subnet/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/subnet/main.cpp -o build/test/subnet/main.o

test_sender_main.o: test/src/sender/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/sender/main.cpp -o build/test/sender/main.o

test_receiver_main.o: test/src/receiver/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/receiver/main.cpp -o build/test/receiver/main.o

message.o: 
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/data_structures/message.cpp -o build/src/message.o

#CLEAN COMMANDS
clean_all: clean_simulator clean_tests
clean_simulator:
	rm -f bin/src/ABP.exe build/src/*.o *~
clean_tests:
	rm -f bin/test/*.exe build/test/**/*.o *~	





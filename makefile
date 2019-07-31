CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I lib/cadmium/include

build_folder := $(shell mkdir -p build)
bin_folder := $(shell mkdir -p bin)

all: main.o ../build/message.o 
	$(CC) -g -o bin/MAIN_ABP build/top_model_main.o build/message.o
<<<<<<< HEAD
	$(CC) -g -o bin/TEST_RECEIVER build/receiver_main.o build/message.o
	$(CC) -g -o bin/TEST_SENDER build/sender_main.o build/message.o
	$(CC) -g -o bin/TEST_SUBNET build/subnet_main.o build/message.o
=======
	$(CC) -g -o bin/RECEIVER build/receiver_main.o build/message.o
	$(CC) -g -o bin/SENDER build/sender_main.o build/message.o
	$(CC) -g -o bin/SUBNET build/subnet_main.o build/message.o
>>>>>>> 03980eb4329f72bfd1c1a0823e5a4351ee3a5bc1

main.o: src/top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/top_model/main.cpp -o build/top_model_main.o
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/receiver/main.cpp -o build/receiver_main.o
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/sender/main.cpp -o build/sender_main.o
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/subnet/main.cpp -o build/subnet_main.o
	

<<<<<<< HEAD
../build/message.o: 
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/data_structures/message.cpp -o build/message.o

clean:
	rm -f MAIN_ABP build/*.o bin/*
=======
../build_folder/message.o: 
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/data_structures/message.cpp -o build/message.o

clean:
	rm -f MAIN_ABP *.o *.exe *~
>>>>>>> 03980eb4329f72bfd1c1a0823e5a4351ee3a5bc1
	
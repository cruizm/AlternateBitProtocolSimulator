CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I lib

bin_directroy := $(shell mkdir -p bin)
build_directroy := $(shell mkdir -p build)

all: message.o main.o receiver.o sender.o subnet.o
	$(CC) -g -o bin/ABP build/main.o build/message.o
	$(CC) -g -o bin/RECEIVER_TEST build/receiver.o build/message.o 
	$(CC) -g -o bin/SENDER_TEST build/sender.o build/message.o
	$(CC) -g -o bin/SUBNET_TEST build/subnet.o build/message.o 

main: main.o message.o 
	$(CC) -g -o bin/ABP build/main.o build/message.o 

receiver: receiver.o message.o 
	$(CC) -g -o bin/RECEIVER_TEST build/receiver.o build/message.o 

sender: sender.o message.o 
	$(CC) -g -o bin/SENDER_TEST build/sender.o build/message.o 

subnet: subnet.o message.o 
	$(CC) -g -o bin/SUBNET_TEST build/subnet.o build/message.o 


message.o: 
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/message.cpp -o build/message.o

main.o: src/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/main.cpp -o build/main.o

receiver.o: test/src/receiver/receiver.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/receiver/receiver.cpp -o build/receiver.o

sender.o: test/src/sender/sender.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/sender/sender.cpp -o build/sender.o

subnet.o: test/src/subnet/subnet.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/subnet/subnet.cpp -o build/subnet.o


clean_all:
	rm -f bin/* *.o *~
	-for d in build; do (cd $$d; rm -f *.o *~ ); done

clean_main:
	rm -f bin/ABP *.o *~
	-for d in build; do (cd $$d; rm -f main.o message.o); done

clean_receiver:
	rm -f bin/RECEIVER_TEST *.o *~
	-for d in build; do (cd $$d; rm -f receiver.o message.o); done


clean_sender:
	rm -f bin/SENDER_TEST *.o *~
	-for d in build; do (cd $$d; rm -f sender.o message.o); done

clean_subnet:
	rm -f bin/SUBNET_TEST *.o *~
	-for d in build; do (cd $$d; rm -f subnet.o message.o); done
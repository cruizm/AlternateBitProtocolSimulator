CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I lib/cadmium/include

bin_directroy := $(shell mkdir -p bin)
build_directroy := $(shell mkdir -p build)

all: main.o ../data_structures/message.o
	$(CC) -g -o bin/ABP ../../build/main.o ../../build/message.o
sender_all: sender_main.o ../data_structures/message.o
	$(CC) -g -o bin/SENDER_TEST ../../build/sender_main.o ../../build/message.o
receiver_all: receiver_main.o ../data_structures/message.o
	$(CC) -g -o bin/RECEIVER_TEST ../../build/receiver_main.o ../../build/message.o
subnet_all: subnet_main.o ../data_structures/message.o
	$(CC) -g -o bin/SUBNET_TEST ../../build/subnet_main.o ../../build/message.o
	
main.o: src/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/main.cpp -o build/main.o
sender_main.o: ../../test/src/sender/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) ../../test/src/sender/main.cpp -o build/main.o
receiver_main.o: ../../test/src/receiver/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) ../../test/src/receiver/main.cpp -o build/main.o
subnet_main.o: ../../test/src/subnet/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) ../../test/src/receiver/main.cpp -o build/main.o	

../data_structures/message.o: 
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/message.cpp -o build/message.o
	
clean:
	rm -f ABP *.o *~
	-for d in ../src; do (cd $$d; rm -f *.o *~ ); done
sunder_clean:
	rm -f sender *.o *~
	-for d in ../src; do (cd $$d; rm -f *.o *~ ); done
receiver_clean:
	rm -f receiver *.o *~
	-for d in ../src; do (cd $$d; rm -f *.o *~ ); done	
subnet_clean:
	rm -f subnet *.o *~
	-for d in ../src; do (cd $$d; rm -f *.o *~ ); done
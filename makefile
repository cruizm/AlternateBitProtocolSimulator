CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I lib/cadmium/include

build_folder := mkdir -p build

bin_folder := mkdir -p bin

all: main.o ../build_folder/message.o 
	$(CC) -g -o bin_folder/MAIN_ABP build_folder/top_model_main.o build_folder/message.o
	$(CC) -g -o bin_folder/RECEIVER build_folder/receiver_main.o build_folder/message.o
	$(CC) -g -o bin_folder/SENDER build_folder/sender_main.o build_folder/message.o
	$(CC) -g -o bin_folder/SUBNET build_folder/subnet_main.o build_folder/message.o

main.o: src/top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/top_model/main.cpp -o build_folder/top_model_main.o
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/receiver/main.cpp -o build_folder/receiver_main.o
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/sender/main.cpp -o build_folder/sender_main.o
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test/src/subnet/main.cpp -o build_folder/subnet_main.o
	

../build_folder/message.o: 
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src/data_structures/message.cpp -o build_folder/message.o

clean:
	rm -f MAIN_ABP *.o *~
	-for d in ../data_structures; do (cd $$d; rm -f *.o *~ ); done
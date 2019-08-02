CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../../cadmium/include

all: main.o ../../data_structures/message.o 
	$(CC) -g -o RECEIVER_TEST main.o ../../data_structures/message.o 

main.o: main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) main.cpp -o main.o

../../data_structures/message.o: 
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) ../../data_structures/message.cpp -o ../../data_structures/message.o

clean:
	rm -f RECEIVER_TEST *.o *~
	-for d in ../../data_structures; do (cd $$d; rm -f *.o *~ ); done

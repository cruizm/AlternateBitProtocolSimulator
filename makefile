CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I lib\cadmium\include

$(shell mkdir -p build)
$(shell mkdir -p bin)

all: build\main_receiver.o build\main_sender.o build\main_subnet.o build\main_top_model.o build\message.o
	$(CC) -g -o bin\RECEIVER_TEST build\main_receiver.o build\message.o
	$(CC) -g -o bin\SENDER_TEST build\main_sender.o build\message.o
	$(CC) -g -o bin\SUBNET_TEST build\main_subnet.o build\message.o
	$(CC) -g -o bin\ABP build\main_top_model.o build\message.o


build\main_receiver.o: test\src\receiver\recv_main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test\src\receiver\recv_main.cpp -o build\main_receiver.o

build\main_sender.o: test\src\sender\send_main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test\src\sender\send_main.cpp -o build\main_sender.o
	
build\main_subnet.o: test\src\subnet\sub_main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) test\src\subnet\sub_main.cpp -o build\main_subnet.o
	
build\main_top_model.o: src\top_model\main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src\top_model\main.cpp -o build\main_top_model.o

build\message.o:
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) src\data_structures\message.cpp -o build\message.o
clean:
	rm -rf build *.o *~
	rm -rf bin *.o *~


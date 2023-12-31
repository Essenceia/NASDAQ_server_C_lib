DOC_DIR=doc
RELEASE_DIR=release
INC=inc
RELEASE_NAME=lib_nasdaq_server.a
LIB=-L. -litch
ifndef debug
debug:=
endif

FLAGS = -Wall -Wextra -Wconversion -Wshadow -Wundef -fno-common  -Wno-unused-parameter -Wno-type-limits -fpic
FLAGS += -fpermissive
FLAGS += -std=c++0x
CC = g++ $(if $(debug),-DDEBUG -g)
LD = g++

test : test.o history.o moldudp64.o feed.o server.o libitch.a libeth.a 
	$(LD) -o test -g $^ $(LIB)

test.o : test.c
	$(CC) -c test.c $(FLAGS)

moldudp64.o : moldudp64.c moldudp64.h
	$(CC) -c moldudp64.c $(FLAGS)

history.o: history.cpp history.hpp
	$(CC) -c history.cpp $(FLAGS)

feed.o: feed.cpp feed.hpp
	$(CC) -I$(INC) -c feed.cpp $(FLAGS)

server.o: server.cpp server.hpp
	$(CC) -I$(INC) -c server.cpp $(FLAGS)

lib:
	ar rcs $(RELEASE_NAME) $^ 

valgrind: test
	valgrind --leak-check=full --track-origins=yes ./test	

release: lib
	mkdir -p $(RELEASE_DIR)/$(INC)
	cp $(RELEASE_NAME) $(RELEASE_DIR)/.
	cp *.h $(RELEASE_DIR)/$(INC)

clean:
	-rm -f *.o	
	-rm -f vgcore.*	
	-rm -f test
	-rm -fr $(RELEASE_DIR)

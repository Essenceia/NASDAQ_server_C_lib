DOC_DIR=doc
RELEASE_DIR=release
INC=inc
RELEASE_NAME=lib_nasdaq_server.a

ifndef debug
debug:=
endif

FLAGS = -Wall -Wextra -Wconversion -Wshadow -Wundef -fno-common  -Wno-unused-parameter -Wno-type-limits -fpic
FLAGS += -fpermissive
FLAGS += -std=c++0x
CC = g++ $(if $(debug),-DDEBUG -g)
LD = g++

test : test.o history.o moldudp64.o 
	$(LD) -o test -g $^

test.o : test.c
	$(CC) -c test.c $(FLAGS)

moldudp64.o : moldudp64.c moldudp64.h
	$(CC) -c moldudp64.c $(FLAGS)

history.o: history.cpp history.hpp
	$(CC) -c history.cpp $(FLAGS)

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
	-rm -f *.a	
	-rm -f vgcore.*	
	-rm -f test
	-rm -fr $(RELEASE_DIR)

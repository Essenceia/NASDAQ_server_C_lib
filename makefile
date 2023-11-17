DOC_DIR=doc
RELEASE_DIR=release
INC=inc
RELEASE_NAME=lib_nasdaq_server.a

ifndef debug
debug:=
endif

FLAGS = -std=gnu99 -Wall -Wextra -Wconversion -Wshadow -Wundef -fno-common  -Wno-unused-parameter -Wno-type-limits -fpic
CC = cc $(if $(debug),-DDEBUG -g)
LD = cc

test : test.o 
	$(LD) -o test -g $^

test.o : test.c
	$(CC) -c test.c $(FLAGS)

moldudp64.o : test.c
	$(CC) -c test.c $(FLAGS)

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

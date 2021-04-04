CC		= g++
CFLAGS		= -ansi -pedantic -Wall -Wextra -O3 -g3 -std=c++11

md5test: md5test.o lib/md5.o
	$(CC) $(CFLAGS) -o md5test md5test.o lib/md5.o

md5test.o: md5test.cpp 
	$(CC) $(CFLAGS) -c -o md5test.o md5test.cpp

gen_table: gen_table.o lib/md5.o
	$(CC) $(CFLAGS) -o gen_table gen_table.o lib/md5.o

gen_table.o: gen_table.cpp 
	$(CC) $(CFLAGS) -c -o gen_table.o gen_table.cpp

crack: crack.o lib/md5.o
	$(CC) $(CFLAGS) -o crack crack.o lib/md5.o

crack.o: crack.cpp
	$(CC) $(CFLAGS) -c -o crack.o crack.cpp

lib/md5.o:
	$(CC) $(CFLAGS) -c -o lib/md5.o lib/md5.cpp

	
.PHONY: all
all: md5test gen_table crack

.PHONY: clean
clean:
	rm md5test
	rm md5test.o
	rm gen_table
	rm gen_table.o
	rm crack
	rm crack.o
	rm lib/md5.o

#.PHONY: clean
#clean: 
#	rm keygen
#	rm keygen.o
#	rm lib/sha256/sha256.o

#.PHONY: install
#install: keygen
#	sudo cp keygen $(INSTALL_PATH)/
#	mkdir ~/.keygen
#	chmod 700 ~/.keygen
#
#.PHONY: uninstall
#uninstall:
#	sudo rm $(INSTALL_PATH)/keygen
#	rm -rf ~/.keygen


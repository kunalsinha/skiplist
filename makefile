#makefile to build skiplist program
cc=g++

all : sl

sl : main.o randomlevel.o skipnode.o skiplist.o
	$(cc) main.o randomlevel.o skipnode.o skiplist.o -o skiplist

randomlevel.o : randomlevel.cpp
	$(cc) -c randomlevel.cpp

skipnode.o : skipnode.cpp
	$(cc) -c skipnode.cpp

skiplist.o : skiplist.cpp
	$(cc) -c skiplist.cpp

main.o : main.cpp
	$(cc) -c main.cpp

clean :
	rm -rf *.o

CC=gcc
FLAGS=-Wall -g
OBJECTS_MAIN=StrList.o main.o

all: StrList

StrList: $(OBJECTS_MAIN)
	$(CC) $(FLAGS) -o StrList $(OBJECTS_MAIN)

StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c

main.o: main.c StrList.h
	$(CC) $(FLAGS) -c main.c

.PHONY: clean

clean:
	rm -f *.o StrList

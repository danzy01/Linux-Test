CC=cc
CXX=CC
CCFLAGS= -g -std=c99 -Wall -Wextra

all: main test

%.o : %.c
	$(CC) -c $(CCFLAGS) $<
main: cmak.o mth.o
	$(CC) -o main cmak.o mth.o
test: main
	./main

clean:
	rm -f core *.o main

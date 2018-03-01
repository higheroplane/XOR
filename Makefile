CC = g++
CFLAGS = -c -Wall

all: main

main: main.o nn.o 
	$(CC) -o main main.o nn.o 



nn.o: nn.cpp
	$(CC) $(CFLAGS) -c nn.cpp

clean:
	rm -rf *o 

r: all
	./main

rc: all
	make r
	make clean

p: all
	gnuplot plot.p

rcp: all
	make r
	make p
	make clean





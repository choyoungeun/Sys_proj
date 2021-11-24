all: read pipe2 pipe3

read: read.o
	cc -o read read.c
pipe2: pipe2.o
	cc -o pipe2 pipe2.c
pipe3: pipe3.o
	cc -o pipe3 pipe3.c

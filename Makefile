cp1.o: cp1.c
	gcc -c -o cp1.o cp1.c
utmplib.o: utmplib.c
	gcc -c -o utmplib.o utmplib.c
who3.o: who3.c
	gcc -c -o who3.o who3.c
mywho.o: mywho.c
	gcc -c -o mywho.o mywho.c
clean:
	rm cp1.o utmplib.o who3.o mywho.o

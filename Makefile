ls2.o: ls2.c
	gcc -c -o ls2.o ls2.c
myls.o: myls.c
	gcc -c -o ls2.o ls2.c

ls2: ls2.o
	gcc -o ls2 ls2.o
myls: myls.o
	gcc -o myls myls.o

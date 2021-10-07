all: write0 mywrite

write0: write0.o
	gcc -o write0 write0.o -lpthread
mywrite: mywrite.o
	gcc -o mywrite mywrite.o -lpthread
	
write0.o: write0.c
	gcc -c -o write0.o write0.c
mywrite.o: mywrite.c
	gcc -c -o mywrite.o mywrite.c
 

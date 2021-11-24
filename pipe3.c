/*
file:pipe3.c
author: 2019117779_choyoungeun
datetime:2021-11-25 02:02
description: add variables(pid_A,pid_B,pid_c) and two pipes for three process.
*/

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define oops(m,x) {perror(m); exit(x);}

void main(int ac,char **av)
{
    int thepipe[2];
    int thepipe2[2];
    pid_t pid_A, pid_B, pid_C;

    if(ac != 5){
	fprintf(stderr,"usage: pipe cmd1 cmd2 cmd3 cmd4\n");
	exit(1);
    }

    if(pipe(thepipe)==-1)
	oops("Cannot get a pipe",1);

    if( !(pid_A = fork()) ) {
        close(thepipe[0]);

        if(dup2(thepipe[1],1) == -1)
	    oops("could not redirect stdout",4);
        close(thepipe[1]);
        execlp(av[1], av[1],  NULL);
	oops(av[1],5);
    }

    close(thepipe[1]);

    if(pipe(thepipe2)==-1)
	oops("Cannot get a pipe",1);

    if( !(pid_B = fork()) ) {
        close(thepipe2[0]);

        if(dup2(thepipe[0],0) == -1)
	    oops("could not redirect stdin",3);
        close(thepipe[0]);

        if(dup2(thepipe2[1],1) == -1)
	    oops("could not redirect stdin",4);
        close(thepipe2[1]);

        execlp(av[2], av[2], NULL);
	oops(av[2],4);
   }
   close(thepipe[0]);
   close(thepipe2[1]);

   if( !(pid_C = fork()) ) {
        if(dup2(thepipe2[0],0) == -1)
	    oops("could not redirect stdin",3);
        close(thepipe2[0]);
	
	int pid;
	int fd;

	if((pid = fork())==-1){
    	perror("fork");
    	exit(1);
	}

	if(pid == 0){
    	close(1);
    	fd = creat(av[4],0644);
    	execlp(av[3],av[3],NULL);
    	perror("execlp");
    	exit(1);
	}
	if(pid!=0){
    	wait(NULL);
    	exit(0);
	}

	exit(4);//added.
   }
   close(thepipe2[0]);
   exit(3);//added.
   
   /*
   int pid;
   int fd;

   if((pid = fork())==-1){
       perror("fork");
       exit(1);
   }

   if(pid == 0){
       close(1);
       fd = creat(av[4],0644);
       execlp(av[3],av[3],NULL);
       perror("execlp");
       exit(1);
   }
   if(pid!=0){
       wait(NULL);
       exit(0);
   }*/

}


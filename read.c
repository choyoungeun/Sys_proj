/*
file:read.c
author:2019117779_choyoungeun
datetime:2021-11-25 01:58
description: get three parameter and process attach stdin to file
usage: read cmd1 cmd2
cmd1<cmd2
*/

#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int ac,char **arg){
    int pid;
    int fd;

    if(ac != 3){
	fprintf(stderr,"please put three parameter.\n");
	exit(1);
    }

    if((pid = fork())== -1){
	perror("fork");
	exit(1);
    }

    if(pid == 0){
	close(0);
	fd = open(arg[2], O_RDONLY);
	execlp(arg[1],arg[1],NULL);
	exit(1);
    }
    if(pid!=0){
	wait(NULL);
    }
}

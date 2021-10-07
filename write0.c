/*
file: write0.c
author: 2019117779_choyoungeun
datetime: 2021-10-06 19:35
description: practice command write.(send message to another terminal.)
add include <unistd.h>
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void main(int ac, char *av[]){
    int fd;
    char buf[BUFSIZ];

    if(ac!=2){
	fprintf(stderr,"usage: write0 ttyname\n");
	exit(1);
    }

    fd = open(av[1],O_WRONLY);
    if(fd == -1){
	perror(av[1]);
	exit(1);
    }

    while(fgets(buf,BUFSIZ,stdin)!=NULL)
	if(write(fd,buf,strlen(buf))== -1)
	    break;
    close(fd);
}

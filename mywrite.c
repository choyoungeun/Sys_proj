/*
file: mywrite.c
author: 2019117779_choyoungeun
datetime: 2021-10-06 19:36
description:"Message from user_id at 14:44..." when chatting starts. geteuid() and current time. output "EOF" message when chatting ends.
*/
#define _GNU_SOURCE	
#include <time.h>
#include <pwd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/utsname.h>
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

    fd = open(av[1],O_WRONLY|O_APPEND);//add to append
    if(fd == -1){
	perror(av[1]);
	exit(1);
    }

    //code for message to user id and real time.
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char *s = pwd->pw_name;
    struct utsname uts;
    char computer[256];
    gethostname(computer,255);
    uname(&uts);
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char *s1 = strcat(s,"@");
    char *s2 = strcat(s1,computer);
    char *s3 = strcat(s2," at ");
    char *ck;
    asprintf(&ck,"%d:%d...\n",tm->tm_hour,tm->tm_min);
    char *all = strcat(s3,ck);
    //printf("%s",all);

    char *err = "EOF";

    write(fd,all,strlen(all));
    while(fgets(buf,BUFSIZ,stdin)!=NULL){
	if(write(fd,buf,strlen(buf))== -1)
	     break;
    }
    write(fd,err,strlen(err));
    close(fd);
}

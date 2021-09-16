/*
file:mywho.c
author:2019117779_choyoungeun
datetime:2021-09-15
discription: "showtime" function modification.
*/

#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utmplib.h"

#define SHOWHOST

void showtime(time_t);
void show_info(struct utmp *);

void showtime(time_t timeval){
    /*Using the sftrtime funtion instead of ctime.*/
    char s[50];
    struct tm* tminfo;
    time(&timeval);
    tminfo = localtime(&timeval);
    
    strftime(s,50,"%Y-%m-%d %R",tminfo);
    puts(s);	
}

void show_info(struct utmp *utbufp){
    printf("%-8.8s",utbufp->ut_name);
    printf(" ");
    printf("-8.8%s", utbufp->ut_line);
    printf(" ");
    showtime(utbufp->ut_time);

    #ifndef SHOWHOST
        if(utbufp->ut_host[0]!='\0')
            printf("(%s)",utbufp->ut_host);
    #endif
            printf("\n");
}

int main(){
    struct utmp *utbufp, *umtp_next();

    if(utmp_open(UTMP_FILE) == -1){
	perror(UTMP_FILE);
	exit(1);
    }
    while((utbufp = utmp_next())!=((struct utmp *) NULL))
	show_info(utbufp);
    
    utmp_close();
    return 0;
}


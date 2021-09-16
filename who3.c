/*
file:who3.c
author:2019117779_choyoungeun
datetime:2021-09-15
discription:add to "utmplib.h" and implicit declaration of show_info,showtime function.
Change the order of functions.
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
    char *cp;
    cp = ctime(&timeval);
    printf("%12.12s",cp+4);
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


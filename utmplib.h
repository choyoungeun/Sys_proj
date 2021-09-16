/*
file:utmplib.h
author:2019117779_choyoungeun
datetime:2021-09-15
discription:Declaration of utmplib funtion.
*/

#ifndef UTMPLIB_H
#define UTMPLIB_H

void utmp_close();
int utmp_reload();
struct utmp *utmp_next();
int utmp_open(char *filename);

#endif

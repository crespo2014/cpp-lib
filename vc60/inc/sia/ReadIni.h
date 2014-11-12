//#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * ReadIniItem(char *devuelve,const char *namefile,const char * section,const char *item);
bool WriteIniItem(const char *param,const char *namefile,const char * section,const char *value,const char *borra);
void read_put_crypted_item(char * passwd,char * inifile,char * section,char * item,char * value);
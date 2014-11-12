// test.cpp : Defines the entry point for the console application.
//


#include "ctime.h"

int main(int argc, char* argv[])
{
	char	tmp[200];
	ctime	tm;
	tm.set_format("%d%-%dd%");
	tm.updatetime();

	tm.getc(tmp,sizeof(tmp));
	return 0;
}


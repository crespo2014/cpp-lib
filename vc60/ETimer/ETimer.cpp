// ETimer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

int main(int argc, char* argv[])
{
	long	time;
	int		i;
	printf("Enter time in seconds ");
	scanf("%d",&time);
	for (;;)
	{ 
		printf("Counting %d seconds \n",time);
		Sleep(time*1000);
		printf("\x07\x07\x07");
		i = getchar();
		if (i == 'e') return 0;
	}
	return 0;
}


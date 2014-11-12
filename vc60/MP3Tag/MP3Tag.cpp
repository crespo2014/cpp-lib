// MP3Tag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mp3file.h"

int main(int argc, char* argv[])
{
	Cmp3File	mp3;

	mp3.File_Open("D:\\Users\\Musica\\Alicia Keys - No One.mp3");

	return 0;
	char	tmp[345];
	sprintf(tmp,"%08d",45);
	printf("Hello World!\n");
	return 0;
}


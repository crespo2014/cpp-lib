// FileParse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "logclient.h"
#include "filedriver.h"
#include "utils.h"


BOOL Normalize(char* in,char* out)
{


	char	*st1;
	char	*st2;
	char	str1[10];
	int		num;
	st1 = strrchr(in,'.');
	*st1 = 0;
	st1++;
	strcpy(out,in);
	/*
	out[13] = 0;
	strcat(out,".");
	strcat(out,st1);
	strcat(out,".dat");
	*/
	//strcat(out,st1);
	return true;

	st1 = in;
	while ((*st1 != 0) && ((*st1 < '0') || (*st1 > '9'))) st1++;
	if (*st1 == 0) return false;
	st2 = st1;
	while ((*st2 != 0) && (*st2 >= '0') && (*st2 <= '9')) st2++;
	str1[0] = 0;
	strncat(str1,st1,st2-st1);
	if (strlen(str1) == 3) return false;
	if (sscanf(str1,"%d",&num) != 1) return false;
	st2[-1] = 0;*st1=0;
	sprintf(out,"%s%.3d%s",in,num,st2);
	return true;
}
void NumerateFiles(char* path)
{
	char	old_path[1024];
	char	new_path[1024];
	char	old_file_name[100];
	char	new_file_name[100];
	DWORD	dwr;
	int		i;
	DWORD	dwtmp;
	char	*fext;
	char	*cptr;

	CFileDriver		filedrv;
	WIN32_FIND_DATA	filedata;

	filedrv.SetCurrentDir(path);
	glog._log(LOG_TRACE,"Folder = %s",path);
	Sleep(500);
	dwr = filedrv.FindFile("*");

	i = 0;
	for (;dwr == ERR_OK;dwr = filedrv.NextFile())
	{
		filedrv.GetFileData(&filedata);
		if (filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;			// no entrar en los directorios

		strcpy(old_file_name,filedata.cFileName);

		cptr = old_file_name;
		fext = NULL;
		for (;;)
		{
			cptr = strchr(cptr,'.');
			if (cptr == NULL) break;
			fext = cptr;
			cptr ++;
		}
		if (fext != NULL) {*fext = 0;fext++;} else fext = "";

		sprintf(old_path,"%s\\%s",path,filedata.cFileName);

		// revisar el nombre del fichero
		if (strlen(old_file_name) == 4) 
			if (sscanf(old_file_name,"%d",&dwtmp) == 1)
			{
				glog._log(LOG_TRACE,"Unchange: %s",old_path);
				continue;
			}
		// obtener un nombre disponible
		do 
		{
			sprintf(new_path,"%s\\%.4d.%s",path,i,fext);
			i++;
		} while (gutils.File_IsValid(new_path) == ERR_OK);

		sprintf(new_file_name,"%.4d.%s",i,fext);

		glog._log(LOG_TRACE,"Rename: %20s ---> %20s",filedata.cFileName,new_file_name);
		if (!MoveFile(old_path,new_path))
				glog._log(LOG_TRACE,"Error in %s ---> %s",old_path,new_path);

		//glog._log(LOG_TRACE,"F: %s",next_folder);
		
	}

}
void ListFolder(char* path)
{
	char	old_path[1024];
	char	new_path[1024];
	char	old_file_name[100];
	char	new_file_name[100];
	DWORD	dwr;

	CFileDriver		filedrv;
	WIN32_FIND_DATA	filedata;

	filedrv.SetCurrentDir(path);
	glog._log(LOG_TRACE,"Folder = %s",path);
	Sleep(500);
	dwr = filedrv.FindFile("*");

	while (dwr == ERR_OK)
	{
		filedrv.GetFileData(&filedata);
		sprintf(old_path,"%s\\%s",path,filedata.cFileName);

		if (filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (filedata.cFileName[0] == '.')
			{
				dwr = filedrv.NextFile();continue;
			}
			//glog._log(LOG_TRACE,"D: %s",next_folder);
			
			ListFolder(old_path);
		}
		else
		{
			strcpy(old_file_name,filedata.cFileName);
			if (Normalize(old_file_name,new_file_name))
			{
				glog._log(LOG_TRACE,"Rename: %20s ---> %20s",filedata.cFileName,new_file_name);
				sprintf(new_path,"%s\\%s",path,new_file_name);
				if (!MoveFile(old_path,new_path))
					glog._log(LOG_TRACE,"Error in %s ---> %s",old_path,new_path);

				//Sleep(100);
			}
			/*
			else
				glog._log(LOG_TRACE,"Unchange: %s",filedata.cFileName);
				*/
			
		}
			//glog._log(LOG_TRACE,"F: %s",next_folder);
		dwr = filedrv.NextFile();
	}

}

int main(int argc, char* argv[])
{
	char	st_dir[MAX_PATH];
//	char	*cptr;
	int		i;
	sprintf(st_dir,"%0.20s","tonot");
	GetCurrentDirectory(sizeof(st_dir),st_dir);

	glog.SetConsoleOutput(true);
	glog._log(LOG_ERROR,"Start File Parse App");
	NumerateFiles(st_dir);
	return 0;
	/*
	ListFolder(st_dir);
	printf("Terminating in 5 seg ");
	for (i=0;i<5;i++)
	{
		Sleep(1000);
		printf(".");
	}

	return 0;
	*/

	CFileDriver	filedrv;
	WIN32_FIND_DATA	filedata;

	char	file_name[100];
	DWORD	dwr;

	GetCurrentDirectory(sizeof(st_dir),st_dir);
	filedrv.SetCurrentDir(st_dir);
	dwr = filedrv.FindFile("*");

	while (dwr == ERR_OK)
	{
		filedrv.GetFileData(&filedata);
		if (filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			glog._log(LOG_TRACE,"<DIR> %s",filedata.cFileName);

		}
		else
		//filedrv.GetFileName(SSIZE(file_name));
		glog._log(LOG_TRACE,"    %s",filedata.cFileName);
		dwr = filedrv.NextFile();
	}
	

	return 0;
	// recorriendo ficheros en directorio

}

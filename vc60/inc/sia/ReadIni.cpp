//#include <../stdafx.h>
#include "ReadIni.h"
#include "rc4.h"
#include <list>
//#include "utiles.h"
//#include "def.h"


char * ReadIniItem(char *devuelve,const char *namefile,const char * section,const char *item)
{
	FILE *hfichero;
	bool encontrado=false;
	size_t litem,lcabecera;
	char temporal[520]; //,*devuelve;

	if (namefile==NULL || section==NULL || item==NULL) {
		strcpy(devuelve,"");
		return "";
	}

	lcabecera=strlen(section);
	strcpy(devuelve,"");
	if (NULL!=(hfichero=fopen(namefile,"rt")))	// READ-ONLY as TEXT
	{
		do	// Read the file searching the header
		{
			memset(temporal,0,sizeof(temporal));
			fgets(temporal,sizeof(temporal),hfichero);
			if (feof(hfichero)) break;	// End of File
			if (temporal[0]=='[')
			{
				if (strncmp(&temporal[1],section,lcabecera)==0)
				{
					encontrado=true;
					break;
				}
			}
		}
		while (1);

		if (encontrado==true)
		{	// NOW search the item in the section
			litem=strlen(item);
			do
			{
				memset(temporal,0,sizeof(temporal));
				fgets(temporal,sizeof(temporal),hfichero);
				if (temporal[0]=='[') break;	// next section, so isnt here
				if (strlen(temporal)>=1)
					temporal[strlen(temporal)-1]='\0';
				if (strncmp(temporal,item,litem)==0)	// Ive found the item
				{
					if ((temporal[litem] == ':') && (temporal[litem+1] == ' ')) {
						strcpy(devuelve,&temporal[litem+2]);
						break;
					}
				}
				if (feof(hfichero)) break;	// Finito
			}
			while(1);
		}
		fclose(hfichero);
	}
	return devuelve;
}

bool WriteIniItem(const char *param,const char *namefile,const char * section,const char *value,const char *borra)
{
	FILE *hfichero,*tempfile;
	bool encontrado=false;
	size_t lborra,lcabecera;
	char temporal[4100]; //,*devuelve;
	char temporal_file_name[4100];
	
	temporal_file_name[0] = 0;
	if (namefile==NULL || section==NULL || borra==NULL || param==NULL || value==NULL)
	{
		return false;
	} 
	lcabecera=strlen(section);
	if (NULL!=(hfichero=fopen(namefile,"rt")))	// READ-ONLY as TEXT
	{
		strcpy(temporal_file_name,".LDAPACCESS");
		
		if (NULL==(tempfile=fopen(temporal_file_name,"w+")))
			return false;
		for(;;)	// Read the file searching the header
		{
			memset(temporal,0,4098);
			fgets(temporal,4096,hfichero);
		
			if (feof(hfichero)) break;	// End of File
			fputs(temporal,tempfile);
			if (temporal[0]=='[')
			{
				
				
				if (strncmp((char *)&temporal[1],section,lcabecera)==0)
				{
				
					encontrado=true;
					break;
				}
			}
		}

		if (encontrado==true)
		{	// Put the new value in the section	
//			fprintf(tempfile,"%s={%s}\n",param,value); This is only for crypted values
			
			fprintf(tempfile,"%s: %s\n",param,value);
			// NOW search the item in the section
			lborra=strlen(borra);
			for (;;)
			{
				memset(temporal,0,4098);
				fgets(temporal,4096,hfichero);

				if (temporal[0]=='[')
				{
					fprintf(tempfile,"%s\n",temporal);
					break;	// next section, so isnt here
				}
				if (strlen(temporal)>=1)
					temporal[strlen(temporal)-1]='\0';
				if (strncmp(temporal,borra,lborra)==0)	// Ive found the item
				{
					// Multiline option (search _continue=x) and appends x to devuelve
					memset(temporal,0,4098);
					while (fgets(temporal,4096,hfichero))
					{
						if (strncmp("_continue=",temporal,10)!=0)
						{
							fprintf(tempfile,"%s",temporal);
							break;
						}
						memset(temporal,0,4098);
					}
					break;
				}
				// Unless borrar was found, write it
				fprintf(tempfile,"%s\n",temporal);
				
				if (feof(hfichero)) break;	// Finito
			}
		}
		for(;;)	// Read the file until the end of file
		{
			memset(temporal,0,4098);
			fgets(temporal,4096,hfichero);
			fprintf(tempfile,"%s",temporal);
			if (feof(hfichero)) break;	// End of File
		}

		fclose(hfichero);
		fclose(tempfile);
		if (remove(namefile)<0)
		{
			perror("remove");
			remove(temporal_file_name);
			//free(temporal_file_name);
			return false;
		}
		if (rename(temporal_file_name,namefile)<0)
		{
			perror("rename");
			//free(temporal_file_name);
			return false;
		}
	}
	//¿Y Esto??free(temporal_file_name);
	return true;
}

void read_put_crypted_item(char * passwd,char * inifile,char * section,char * item,char * value)
{
//	rc4 lcrypt("CAST-128");
	rc4 lcrypt(passwd);
	char temp[2048];
	char temp2[2048];
	temp[2] = 0;
	// Rewrite the .ini file with the passwords encrypted if they are not
	// encripted.
	ReadIniItem(temp,inifile,section,item);
	
	if (strlen(temp)>0 && strlen(temp)<2048)
	{
		char * decrypted=NULL;
		char * crypted=NULL;
		
		if (temp[0]=='{')
		{
			// Remove the last }
			strcpy((char *)&temp2,(char *)&temp[1]);
			
			
			
			temp2[strlen(temp2)-1]='\0';
			
			
			decrypted=lcrypt.base64_decrypt(temp2);
			
			
			if (decrypted && strlen(decrypted)>0)
			{
				strcpy(value,decrypted);
			}
			else	// I must crypt the clear text that is not in base64
			{
				strcpy(value,temp);
				crypted=lcrypt.base64_crypt(temp);
				sprintf(temp,"{%s}",crypted);
				WriteIniItem(item,inifile,section,temp,item);
			}
			
			if (decrypted!=NULL) free(decrypted);
			if (crypted!=NULL) free(crypted);
			
		}
		else	// Not Crypted
		{
			
			strcpy(value,temp);
			crypted=lcrypt.base64_crypt(temp);
			temp[0] = 0;
			sprintf(temp,"{%s}",crypted);
			WriteIniItem(item,inifile,section,temp,item);
		}
	}
}


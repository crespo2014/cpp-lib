// csvfiles.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "datafile.h"
#include "time.h"

int Incidencias();
int EstandarDisponibilidad();
DWORD ConvertToTXT();

DWORD		row_index;
struct tm	start_time;
struct tm	end_time;

int main(int argc, char* argv[])
{
	float f=1.0f;
	return ConvertToTXT();
	return Incidencias();
	EstandarDisponibilidad();
	return 0;
}

typedef struct
{
	char	app_type[100];
	char	app_name[100];
	char	cd[100];
	float	duracion_comercial;
	float	duracion_nocomercial;
	SYSTEMTIME	fecha_aper;
	SYSTEMTIME	fecha_fin;
} _DISPONIBILIDAD;

typedef struct
{
	DWORD	id;
	char	area[100];
	char	grupo_eventos[100];
	char	clase[100];
	char	mensaje[200];
	char	hostname[200];
	char	administrator[100];
	struct tm fecha;
	float	duracion;
	DWORD	repeticiones;
	char	severidad[100];
	char	estado[100];
	char	msgcatalogo[100];
	char	subsource[100];
	char	source[100];
	char	server_hndl[100];
	DWORD	date_reception;
	DWORD	event_hndl;
	
} _EVENTOS;

int GetDayEnglish(char* sday)
{
	strupr(sday);
	if (strcmp(sday,"SUN") == 0) return 1;
	if (strcmp(sday,"MON") == 0) return 2;
	if (strcmp(sday,"TUE") == 0) return 3;
	if (strcmp(sday,"WED") == 0) return 4;
	if (strcmp(sday,"THU") == 0) return 5;
	if (strcmp(sday,"FRI") == 0) return 6;
	if (strcmp(sday,"SAT") == 0) return 7;
	return 0;
}
int GetMonthSpanish(char* smonth)
{
	strupr(smonth);
	if (strcmp(smonth,"ENE") == 0) return 1;
	if (strcmp(smonth,"FEB") == 0) return 2;
	if (strcmp(smonth,"MAR") == 0) return 3;
	if (strcmp(smonth,"ABR") == 0) return 4;
	if (strcmp(smonth,"MAY") == 0) return 5;
	if (strcmp(smonth,"JUN") == 0) return 6;
	if (strcmp(smonth,"JUL") == 0) return 7;
	if (strcmp(smonth,"AGO") == 0) return 8;
	if (strcmp(smonth,"SEP") == 0) return 9;
	if (strcmp(smonth,"OCT") == 0) return 10;
	if (strcmp(smonth,"NOV") == 0) return 11;
	if (strcmp(smonth,"DIC") == 0) return 12;
	return 0;
}

int GetMonthEnglish(char* smonth)
{
	strupr(smonth);
	if (strcmp(smonth,"ENE") == 0) return 1;
	if (strcmp(smonth,"FEB") == 0) return 2;
	if (strcmp(smonth,"MAR") == 0) return 3;
	if (strcmp(smonth,"APR") == 0) return 4;
	if (strcmp(smonth,"MAY") == 0) return 5;
	if (strcmp(smonth,"JUN") == 0) return 6;
	if (strcmp(smonth,"JUL") == 0) return 7;
	if (strcmp(smonth,"AGO") == 0) return 8;
	if (strcmp(smonth,"SEP") == 0) return 9;
	if (strcmp(smonth,"OCT") == 0) return 10;
	if (strcmp(smonth,"NOV") == 0) return 11;
	if (strcmp(smonth,"DIC") == 0) return 12;
	return 0;
}

int GetFecha3(char* strfecha, struct tm* fecha)
{
	// formato 02/04/2007 00:00:00
	int			ir;
	struct tm	time;

	if (strfecha[0] == 0) return ERR_FATAL;
	ir = sscanf(strfecha,"%d/%d/%d %d:%d:%d",&time.tm_mday,&time.tm_mon,&time.tm_year,&time.tm_hour,&time.tm_min,&time.tm_sec);
	if (ir != 6) return ERR_FATAL;
	time.tm_wday = -1;
	time.tm_yday = -1;
	*fecha = time;

	return ERR_OK;
}
int GetFecha2(char* strfecha, SYSTEMTIME* fecha)
{
	// formato Apr 02, 2007 00:00
	char*	cptr;
	char	mes[10];
	char	day[10];
	char	year[10];
	int		ir;
	mes[0] = 0;
	
	memset(fecha,0,sizeof(SYSTEMTIME));
	fecha->wYear = 2007;

	cptr = strstr(strfecha,",");
	if (cptr != NULL)
	{
		ir = sscanf(strfecha,"%s %d, %d %d:%d",mes,&fecha->wDay,&fecha->wYear,&fecha->wHour,&fecha->wMinute);
		ir++;
	}
	else
	{
		ir = sscanf(strfecha,"%s %d %d:%d:%d %s",mes,&fecha->wDay,&fecha->wHour,&fecha->wMinute,&fecha->wSecond,year);
		if (ir == 1) // esta puesto el dia de la semana
			ir = sscanf(strfecha,"%*s %s %d %d:%d:%d %s",mes,&fecha->wDay,&fecha->wHour,&fecha->wMinute,&fecha->wSecond,year);
			
		if (ir == 6)	//revisar el año
		{
			if (sscanf(year,"%d",&fecha->wYear) == 0)	// no se proceso el año
			{
				strupr(year);
				if (strcmp(year,"PM") == 0) fecha->wHour += 12;
				else
					if (strcmp(year,"AM") != 0) ir = 0;
			}
		}
		if (ir == 5) ir = 6; // no hay año ni am, pm
	}
	if (ir != 6) return ERR_FATAL;
	fecha->wMonth = GetMonthEnglish(mes);
	if (fecha->wMonth == 0) return ERR_FATAL;
	return ERR_OK;
}

int GetFecha(char* strfecha, SYSTEMTIME* fecha)
{
	char	mes[30];
	int		ir;
	memset(fecha,0,sizeof(SYSTEMTIME));
	mes[0] = 0;
	ir = sscanf(strfecha,"%d/%[^/]/%d %d:%d:%d",&fecha->wDay,mes,&fecha->wYear,&fecha->wHour,&fecha->wMinute,&fecha->wSecond);
	if (ir != 6) 
	{
		return ERR_FATAL;
		glog.AddString("failed to process ->",strfecha);
		return ERR_FATAL;
	}
	strupr(mes);
	for (;;)
	{
		if (strcmp(mes,"ENE") == 0) {fecha->wMonth = 1;break;}
		if (strcmp(mes,"FEB") == 0) {fecha->wMonth = 2;break;}
		if (strcmp(mes,"MAR") == 0) {fecha->wMonth = 3;break;}
		if (strcmp(mes,"ABR") == 0) {fecha->wMonth = 4;break;}
		if (strcmp(mes,"MAY") == 0) {fecha->wMonth = 5;break;}
		if (strcmp(mes,"JUN") == 0) {fecha->wMonth = 6;break;}
		if (strcmp(mes,"JUL") == 0) {fecha->wMonth = 7;break;}
		if (strcmp(mes,"AGO") == 0) {fecha->wMonth = 8;break;}
		if (strcmp(mes,"SEP") == 0) {fecha->wMonth = 9;break;}
		if (strcmp(mes,"OCT") == 0) {fecha->wMonth = 10;break;}
		if (strcmp(mes,"NOV") == 0) {fecha->wMonth = 11;break;}
		if (strcmp(mes,"DIC") == 0) {fecha->wMonth = 12;break;}
		glog.AddString("Mes no valido en fecha ->",strfecha);
		return ERR_FATAL;
	}
	return ERR_OK;
}

int GetFloat(char* fstr,float* pfloat)
{
	char* cptr;
	int	ir;
	// cambiar la , por el
	cptr = strstr(fstr,",");
	if (cptr != NULL) *cptr = '.';
	ir = sscanf(fstr,"%f",pfloat);
	if (ir == 1) return ERR_OK;
	return ERR_FATAL;
}

int GetDisponibilidadData(_DISPONIBILIDAD* pdisp,_datafile*	pdata_file)
{
	return ERR_OK;
}

int IncidenciaAddToFile(FILE* pfile,_DISPONIBILIDAD* pdisp)
{
	fprintf(pfile,"%s\x09%s\x09%s\x09%d/%d/%d %d:%d:%d\x09%d/%d/%d %d:%d:%d\x09%f\x09%f\x0d",
		pdisp->app_type,pdisp->app_name,pdisp->cd,
		pdisp->fecha_aper.wDay,pdisp->fecha_aper.wMonth,pdisp->fecha_aper.wYear,pdisp->fecha_aper.wHour,pdisp->fecha_aper.wMinute,pdisp->fecha_aper.wSecond,
		pdisp->fecha_fin.wDay,pdisp->fecha_fin.wMonth,pdisp->fecha_fin.wYear,pdisp->fecha_fin.wHour,pdisp->fecha_fin.wMinute,pdisp->fecha_fin.wSecond,
		pdisp->duracion_comercial,pdisp->duracion_nocomercial);
	return ERR_OK;
}

int EstandarDisponibilidad()
{
	float f=1.0f;

	_datafile	data_file;
	_DISPONIBILIDAD	disp;
	_DISPONIBILIDAD	disp_old;
	int	ir;
	int ir1;
	DWORD	count = 0;
	FILE*	outfile;


	InitDataFile(&data_file);
	data_file.file_handle = fopen("D:\\Reports BO\\Excel disponibilidad\\EstandarDisponibilidad_Alpha2.txt","rb");
	outfile = fopen("C:\\out.csv","wb");
	data_file.colum_delimiter = 9;
	data_file.row_delimiter = 0;
	GetLine(&data_file);	// nombre del informe
	GetLine(&data_file);	// linea con nombre de columnas

	for (;;)
	{
		if (ReadRowData(&data_file) == 0) break;
		count ++;
		// pasar datos a la estructura
		if (data_file.value_count != 7) 
		{
			glog.AddLong("",count,TYP_LOG,false);
			glog.Error(data_file.currline);
			continue;
		}
		
		strcpy(disp.app_type,data_file.values[0]);
		strcpy(disp.app_name,data_file.values[1]);
		strcpy(disp.cd,data_file.values[2]);
		ir = GetFecha(data_file.values[3],&disp.fecha_aper);
		ir1 = GetFecha(data_file.values[4],&disp.fecha_fin);
		if (ir1 != ERR_OK)
		{
			disp.fecha_fin.wYear = 2007;
			disp.fecha_fin.wMonth = 4;
			disp.fecha_fin.wDayOfWeek = 1;
			disp.fecha_fin.wDay = 30;
			disp.fecha_fin.wHour = 23;
			disp.fecha_fin.wMinute = 59;
			disp.fecha_fin.wSecond = 59;
			disp.fecha_fin.wMilliseconds = 0;
		}
		if (ir != ERR_OK)
		{
			glog.AddLong("Line : ",count,TYP_LOG,false);
			glog.Error(data_file.values[3]);
			continue;
		}
		ir = GetFloat(data_file.values[5],&disp.duracion_comercial);
		if ( ir != ERR_OK) 
		{
			glog.AddLong("Line : ",count,TYP_LOG,false);
			glog.Error(data_file.values[5]);
			continue;
		}
		ir = GetFloat(data_file.values[6],&disp.duracion_nocomercial);
		if ( ir != ERR_OK) 
		{
			glog.AddLong("Line : ",count,TYP_LOG,false);
			glog.Error(data_file.values[6]);
			continue;
		}
		if (disp_old.app_name[0]  == 0)	
		{
			disp_old = disp; continue;
		}
		// revisar las fechas
		if (strcmp(disp_old.app_name,disp.app_name) != 0)
		{
			IncidenciaAddToFile(outfile,&disp_old);
			disp_old = disp;
			continue;
		}
		
	}
	glog.AddLong("Lines Procesed ... ",count);
	return 0;
}

#define INCIDENCIAS_MES	4

int EventoSaveToFile(_EVENTOS *eventos,FILE*	poutfile)
{
	fprintf(poutfile,"%d&%s&%s&\
					%s&%s&%s&\
					%s&%s&\
					%d/%d/%d %d:%d:%d&\
					%f&%d&%s&\
					%s&%s&%s&\
					%s&%s&%d&\
					%d\n",
		eventos->id,
		eventos->area+3,
		eventos->area,
		eventos->grupo_eventos,
		eventos->clase,
		eventos->mensaje,
		eventos->hostname,
		eventos->administrator,
		eventos->fecha.tm_mday,eventos->fecha.tm_mon,eventos->fecha.tm_year,eventos->fecha.tm_hour,eventos->fecha.tm_min,eventos->fecha.tm_sec,
		eventos->duracion,
		eventos->repeticiones,
		eventos->severidad,
		eventos->estado,
		eventos->msgcatalogo,
		eventos->subsource,
		eventos->source,
		eventos->server_hndl,
		eventos->date_reception,
		eventos->event_hndl);
	return ERR_OK;
}

int IncidenciaGetData(_EVENTOS *eventos,_datafile* pdata_file)
{
#define AREA_INDEX 0
#define GRP_EVEN	1
#define CLASE		2
#define MENSAJE		3
#define HOSTNAME	4
#define ADMIN		5
#define FECHA_INDEX	6
#define DURACION	7
#define REPET		8
#define	SEVER		9
#define ESTADO		10
#define MSGCAT		11
#define SUBSOURCE	12
#define	SOURCE		13
#define	SERV_HND	14
#define	DATE_RECEP	15
#define EVENT_HND	16
#define DATA_COUNT	17

	int	ir;
	char	err_msg[100];
	// validacion inicial
	if (pdata_file->value_count < DATA_COUNT)
	{
		sprintf(err_msg,"Row : %d DataCount = %d is Invalid",row_index,pdata_file->value_count);
		glog.Error(err_msg);
		return ERR_FATAL;
	}
	if (pdata_file->values[FECHA_INDEX][0] == 0) 
	{
		sprintf(err_msg,"Row : %d Date is empty",row_index);
		glog.Error(err_msg);
		return ERR_FATAL;
	}
	eventos->date_reception = 1;
	eventos->event_hndl = 1;

	strcpy(eventos->area,pdata_file->values[AREA_INDEX]);
	strcpy(eventos->grupo_eventos,pdata_file->values[GRP_EVEN]);
	strcpy(eventos->clase,pdata_file->values[CLASE]);
	strcpy(eventos->mensaje,pdata_file->values[MENSAJE]);
	strcpy(eventos->hostname,pdata_file->values[HOSTNAME]);
	strcpy(eventos->administrator,pdata_file->values[ADMIN]);
	sscanf(pdata_file->values[DURACION],"%f",&eventos->duracion);
	sscanf(pdata_file->values[REPET],"%d",&eventos->repeticiones);
	strcpy(eventos->severidad,pdata_file->values[SEVER]);
	strcpy(eventos->estado,pdata_file->values[ESTADO]);
	strcpy(eventos->msgcatalogo,pdata_file->values[MSGCAT]);
	strcpy(eventos->subsource,pdata_file->values[SUBSOURCE]);
	strcpy(eventos->source,pdata_file->values[SOURCE]);
	strcpy(eventos->server_hndl,pdata_file->values[SERV_HND]);
	sscanf(pdata_file->values[DATE_RECEP],"%d",&eventos->date_reception);
	sscanf(pdata_file->values[EVENT_HND],"%d",&eventos->event_hndl);

	ir = GetFecha3(pdata_file->values[FECHA_INDEX],&eventos->fecha);
	if (ir != ERR_OK)
	{
		sprintf(err_msg,"Row : %d Date is invalid = %s",row_index,pdata_file->values[FECHA_INDEX]);
		glog.Error(err_msg);
		return ERR_FATAL;
	}

	return ERR_OK;
}

int IsTecnologia(char* pstr)
{
	strupr(pstr);
	if (strcmp(pstr,"GR-APLICACIONES") == 0) return ERR_OK;
	

	return ERR_FATAL;
}

int Incidencias()
{
#define FILE1 "D:\\Users\\Lester\\Reports BO\\DATOS excel\\csv\\csvdump.csv"
#define FILE2 "D:\\Reports BO\\DATOS excel\\csv\\mayo.csv"
#define OUTFILE "c:\\mayo.csv"

	float f=1.0f;

	_datafile	data_file;
	_EVENTOS	eventos;
	FILE*		outfile;

	int	ir;
	int ir1;

	InitDataFile(&data_file);
	data_file.file_handle = fopen(FILE2,"rb");
	
	if (data_file.file_handle == NULL)
	{
		glog.AddString("Failed to open file ",FILE2);
		return ERR_FATAL;
	}
	outfile = fopen(OUTFILE,"wb");
	if (outfile == NULL)
	{
		glog.AddString("Failed to open file ",OUTFILE);
		return ERR_FATAL;
	}

	data_file.colum_delimiter = '&';
	data_file.row_delimiter = 10;
	row_index = 1;
	GetLine(&data_file);	// linea con nombre de columnas
	fprintf(outfile,"ID&TECNOLOGIA&");
	fwrite(data_file.currline,strlen(data_file.currline),1,outfile);
	fprintf(outfile,"\n");
	for (;;row_index ++)
	{
		if (ReadRowData(&data_file) == 0) break;
		// revisar si los datos estan correctos en el informe
		if (data_file.value_count < DATA_COUNT)
		{ 
			glog.AddString("Missing data in ->",data_file.currline);
			continue;
		}
		if (data_file.values[FECHA_INDEX][0] == 0) 
		{
			glog.AddString("Date is empty in ->",data_file.currline);
			continue;
		}
		ir = GetFecha3(data_file.values[FECHA_INDEX],&eventos.fecha);
		if (ir != ERR_OK)
		{
			glog.AddString("Invalid date format in ->",data_file.currline);
			continue;
		}
		/*
		if (eventos.fecha.tm_mon != 4) 
		{
			glog.AddString("Invalid month in ->",data_file.currline);
			continue;
		}
		*/
		fprintf(outfile,"%d&%s&",row_index,data_file.values[0]+3);
		fwrite(data_file.currline,strlen(data_file.currline),1,outfile);
		fprintf(outfile,"\n");

		/*
		ir = IncidenciaGetData(&eventos,&data_file);
		if (ir != ERR_OK) 
		{
			glog.Error(data_file.currline);
			continue;
		}
		*/
	}
	fclose(data_file.file_handle);
	fclose(outfile);

	return ERR_OK;
}

// en str remplaza los caracteres look por replace y oloca neutral si ya hay replace
void ChangeChar(char* str,char look,char replace,char neutral)
{
	char*	cptr;
	cptr = strchr(str,replace);
	while (cptr != NULL)
	{
		cptr[0]= neutral;
		cptr = strchr(cptr,replace);
	}
	cptr = strchr(str,look);
	while (cptr != NULL)
	{
		cptr[0]= replace;
		cptr = strchr(cptr,look);
	}

}

// cambiar el caracter delimitador por 9
#define IN_FILE "c:\\mayo.csv"
#define ERR_FILE "c:\\err.txt"
#define OUT_FILE "c:\\out1.txt"

DWORD ConvertToTXT()
{
	float f=1.0f;

	_datafile	data_file;
	_EVENTOS	eventos;
	FILE*		outfile;
	FILE*		errfile;

	int	ir;
	int ir1;

	InitDataFile(&data_file);
	data_file.file_handle = fopen(IN_FILE,"rb");
	
	if (data_file.file_handle == NULL)
	{
		glog.AddString("Failed to open file ",FILE2);
		return ERR_FATAL;
	}

	outfile = fopen(OUT_FILE,"wb");
	if (outfile == NULL)
	{
		glog.AddString("Failed to open file ",OUTFILE);
		return ERR_FATAL;
	}

	errfile = fopen(ERR_FILE,"wb");
	if (outfile == NULL)
	{
		glog.AddString("Failed to open file ",ERR_FILE);
		return ERR_FATAL;
	}

	data_file.colum_delimiter = '&';
	data_file.row_delimiter = 10;
	row_index = 1;
	GetLine(&data_file);	// linea con nombre de columnas
	fprintf(outfile,"IS\x09");
	ChangeChar(data_file.currline,'&',9,'*');
	fwrite(data_file.currline,strlen(data_file.currline),1,outfile);
	fprintf(outfile,"\r\n");
	for (;row_index<2;row_index ++)
	{
		if (ReadRowData(&data_file) == 0) break;
		// revisar si los datos estan correctos en el informe
		if (data_file.value_count < DATA_COUNT)
		{ 
			glog.AddString("Missing data in ->",data_file.currline);
			fprintf(errfile,"Missing data in -> %s\r\n",data_file.currline);
			continue;
		}
		if (data_file.values[FECHA_INDEX][0] == 0) 
		{
			glog.AddString("Date is empty in ->",data_file.currline);
			fprintf(errfile,"Date is empty in -> %s\r\n",data_file.currline);
			continue;
		}
		ir = GetFecha3(data_file.values[FECHA_INDEX],&eventos.fecha);
		if (ir != ERR_OK)
		{
			glog.AddString("Invalid date format in ->",data_file.currline);
			fprintf(errfile,"Invalid date format in -> %s\r\n",data_file.currline);
			continue;
		}
		/*
		if (eventos.fecha.tm_mon != 4) 
		{
			glog.AddString("Invalid month in ->",data_file.currline);
			continue;
		}
		*/
		fprintf(outfile,"%d\x09",row_index,data_file.values[0]+3);
		ChangeChar(data_file.currline,'&',9,'*');
		fwrite(data_file.currline,strlen(data_file.currline),1,outfile);
		fprintf(outfile,"\r\n");

		/*
		ir = IncidenciaGetData(&eventos,&data_file);
		if (ir != ERR_OK) 
		{
			glog.Error(data_file.currline);
			continue;
		}
		*/
	}
	fclose(data_file.file_handle);
	fclose(outfile);
	fclose(errfile);
	return ERR_OK;	
}




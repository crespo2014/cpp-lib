// logonclient.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "LogonTrans.h" 
#include "inifile.h"
#include "stdio.h"
#include "datafile.h"
#include "logclient.h"

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
	char	area[100];
	char	grupo_eventos[100];
	char	clase[100];
	char	mensaje[200];
	char	hostname[200];
	char	administrator[100];
	SYSTEMTIME	fecha;
	float	duracion;
	DWORD	repeticiones;
	char	severidad[100];
	char	estado[100];
	char	msgcatalogo[100];
	char	subsource[100];
	char	source[100];
	//char	
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

int IncidenciaGetData(_EVENTOS *eventos,_datafile* pdata_file)
{
	int	ir;
	if (pdata_file->value_count != 13) return ERR_FATAL;
	ir = GetFecha2(pdata_file->values[5],&eventos->fecha);
	if (ir != ERR_OK)
	{
		glog.Error(pdata_file->values[5]);
		return ir;
	}

	return ERR_OK;
}

int Incidencias()
{
	float f=1.0f;

	_datafile	data_file;
	_EVENTOS	eventos;

	int	ir;
	int ir1;
	DWORD	count = 0;

	InitDataFile(&data_file);
	data_file.file_handle = fopen("D:\\Reports BO\\DATOS excel\\csv\\my.csv","rb");
	if (data_file.file_handle == NULL)
	{
		glog.Error("Failed to open file ");
		return ERR_FATAL;
	}
	data_file.colum_delimiter = '#';
	data_file.row_delimiter = 10;
	GetLine(&data_file);	// linea con nombre de columnas
	for (;;count ++)
	{
		if (ReadRowData(&data_file) == 0) break;
		ir = IncidenciaGetData(&eventos,&data_file);
		if (ir != ERR_OK) 
		{
			glog.Error(data_file.currline);
			continue;
		}
	}
	fclose(data_file.file_handle);

	return ERR_OK;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	float f=1.0f;
	
	return Incidencias();
	EstandarDisponibilidad();
	return 0;
}




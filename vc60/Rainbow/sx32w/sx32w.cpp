// sx32w.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "sx32w.h"

// Globales
RNBKEY	RnbKey;
HMODULE hRnbDll = NULL;
RB_SPRO_APIPACKET Packet;

//Banderas utilizadas para indicar validez de variables

// Funciones de rainbown
_RNBOsproFindFirstUnit*	RNBFindFirstUnit;
_RNBOsproQuery*			RNBQuery;
_RNBOsproActivate*		RNBActivate;
_RNBOsproDecrement*		RNBDecrement;
_RNBOsproExtendeRead*	RNBExtendeRead;
_RNBOsproFindNextUnit*	RNBFindNextUnit;
_RNBOsproFormatPacket*	RNBFormatPacket;
_RNBOsproGetVersion*	RNBGetVersion;
_RNBOsproInitialize*	RNBInitialize;
_RNBOsproOverWrite*		RNBOverWrite;
_RNBOsproRead*			RNBRead;
_RNBOsproWrite*			RNBWrite;

BOOL LoadRnbDLL()
{
	char	filename[MAX_PATH];
	UINT	ur;
	ur = GetSystemDirectory(filename,MAX_PATH);
	if (ur == 0) return FALSE;
	strcat(filename,"\\sx32w.dll");
	hRnbDll = LoadLibrary(filename);
	if (hRnbDll == NULL) return false;
	// Tomar direccion de los metodos de rainbown
	RNBFindFirstUnit	= (_RNBOsproFindFirstUnit*)GetProcAddress(hRnbDll,"RNBOsproFindFirstUnit");
	RNBQuery			= (_RNBOsproQuery*)GetProcAddress(hRnbDll,"RNBOsproQuery");
	RNBActivate			= (_RNBOsproActivate*)GetProcAddress(hRnbDll,"RNBOsproActivate");
	RNBDecrement		= (_RNBOsproDecrement*)GetProcAddress(hRnbDll,"RNBOsproDecrement");
	RNBExtendeRead		= (_RNBOsproExtendeRead*)GetProcAddress(hRnbDll,"RNBOsproExtendeRead");
	RNBFindNextUnit		= (_RNBOsproFindNextUnit*)GetProcAddress(hRnbDll,"RNBOsproFindNextUnit");
	RNBFormatPacket		= (_RNBOsproFormatPacket*)GetProcAddress(hRnbDll,"RNBOsproFormatPacket");
	RNBGetVersion		= (_RNBOsproGetVersion*)GetProcAddress(hRnbDll,"RNBOsproGetVersion");
	RNBInitialize		= (_RNBOsproInitialize*)GetProcAddress(hRnbDll,"RNBOsproInitialize");
	RNBOverWrite		= (_RNBOsproOverWrite*)GetProcAddress(hRnbDll,"RNBOsproOverWrite");
	RNBRead				= (_RNBOsproRead*)GetProcAddress(hRnbDll,"RNBOsproRead");
	RNBWrite			= (_RNBOsproWrite*)GetProcAddress(hRnbDll,"RNBOsproWrite");
	return true;
}

// Buscar fichero para la tecla especifica
BOOL LoadRnbKey(WORD KeyID)
{
	char	filename[20];
	HANDLE	hFile;
	BOOL	br;
	sprintf(filename,"Rnb%x.bin",KeyID);
	hFile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	// cargar datos del fichero a las variables
	DWORD BytesRead;
	br = ReadFile(hFile,&RnbKey,sizeof(RnbKey),&BytesRead,NULL);
	CloseHandle(hFile);
	if (BytesRead != sizeof(RnbKey)||(br == false))
	{
		RnbKey.OnKeyID = false;
		return false;
	}
	return true;
}

BOOL SaveRnbKey()
{
	if (!RnbKey.OnKeyID) return false;
	char	filename[20];
	HANDLE	hFile;
	BOOL	br;
	sprintf(filename,"Rnb%x.bin",RnbKey.KeyID);
	hFile = CreateFile(filename,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	// cargar datos del fichero a las variables
	DWORD BytesWriten;
	br = WriteFile(hFile,&RnbKey,sizeof(RnbKey),&BytesWriten,NULL);
	CloseHandle(hFile);
	if (BytesWriten != sizeof(RnbKey) || (br == false))
	{
		return false;
	}
	return true;
}

WORD RequestRnbKey(WORD KeyID)
{
	int		ir;
	WORD	wr;
	char	str[200];
	if (!hRnbDll) 
	{
		if (!LoadRnbDLL()) return 3;
	}
	sprintf(str,"Introduzca la llave con ID %X y pulsa OK",KeyID);
	wr = RNBFormatPacket(Packet,sizeof(Packet));
	wr = RNBInitialize(Packet);
	for (;;)
	{
		wr = RNBFindFirstUnit(Packet,KeyID);
		if (wr != 3) return wr;		// Ocurrio un error diferente de no encontrada
		ir = MessageBox(NULL,str,"Rainbow Hack dll",MB_OKCANCEL|MB_TASKMODAL);
		if (ir == IDCANCEL) return 3;	// No hay llave
	}
	return 3;						// No se encontro la llave
}

 bool InitializeKey()
 {
	 RnbKey.OnKeyID = false;
	//Inicialización de las banderas de las celdas
	int i;
	for (i=0;i<64;i++)
	{
		RnbKey.cell[i].OnValidAccesCode=false;
		RnbKey.cell[i].OnValidActivePassword1=false;
		RnbKey.cell[i].OnValidActivePassword2=false;
		RnbKey.cell[i].OnValidData=false;
		RnbKey.cell[i].OnValidOverWritePassword1=false;
		RnbKey.cell[i].OnValidOverWritePassword2=false;
		RnbKey.cell[i].OnValidWritePassword=false;
	}
	return true;
 }

BOOL APIENTRY DllMain( HANDLE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{	
				InitializeKey();
				break;
			}
		case DLL_THREAD_ATTACH: break;
		case DLL_THREAD_DETACH: break;
		case DLL_PROCESS_DETACH:
			{
				SaveRnbKey();
				if (hRnbDll)
					FreeLibrary(hRnbDll);
				break;
			}
    }
    return TRUE;
}

DLL_API WORD _stdcall RNBOsproFindFirstUnit(void* packet,WORD developerID )
{
	WORD	wr;
	if (RnbKey.OnKeyID && RnbKey.KeyID == developerID) return 0;	// se solicito la llave en uso
	if (LoadRnbKey(developerID)) return 0;	// Ya se cuenta con esa llave
	wr = RequestRnbKey(developerID);		// No se tiene dicha llave
	if (wr == 0) 
	{
		RnbKey.OnKeyID = true;
		RnbKey.KeyID = developerID;
	}
	return wr;
}

DLL_API WORD _stdcall RNBOsproFindNextUnit(void* packet) {return 3;}

DLL_API WORD _stdcall RNBOsproFormatPacket(void* thePacket,DWORD thePacketSize )
{
	return 0;
}

DLL_API WORD _stdcall RNBOsproGetVersion(void* thePacket,WORD* majVer,WORD* minVer,WORD* rev,WORD* osDrvrType)
{
	return 0;
	return RNBGetVersion(Packet,majVer,minVer,rev,osDrvrType);
	WORD RetVal=RequestRnbKey(RnbKey.KeyID);
	 if (!RetVal)
	 {
		RetVal=RNBGetVersion(Packet,majVer,minVer,rev,osDrvrType);
		return RetVal;//retorno el valor de RNBGetVersion
	 }
	 return RetVal;//retorna el valor de RequestRnbKey
}

DLL_API WORD _stdcall RNBOsproInitialize(void* packet)
{
	return 0;
}


DLL_API WORD _stdcall RNBOsproRead(void* packet,WORD address,WORD* data)
{
	if (address > 63) return 5;
	if(RnbKey.cell[address].OnValidData)
	{
		 *data=RnbKey.cell[address].Data;
		 return 0;
	}
	WORD wr = RequestRnbKey(RnbKey.KeyID);
	if (wr != 0) return wr;
	wr = RNBRead(Packet,address,data);
	if (wr == 0)
	{
		RnbKey.cell[address].Data=*data;
		RnbKey.cell[address].OnValidData=true;
	}
	return wr;
}


DLL_API WORD _stdcall RNBOsproWrite(void* packet,WORD writePassword,WORD address,WORD data,BYTE accessCode)
{
	if (address > 63) return 5;
	if ((RnbKey.cell[address].OnValidData)&&
		(RnbKey.cell[address].OnValidAccesCode)&&
		(RnbKey.cell[address].OnValidWritePassword))
	{
		if ((RnbKey.cell[address].AccesCode == accessCode)&&
			(RnbKey.cell[address].WritePassword == writePassword))
		{
			RnbKey.cell[address].Data = data;
			return 0;
		}
		return 6;
	}
	WORD wr = RequestRnbKey(RnbKey.KeyID);
	if (wr != 0) return wr;
	wr = RNBWrite(Packet,writePassword,address,data,accessCode);
	if (wr == 0)
	{
		RnbKey.cell[address].AccesCode=accessCode;
		RnbKey.cell[address].WritePassword=writePassword;
		RnbKey.cell[address].Data=data;
		RnbKey.cell[address].OnValidAccesCode=true;
		RnbKey.cell[address].OnValidWritePassword=true;
		RnbKey.cell[address].OnValidData=true;
	}
	return wr;
}

DLL_API WORD _stdcall RNBOsproOverwrite(void* packet,WORD writePassword,WORD overwritePassword1,WORD overwritePassword2,WORD address,WORD data,BYTE accessCode)
{
	if (address > 63) return 5;
	if ((RnbKey.cell[address].OnValidWritePassword)&&
		(RnbKey.cell[address].OnValidOverWritePassword1)&&
		(RnbKey.cell[address].OnValidOverWritePassword2)&&
		(RnbKey.cell[address].OnValidData)&&
		(RnbKey.cell[address].OnValidAccesCode))
		{
			if ((RnbKey.cell[address].AccesCode == accessCode) &&
				(RnbKey.cell[address].OverWritePassword1 == overwritePassword1)&&
				(RnbKey.cell[address].OverWritePassword2 == overwritePassword2)&&
				(RnbKey.cell[address].WritePassword == writePassword))
			{
				RnbKey.cell[address].Data=data;
				return 0;
			}
			return 6;
		}
	WORD wr = RequestRnbKey(RnbKey.KeyID);
	if (wr != 0) return wr;
	wr = RNBOverWrite(Packet,writePassword,overwritePassword1,overwritePassword2,address,data,accessCode);
	if (wr == 0)
	{
		RnbKey.cell[address].AccesCode=accessCode;
		RnbKey.cell[address].WritePassword=writePassword;
		RnbKey.cell[address].Data=data;
		RnbKey.cell[address].OverWritePassword1=overwritePassword1;
		RnbKey.cell[address].OverWritePassword2=overwritePassword2;
		RnbKey.cell[address].OnValidAccesCode=true;
		RnbKey.cell[address].OnValidWritePassword=true;
		RnbKey.cell[address].OnValidData=true;
		RnbKey.cell[address].OnValidOverWritePassword1=true;
		RnbKey.cell[address].OnValidOverWritePassword2=true;
	}
	return wr;
}

DLL_API WORD _stdcall RNBOsproActivate(void* packet,WORD writePassword,WORD activatePassword1,WORD activatePassword2,WORD address)
{
	return 0;
	if (address > 63) return 5;
	if ((RnbKey.cell[address].OnValidWritePassword) &&
		(RnbKey.cell[address].OnValidActivePassword1)&&
		(RnbKey.cell[address].OnValidActivePassword2))
	{
		return 0;
	}
	WORD wr = RequestRnbKey(RnbKey.KeyID);
	if (wr != 0) return wr;
	wr = RNBActivate(Packet,writePassword,activatePassword1,activatePassword2,address);
	if (wr == 0)
	{
		RnbKey.cell[address].WritePassword=writePassword;
		RnbKey.cell[address].ActivePassword1=activatePassword1;
		RnbKey.cell[address].ActivePassword2=activatePassword2;
		RnbKey.cell[address].OnValidWritePassword=true;
		RnbKey.cell[address].OnValidActivePassword1=true;
		RnbKey.cell[address].OnValidActivePassword2=true;
	}
	return wr;
}

DLL_API WORD _stdcall RNBOsproDecrement(void* packet,WORD writePassword,WORD address)
{
	if (address > 63) return 5;
	if (RnbKey.cell[address].OnValidWritePassword)
	{
		return 0;//todoOK
	}
	WORD wr = RequestRnbKey(RnbKey.KeyID);
	if (wr != 0) return wr;
	wr = RNBDecrement(Packet,writePassword,address);
	if (wr == 0)
	{
		RnbKey.cell[address].WritePassword=writePassword;
		RnbKey.cell[address].OnValidWritePassword=true;
	}
	return wr;

}

DLL_API WORD _stdcall RNBOsproExtendedRead(void* packet,WORD  address,WORD* data,BYTE* accessCode)
{

	if (address > 63) return 5;
	if ((RnbKey.cell[address].OnValidData)&&
		(RnbKey.cell[address].OnValidAccesCode))
	 {
		*data=RnbKey.cell[address].Data;
		*accessCode=RnbKey.cell[address].AccesCode;
		return 0;
	 }
	WORD wr = RequestRnbKey(RnbKey.KeyID);
	if (wr != 0) return wr;
	wr = RNBExtendeRead(Packet,address,data,accessCode);
	if (wr == 0)
	{
		RnbKey.cell[address].AccesCode=*accessCode;
		RnbKey.cell[address].OnValidAccesCode=true;
		RnbKey.cell[address].Data=*data;
		RnbKey.cell[address].OnValidData=true;
	}
	return wr;
}


DLL_API WORD _stdcall RNBOsproQuery(void* packet,WORD address,void* queryData,void* response,DWORD* response32,WORD length)
{
	if (address > 63) return 5;
	WORD i;
	WORD wr;
	// Buscar un query con igual direccion y longitud 
	for (i = 0;i<RnbKey.QueryCount;i++)
	{
		if ((address == RnbKey.Querys[i].address) && (length == RnbKey.Querys[i].length))
		{
			if (memcmp(queryData,RnbKey.Querys[i].query,length) == 0)
			{
				memcpy(response,RnbKey.Querys[i].response,length);
				return 0;
			}
		}
	}
	if (i == MAX_QUERYS) return 3;
	// No se encontro el query
	wr = RequestRnbKey(RnbKey.KeyID);
	if (wr != 0) return wr;
	wr = RNBQuery(Packet,address,queryData,response,response32,length);
	if (wr == 0)
	{
		// adicionar query
		i = RnbKey.QueryCount;
		RnbKey.Querys[i].address = address;
		RnbKey.Querys[i].length = length;
		memcpy(RnbKey.Querys[i].query,queryData,length);
		memcpy(RnbKey.Querys[i].response,response,length);
		RnbKey.QueryCount++;
	}
	return wr;
}
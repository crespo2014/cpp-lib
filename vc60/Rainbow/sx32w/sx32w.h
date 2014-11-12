#if !defined(sx32wh)
#define sx32wh

#define DLL_API extern "C" __declspec(dllexport)

#define SPRO_APIPACKET_ALIGNMENT_VALUE (sizeof(unsigned long))
#define SPRO_APIPACKET_SIZE            (1024+SPRO_APIPACKET_ALIGNMENT_VALUE)
#define SPRO_MAX_QUERY_SIZE            56              /* in bytes         */


typedef DWORD RB_SPRO_APIPACKET[SPRO_APIPACKET_SIZE/sizeof(DWORD)];


// declaracion de funciones de rainbow
typedef WORD _stdcall _RNBOsproFindFirstUnit(void*,WORD);
typedef WORD _stdcall _RNBOsproQuery(void*,WORD,void*,void*,DWORD*,WORD);
typedef WORD _stdcall _RNBOsproActivate(void*,WORD,WORD,WORD,WORD);
typedef WORD _stdcall _RNBOsproDecrement(void*,WORD,WORD);
typedef WORD _stdcall _RNBOsproExtendeRead(void*,WORD,WORD*,BYTE*);
typedef WORD _stdcall _RNBOsproFindNextUnit(void*);
typedef WORD _stdcall _RNBOsproFormatPacket(void*,DWORD);
typedef WORD _stdcall _RNBOsproGetVersion(void*,WORD*,WORD*,WORD*,WORD*);
typedef WORD _stdcall _RNBOsproInitialize(void*);
typedef WORD _stdcall _RNBOsproOverWrite(void*,WORD,WORD,WORD,WORD,WORD,BYTE);
typedef WORD _stdcall _RNBOsproRead(void*,WORD,WORD*);
typedef WORD _stdcall _RNBOsproWrite(void*,WORD,WORD,WORD,BYTE);



#define MAX_QUERYS 200

// declaracion de estructuras
struct RNBQUERY
{
	WORD address;
	BYTE query[SPRO_MAX_QUERY_SIZE];
	BYTE response[SPRO_MAX_QUERY_SIZE];
	WORD length;
};

struct RNBCELL
{
	WORD	Data;
	BYTE	AccesCode;
	DWORD	WritePassword;
	WORD	OverWritePassword1;
	WORD	OverWritePassword2;
	DWORD	ActivePassword1;
	DWORD	ActivePassword2;
	bool OnValidData;
	bool OnValidAccesCode;
	bool OnValidWritePassword;
	bool OnValidOverWritePassword;
	bool OnValidOverWritePassword1;
	bool OnValidOverWritePassword2;
	bool OnValidActivePassword1;
	bool OnValidActivePassword2;
};


struct RNBKEY
{
	BOOL	OnKeyID;	// Indica que el ID es valido
	WORD	KeyID;
	RNBCELL cell[64];
	WORD	QueryCount;
	RNBQUERY	Querys[MAX_QUERYS];
};

#endif

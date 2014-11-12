 #if !defined(GL10S_H)
#define GL10S_H

#include "..\g_01\g_01def.h"

// cada elemento del tree posee una estructura como esta
typedef struct
{
	WORD	type;
	LPVOID	object;
}S_TREELPARAM;

// identifica el elemento en el tree y el menu a tomar
typedef enum
{
	ID_ESCENA,
	ID_MATERIAL,
	ID_MESH,
	ID_MESHGROUP,
	ID_VARIABLE,
	ID_MESHINSTANCE,
	ID_VARIABLEINSTANCE
};
// iconos en el tree contiene los folders tambien
typedef enum
{
	VISTA_ICON,
	FOLDER_ICON,
	MATERIAL_ICON,
	MESH_ICON,
	MESHGROUP_ICON,
	VARIABLE_ICON,
};

typedef enum
{
	VAR_POSX,
	VAR_POSY,
	VAR_POSZ,
	VAR_ROTX,
	VAR_ROTY,
	VAR_ROTZ
};

/*
typedef struct
{
	float x,y,z;
} S_3DSPOINT;

typedef struct
{
	DWORD	v1,v2,v3;
} S_3DSFACE;

typedef struct 
{
	float	r,g,b;
}S_3DSCOLOR;
*/

class CEscena;
class CEscenaTree;
class CMaterial;
class CMeshMat;
class CMeshInstance;
class CMeshGroup;		//forward definition
class CGLView;
class CVariable;
class CVariableInstance;

#endif
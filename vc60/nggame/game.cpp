#define INITGUID

#include "gdef.h"
#include "gc01.h"
#include "gc06.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//C3DViewGame	Game;
	CDirectXGame	Game;
	return Game.Run();
}




typedef struct StructCommand
{ 
	DWORD Message[5];  // incluye OnComand,OnRun
					  //Message,MotorNum,NewValue
	int Pos[6];
	WORD dPos[6];
	BYTE dir[6];
	BYTE TablePtr[6];
	BYTE Moving[6];


} Command;

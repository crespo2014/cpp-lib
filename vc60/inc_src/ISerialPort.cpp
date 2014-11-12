
#include "stdafx.h"
#include "iserialport.h"

char* PORTS[]={"COM1","COM2","COM3","COM4"};

S_PORTDATA DTROFC[]={"ON",DTR_CONTROL_ENABLE,
					 "OFF",DTR_CONTROL_DISABLE,
					 "Handshake",DTR_CONTROL_HANDSHAKE};


S_PORTDATA RTSOFC[]={"ON",RTS_CONTROL_ENABLE,
				 	 "OFF",RTS_CONTROL_DISABLE,
					 "In Handshake",RTS_CONTROL_HANDSHAKE,
					 "Out Handshake",RTS_CONTROL_TOGGLE};


S_PORTDATA	BYTESIZE[]={"5 Bits",5,
						"6 Bits",6,
						"7 Bits",7,
						"8 Bits",8};


S_PORTDATA	STOPBITS[]={"1",	ONESTOPBIT,
						"1.5",	ONE5STOPBITS,
						"2",	TWOSTOPBITS};


S_PORTDATA  PARITY[]=  {"Even",		EVENPARITY,
						"Mark",		MARKPARITY,
						"No parity",NOPARITY,
						"Odd",		ODDPARITY,
						"Space",	SPACEPARITY};


S_PORTDATA BAUDRATE[]= {"110 Bits/s",	CBR_110,
						"300 Bits/s",	CBR_300,
						"600 Bits/s",	CBR_600,
						"1K2 Bits/s",	CBR_1200,
						"2K4 Bits/s",	CBR_2400,
						"4K8 Bits/s",	CBR_4800,
						"9K6 Bits/s",	CBR_9600,
						"14K4 Bits/s",	CBR_14400,
						"19K2 Bits/s",	CBR_19200,
						"38K4 Bits/s",	CBR_38400,
						"56 KBits/s",	CBR_56000,
						"57K6 Bits/s",	CBR_57600,
						"115K2 Bits/s",	CBR_115200,
						"128 KBits/s",	CBR_128000,
						"256 KBits/s",	CBR_256000};


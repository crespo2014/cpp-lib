// s10c1.h: interface for the CSock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_S10C1_H__68847DEF_13B8_11D3_BC46_0000E8DE4B3B__INCLUDED_)
#define AFX_S10C1_H__68847DEF_13B8_11D3_BC46_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
	int					af;			//tipo de socket address family specification
	int					type;		//tipo de coneccion datagrama o orientada
	int					protocol;	//protocolo
	SOCKET				handle;
	struct sockaddr_in	IPaddress;
	struct sockaddr		address;
	struct in_addr		in_address;
	
} S_CSOCK;

class AFX_EXT_CLASS CSock : public CObject  
{
public:
	int EnableMultiIP();
	int Listen();
	int SetAddress(struct sockaddr_in address);
	int Accept();
	int SetIPandPort(char* ip,u_short port);
	int Bind();
	int Create();
	int SetTCPIP();
	S_CSOCK* m_CSock;
	int InitCSock();
	CSock();
	virtual ~CSock();

};

#endif // !defined(AFX_S10C1_H__68847DEF_13B8_11D3_BC46_0000E8DE4B3B__INCLUDED_)

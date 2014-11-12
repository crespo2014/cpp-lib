/*
 * TcpBridgeApp.cpp
 *
 *  Created on: 16 Jun 2014
 *      Author: lester
 */

#include "TcpBridgeApp.h"
#include "log.h"
#include "ioPoll.h"

//#define log_e(...)

TcpBridgeApp::TcpBridgeApp()
{
	// TODO Auto-generated constructor stub

}

TcpBridgeApp::~TcpBridgeApp()
{
	// TODO Auto-generated destructor stub
}

void TcpBridgeApp::run(uint32_t inPort, uint32_t outPort)
{
	try
	{
	io::sPoll	p;
	net::socket srv;
	srv.create();
	srv.setnonBlocking(true);
	srv.bind(inPort);
	srv.listen(5);

	p.add(&srv);

	for (;;)
	{
		p.pollDevices();
		if (srv.canRead())
		{
			bridges.push_back(TcpBridge());
			TcpBridge& b = bridges.back();
			net::socket &s = b.getInSock();
			net::socket &c = b.getOutSock();
			s = srv.accept();
			c.create();
			c.setnonBlocking(true);
			c.connect("127.0.0.1", outPort);
			p.add(&s);
			p.add(&c);
		}
	}
	}catch (error_base& e)
	{
		log_e_push(e);
	}
}

/*
 * TcpBridge.h
 *
 *  Created on: 16 Jun 2014
 *      Author: lester
 */

#ifndef TCPBRIDGE_H_
#define TCPBRIDGE_H_

#include <utility>
#include "BridgeSock.h"

//template<class N>		// notifier
class TcpBridge
{
public:
	TcpBridge() :
			in_sock(*this, &out_sock), out_sock(*this, &in_sock)
	{

	}
	TcpBridge(const TcpBridge& t) :
			in_sock(*this, &out_sock), out_sock(*this, &in_sock)
	{
		in_sock = t.in_sock;
		out_sock = t.out_sock;
	}
	~TcpBridge()
	{

	}
	BridgeSock<TcpBridge>& getInSock()
	{
		return in_sock;
	}
	BridgeSock<TcpBridge>& getOutSock()
	{
		return out_sock;
	}
	void onSockError(BridgeSock<TcpBridge>* sock)
	{
		if ((sock == &in_sock && !out_sock.isConnected()) || ((sock == &out_sock) && !in_sock.isConnected()))
		{
			// close bridge
		}
	}

protected:
private:
	BridgeSock<TcpBridge> in_sock;
	BridgeSock<TcpBridge> out_sock;
};

#endif /* TCPBRIDGE_H_ */

/*
 * TcpBridgeApp.h
 *
 *  Created on: 16 Jun 2014
 *      Author: lester
 */

#ifndef TCPBRIDGEAPP_H_
#define TCPBRIDGEAPP_H_

#include <vector>
#include <list>
#include <stdint.h>
#include "TcpBridge.h"

class TcpBridgeApp
{
public:
	TcpBridgeApp();
	virtual ~TcpBridgeApp();
	void run(uint32_t inPort,uint32_t outPort);
private:
	std::list<TcpBridge> bridges;
};

#endif /* TCPBRIDGEAPP_H_ */

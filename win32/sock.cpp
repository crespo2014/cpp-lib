/*
 * sock.cpp
 *
 *  Created on: 23 Jun 2014
 *      Author: lester.crespo
 */

#include "sock.h"

WORD net::socket::ws_version;
WSADATA net::socket::ws_data;
int net::socket::ws_startup = net::socket::startUp();



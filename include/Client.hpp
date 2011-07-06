// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal

// Server.hpp (developer: Faisal@Nasim.org)
// $Id: Server.hpp,v 1.1 2003/06/13 17:32:17 faisal Exp faisal $

#ifndef __SQL_CLIENT_H
#define __SQL_CLIENT_H

#include <winsock2.h>

class Client
{
private:
	int socket;

public:
	bool			IsConnected;
	sockaddr_in		sinClient;

	int		GetSocket	();
	void	SetSocket	(int);
	int		SendData	(char*, int);
	int		Disconnect	();

	Client	() { IsConnected = false; }
	~Client	() { Disconnect(); }
};

#endif
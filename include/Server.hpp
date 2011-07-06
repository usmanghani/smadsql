// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
// Developer: faisal

// Server.hpp (developer: Faisal@Nasim.org)
// $Id: Server.hpp,v 1.1 2003/06/13 17:32:17 faisal Exp faisal $

#ifndef __SQL_SERVER_H
#define __SQL_SERVER_H

#include <winsock2.h>
#include <Client.hpp>

class Server
{
private:
	static const int StackBuffer = 1024; // 1K socket stack buffer
	static const int StatementBuffer = 1024*32; // 32K statement buffer size

	// statement handler pointer
	int (*handler)(char* , int , Server& , Client& );
	bool DEBUGMODE , ISRUNNING;

	struct sockaddr_in sin;
	struct hostent *server_host_name;
	int serversocket;

	char* host;
	int port;

public:
	Server ();
	~Server ();
	Server (int);
	int		GetPort ();
	void	SetPort ( int );
	void	DebugOn ();
	void	DebugOff ();
	void	SetHandler ( int (*) (char* , int , Server& , Client& ) );
	void	StopServer ();
	void	StartServer ();
	int		ParseCommand (Client&);
	void	ProcessStatement ( Client& , char* , int );
	void	DebugPrint ( const char* );

	bool	IsRunning () { return ISRUNNING; }
	int		GetSocket () { return serversocket; }
};

#endif
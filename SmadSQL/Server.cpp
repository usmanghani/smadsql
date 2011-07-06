// SMAD-SQL v0.1
// Copyright (C)2003 by:
//		Faisal Nasim	(Email: Faisal@Nasim.org)
//		Usman Ghani		(Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
//
// Provides the server functionality

// developer: Faisal@Nasim.org
// $Id: Server.cpp,v 1.1 2003/07/15 07:29:46 faisal Exp faisal $

#include <Base.hpp>
#include <Client.hpp>
#include <Server.hpp>

using namespace std;

int		Server::GetPort ()				{ return port; }
void	Server::SetPort ( int port )	{ if ( port > 0 && port < 65536 ) this->port = port; }
void	Server::DebugOn ()				{ DEBUGMODE = true; }
void	Server::DebugOff ()				{ DEBUGMODE = false; }
void	Server::SetHandler ( int (*ptr)(char* , int , Server& , Client& ) ) { handler = ptr; }

int		Client::Disconnect ()			{ IsConnected = false; return closesocket ( socket ); }
int		Client::SendData ( char* str , int len ){ return send ( socket , str , len , 0 ); }
int		Client::GetSocket ()			{ return socket; }
void	Client::SetSocket (int s)		{ socket = s; if ( s != INVALID_SOCKET ) IsConnected = true; }

Server::Server ()
{
	serversocket = INVALID_SOCKET;
	ISRUNNING = false;

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD( 2, 0 );
	if ( WSAStartup( wVersionRequested, &wsaData ) != 0 )
	{
		cerr << "Socket Initialization Error!" << endl;
		return;
	}
	DebugOff ();
}

Server::~Server ()
{
	StopServer();
	WSACleanup();
}

Server::Server (int port)	{ Server(); this->port = port; }

void Server::StopServer ()
{
	ISRUNNING = false;
	if ( serversocket != INVALID_SOCKET )
		closesocket (serversocket);
}

void Server::StartServer ()
{
	char welcome [128];
	sprintf ( welcome , "200 Salaam! SMAD-Server v%s Ready!\r\n" , SMAD_VERSION );
	host = "127.0.0.1";
	server_host_name = gethostbyname ( host );
	memset ( &sin , 0 , sizeof (sin) );

	serversocket = socket(AF_INET,SOCK_STREAM,0);

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl (INADDR_ANY);
	sin.sin_port = htons (port);
	if ( bind(serversocket, (sockaddr*) &sin , sizeof(sin)) != SOCKET_ERROR)
		listen ( serversocket, 60 );

	cout << "Listening on port " << port << endl;

	ISRUNNING = true;
	int socksize = sizeof ( sockaddr_in );
	
	while (ISRUNNING)
	{
		cout << "\n\nWaiting for a connection..." << flush << endl;

		Client C;
		C.SetSocket ( accept ( serversocket , (sockaddr*) &C.sinClient , &socksize ) );

		if ( C.GetSocket () != INVALID_SOCKET)
		{
			C.SendData ( welcome , strlen(welcome) );
			cout << "Accepted connection from " <<
                inet_ntoa(C.sinClient.sin_addr) << ":" <<
                ntohs(C.sinClient.sin_port) << "." << endl;
		}
		else {
			//cout << endl << WSAGetLastErrorMessage("accept connection") << endl;
			cout << "ERROR! :(\n" << endl;
		}	

	    if (ParseCommand(C))
			cout << "SHUTTING DOWN\n";

/*			char message [32];
		int sin_len = sizeof (sin);
		int bytes = recvfrom ( remotesd , message , 32 , 0 , (struct sockaddr*)&sinRemote , &sin_len );
		if ( bytes > 0 )
			std::cout << "Response: " << message << std::endl;
		if ( ! strncmp ( message , "stop" , 4 ) ) break;
*/
	}	
	closesocket (serversocket);
}

int Server::ParseCommand (Client& C)
{	
	char acReadBuffer[StackBuffer];
	char statement [StatementBuffer];
	char* ptr = statement;
	int nReadBytes , statementlen = 0;
	int sd = C.GetSocket();

	do
	{
		if ( ! ISRUNNING ) break;
		nReadBytes = recv (sd, acReadBuffer, StackBuffer, 0);

		if (nReadBytes > 0)
		{
			if ( DEBUGMODE )
				cout << "Received " << nReadBytes << " bytes from client." << endl;

			int cnt = 0;
			while ( cnt <= nReadBytes )
			{
				if ( acReadBuffer [cnt] == ';' || statementlen >= StatementBuffer-1 )
				{
					*ptr = 0;
					ProcessStatement ( C , statement , statementlen );
					strcpy ( statement , "" );
					ptr = statement;
					statementlen = 0;
					break;
				}
				if ( acReadBuffer[cnt] != ';' )
				{
					*ptr++ = acReadBuffer [cnt];
					statementlen++;
				}
				cnt++;
			}
			
			int nSentBytes = 0;
			while (nSentBytes < nReadBytes)
			{
				int nTemp = send(sd, acReadBuffer + nSentBytes, nReadBytes - nSentBytes, 0);
				if (nTemp > 0) {
					if ( DEBUGMODE )
						cout << "Sent " << nTemp << " bytes back to client." << endl;
					nSentBytes += nTemp;
				}
				else if (nTemp == SOCKET_ERROR) {
					cout << "SOCKET ERR!!";
					return false;
				}
				else {
					cout << "Peer unexpectedly dropped connection!" << endl;
					return true;
				}
			}
		}
		else if (nReadBytes == SOCKET_ERROR) {
			cout << "SOCKET ERROR";
			return false;
		}
	} while (nReadBytes != 0);

	DebugPrint ("Connection closed by peer.");
	return 0;
}

void Server::ProcessStatement ( Client& C , char* str , int length )
{
	int result = (*handler) ( str , length , *this , C );
}

void Server::DebugPrint ( const char* str )
{
	if ( DEBUGMODE == true ) cout << str << endl;
}

//
// _WIN32_WINNT version constants --> https://stackoverflow.com/questions/15370033/how-to-use-inet-pton-with-the-mingw-compiler
//
// #define _WIN32_WINNT_NT4                    0x0400 // Windows NT 4.0
// #define _WIN32_WINNT_WIN2K                  0x0500 // Windows 2000
// #define _WIN32_WINNT_WINXP                  0x0501 // Windows XP
// #define _WIN32_WINNT_WS03                   0x0502 // Windows Server 2003
// #define _WIN32_WINNT_WIN6                   0x0600 // Windows Vista
// #define _WIN32_WINNT_VISTA                  0x0600 // Windows Vista
// #define _WIN32_WINNT_WS08                   0x0600 // Windows Server 2008
// #define _WIN32_WINNT_LONGHORN               0x0600 // Windows Vista
// #define _WIN32_WINNT_WIN7                   0x0601 // Windows 7
// #define _WIN32_WINNT_WIN8                   0x0602 // Windows 8
// #define _WIN32_WINNT_WINBLUE                0x0603 // Windows 8.1
// #define _WIN32_WINNT_WINTHRESHOLD           0x0A00 // Windows 10
// #define _WIN32_WINNT_WIN10                  0x0A00 // Windows 10
//
#define _WIN32_WINNT 0x0601

#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//int inet_pton( int af, const char * src, void * dst );
//const char * inet_ntop( int af, const void * src, char * dst, socklen_t size );

int main( int argc, char * argv[] )
{
	WSADATA wsaData; // if this doesn't work
	//WSAData wsaData; // then try this instead

	// MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:
	if( WSAStartup( MAKEWORD(2,0), &wsaData ) != 0 )
	{
		fprintf( stderr, "WSAStartup failed.\n" );
		exit( 1 );
	}


/*
	struct sockaddr_in internet_address;
	internet_address.sin_family = AF_INET; //IPv4 == AF_INET ; IPv6 == AF_INET6
	internet_address.sin_port = htons( 24042 ); //Host to Network Short (byte order)
	internet_address.sin_addr.s_addr = inet_addr( "127.0.0.1" ); //internet
	memset( internet_address.sin_zero, '\0', sizeof internet_address.sin_zero );
*/

	struct sockaddr_in internet_address;
	
	internet_address.sin_family = AF_INET;
	internet_address.sin_port = htons( 24042 ); //Host to Network Short (byte order)
	inet_pton( AF_INET, "127.0.0.1", &internet_address.sin_addr );
/*
	struct sockaddr_in6 internet_address;
	
	internet_address.sin_family = AF_INET6;
	internet_address.sin_port = htons( 24042 ); //Host to Network Short (byte order)
	inet_pton( AF_INET6, "::1", &internet_address.sin6_addr );
*/

	int internet_socket;
	
	internet_socket = socket( PF_INET, SOCK_DGRAM, 0 ); //UDP == SOCK_DGRAM ; TCP == SOCK_STREAM

	sendto( internet_socket, "Hello UDP world!", 16, 0, (struct sockaddr *) &internet_address, sizeof internet_address );

	close( internet_socket );

	WSACleanup();

	return 0;
}
// gcc UDP_client_1.c -lws2_32 -o UDP_client_1.exe -D IPv4
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
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

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

	struct addrinfo hints, *result_head, *result_item;
	int gai_return;

	memset( &hints, 0, sizeof hints );
	hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
	hints.ai_socktype = SOCK_DGRAM;

	gai_return = getaddrinfo( "localhost.pxl-ea-ict.be", NULL, &hints, &result_head );
//	gai_return = getaddrinfo( "example.com", NULL, &hints, &result_head ); //nslookup example.com
//	gai_return = getaddrinfo( "cnn.com", NULL, &hints, &result_head ); //https://webmasters.stackexchange.com/questions/10927/using-multiple-a-records-for-my-domain-do-web-browsers-ever-try-more-than-one
	if( gai_return != 0 )
	{
		fprintf( stderr, "getaddrinfo: %s\n", gai_strerror( gai_return ) );
		exit( 2 );
	}

	result_item = result_head; //take first of the linked list
	while( result_item != NULL ) //while the pointer is valid
	{
		void * ip_address;
		char * ip_version;
		char ip_string[INET6_ADDRSTRLEN];

		if( result_item->ai_family == AF_INET )
		{ // IPv4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)result_item->ai_addr;
			ip_address = &(ipv4->sin_addr);
			ip_version = "IPv4";
		}
		else
		{ // IPv6
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)result_item->ai_addr;
			ip_address = &(ipv6->sin6_addr);
			ip_version = "IPv6";
		}

		inet_ntop( result_item->ai_family, ip_address, ip_string, sizeof ip_string );
		printf( "%s : %s\n", ip_version, ip_string );

		result_item = result_item->ai_next; //take next in the linked list
	}

	freeaddrinfo( result_head ); //free the linked list

	WSACleanup();

	return 0;
}
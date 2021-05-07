#ifdef _WIN32
	#define _WIN32_WINNT _WIN32_WINNT_WIN7
	#include <winsock2.h> //for all socket programming
	#include <ws2tcpip.h> //for getaddrinfo, inet_pton, inet_ntop
	int OSInit( void )
	{
		WSADATA wsaData;
		int WSAError = WSAStartup( MAKEWORD( 2, 0 ), &wsaData ); 
		if( WSAError != 0 )
		{
			fprintf( stderr, "WSAStartup errno = %d\n", WSAError );
			exit( -1 );
		}
	}
	int OSCleanup( void )
	{
		WSACleanup();
	}
	#define perror(string) fprintf( stderr, #string ": %d\n", WSAGetLastError() )
#else
	#include <sys/socket.h> //for sockaddr, socket, socket
	#include <sys/types.h> //for size_t
	#include <netdb.h> //for getaddrinfo
	#include <netinet/in.h> //for sockaddr_in
	#include <arpa/inet.h> //for htons, htonl, inet_pton, inet_ntop
	#include <errno.h> //for errno
	int OSInit( void ) {}
	int OSCleanup( void ) {}
#endif

#include <stdio.h> //for fprintf, perror
#include <unistd.h> //for close
#include <stdlib.h> //for exit
#include <string.h> //for memset

int initialization( struct addrinfo ** internet_address );
void execution( int internet_socket, struct addrinfo * internet_address );
void cleanup( int internet_socket, struct addrinfo * internet_address );

int main( int argc, char * argv[] )
{
	//////////////////
	//Initialization//
	//////////////////

	OSInit();

	struct addrinfo * internet_address = NULL;
	int internet_socket = initialization( &internet_address );


	/////////////
	//Execution//
	/////////////

	execution( internet_socket, internet_address );


	////////////
	//Clean up//
	////////////

	cleanup( internet_socket, internet_address );

	OSCleanup();

	return 0;
}

int initialization( struct addrinfo ** internet_address )
{
	//Step 1.1
	struct addrinfo internet_address_setup;
	memset( &internet_address_setup, 0, sizeof internet_address_setup );
	internet_address_setup.ai_family = AF_UNSPEC;
	internet_address_setup.ai_socktype = SOCK_DGRAM;
	getaddrinfo( "127.0.0.1", "24042", &internet_address_setup, &internet_address );
	printf( "errno = %d\n", WSAGetLastError() );

	//Step 1.2
	int internet_socket;
	internet_socket = socket( internet_address->ai_family, internet_address->ai_socktype, internet_address->ai_protocol );

	return internet_socket;
}

void execution( int internet_socket, struct addrinfo * internet_address )
{
	//Step 2.1
	sendto( internet_socket, "Hello UDP world!", 16, 0, internet_address->ai_addr, internet_address->ai_addrlen );

	//Step 2.2
	int number_of_bytes_received = 0;
	char buffer[1000];
	number_of_bytes_received = recvfrom( internet_socket, buffer, ( sizeof buffer ) - 1, 0, internet_address->ai_addr, internet_address->ai_addrlen );
	buffer[number_of_bytes_received] = '\0';
	printf( "Received : %s\n", buffer );
}

void cleanup( int internet_socket, struct addrinfo * internet_address )
{
	//Step 3.2
	freeaddrinfo( internet_address );

	//Step 3.1
	close( internet_socket );
}
#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <unistd.h>

int main( int argc, char * argv[] )
{
	//////////////////
	//Initialization//
	//////////////////

	//Step 1.0
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2,0), &wsaData );

	//Step 1.1
	struct addrinfo internet_address_setup;
	struct addrinfo *internet_address = NULL;
	memset( &internet_address_setup, 0, sizeof internet_address_setup );
	internet_address_setup.ai_family = AF_UNSPEC;
	internet_address_setup.ai_socktype = SOCK_DGRAM;
	getaddrinfo( "127.0.0.1", "24042", &internet_address_setup, &internet_address );

	//Step 1.2
	int internet_socket;
	internet_socket = socket( internet_address->ai_family, internet_address->ai_socktype, internet_address->ai_protocol );


	/////////////
	//Execution//
	/////////////

	//Step 2.1
	sendto( internet_socket, "Hello UDP world!", 16, 0, internet_address->ai_addr, internet_address->ai_addrlen );

	//Step 2.2
	int number_of_bytes_received = 0;
	char buffer[1000];
	socklen_t internet_address_length = internet_address->ai_addrlen;
	number_of_bytes_received = recvfrom( internet_socket, buffer, ( sizeof buffer ) - 1, 0, internet_address->ai_addr, &internet_address_length );
	buffer[number_of_bytes_received] = '\0';
	printf( "Received : %s\n", buffer );


	////////////
	//Clean up//
	////////////

	//Step 3.2
	freeaddrinfo( internet_address );

	//Step 3.1
	close( internet_socket );

	//Step 3.0
	WSACleanup();

	return 0;
}
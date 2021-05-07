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


	/////////////
	//Execution//
	/////////////


	////////////
	//Clean up//
	////////////

	//Step 3.0
	WSACleanup();

	return 0;
}
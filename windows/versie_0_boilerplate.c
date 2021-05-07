#include <winsock2.h>

int main( int argc, char * argv[] )
{
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2,0), &wsaData );



	WSACleanup();

	return 0;
}
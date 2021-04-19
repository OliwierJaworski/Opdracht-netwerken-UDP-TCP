// gcc 1_UDP_client.c -lws2_32 -o 1_UDP_client.exe
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
	WSADATA wsaData;
	WSAStartup( MAKEWORD(2,0), &wsaData );

	struct sockaddr internet_address;
	internet_address.sa_family = AF_INET;
	internet_address.sa_data[0] = 24042 >> 8;
	internet_address.sa_data[1] = 24042 & 0xFF;
	internet_address.sa_data[2] = 127;
	internet_address.sa_data[3] = 0;
	internet_address.sa_data[4] = 0;
	internet_address.sa_data[5] = 1;
	internet_address.sa_data[6] = 0;
	internet_address.sa_data[7] = 0;
	internet_address.sa_data[8] = 0;
	internet_address.sa_data[9] = 0;
	internet_address.sa_data[10] = 0;
	internet_address.sa_data[11] = 0;
	internet_address.sa_data[12] = 0;
	internet_address.sa_data[13] = 0;

	int internet_socket;
	internet_socket = socket( PF_INET, SOCK_DGRAM, 0 );

	sendto( internet_socket, "Hello UDP world!", 16, 0, &internet_address, sizeof internet_address );

	close( internet_socket );

	WSACleanup();

	return 0;
}
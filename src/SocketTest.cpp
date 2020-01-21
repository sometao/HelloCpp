#include <iostream>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define OK 0
#define ERR -1

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 42003
#define BACKLOG 15

#define IP_MAX_LEN 16
#define SOCKET_VERSION MAKEWORD(2, 2)
#define BUFF_SIZE 1024
#define REPLY_MSG "Welcome to here"



int ParseSocketAddr(SOCKADDR_IN stAddr, char* szIpAddr, short* pPort)
{
	char* remoteIp;
	memset(szIpAddr, 0, IP_MAX_LEN);
	remoteIp = inet_ntoa(stAddr.sin_addr);
	strcpy_s(szIpAddr, strlen(remoteIp) + 1, remoteIp);
	*pPort = ntohs(stAddr.sin_port);
	return OK;
}



int startServer() {

	cout << "server starting..." << endl;

	WSADATA stWsa;
	SOCKET iFd;
	SOCKADDR_IN stAddr = { 0 };
	SOCKADDR_IN stClientAddr = { 0 };
	SOCKET iClientFd;
	int     iConnAddrLen = sizeof(SOCKADDR_IN);
	char   szIpAddr[IP_MAX_LEN] = { 0 };
	short  sPort = 0;
	char szBuf[BUFF_SIZE] = { 0 };
	int iRcvLen = 0;
	int  iLoop = 0;


	stAddr.sin_family = AF_INET;
	stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	stAddr.sin_port = htons(SERVER_PORT);


	if (WSAStartup(SOCKET_VERSION, &stWsa) != OK) {
		cout << "WSAStartup failed." << endl;
		return ERR;
	}
	else {
		cout << "WSAStartup success." << endl;
	}
	if (LOBYTE(stWsa.wVersion) != 2 || HIBYTE(stWsa.wVersion) != 2) {
		cout << "socket version error:" << stWsa.wVersion << endl;
		WSACleanup();
		return ERR;
	}
	else {
		cout << "socket version correct:" << stWsa.wVersion << endl;
	}


	if ((iFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		cout << "socket init error" << endl;
		return ERR;
	}
	else {
		cout << "socket init success" << endl;
	}

	if (bind(iFd, (SOCKADDR*)&stAddr, sizeof(SOCKADDR)) < 0) {
		cout << "bind port[" << SERVER_PORT << "] error."  << endl;
		WSACleanup();
		closesocket(iFd);
		return ERR;
	}
	else {
		cout << "bind success: port=" << SERVER_PORT << endl;
	}



	if (listen(iFd, BACKLOG) != OK) {
		WSACleanup();
		closesocket(iFd);
		return ERR;
	}
	else {
		cout << "listen success;" << endl;
	}


	cout << "waiting connect..." << endl;
	iClientFd = accept(iFd, (SOCKADDR*)&stClientAddr, &iConnAddrLen);
	cout << "got connection: " << iClientFd << endl;



	while (1) {
		iLoop += 1;
		cout << "loop[" << iLoop << "]" << endl;
		//iClientFd = accept(iFd, (SOCKADDR*)&stClientAddr, &iConnAddrLen);
		//cout << "got connection: " << iClientFd << endl;
		//if (iClientFd < 0) {
		//	continue;
		//}

		ParseSocketAddr(stClientAddr, szIpAddr, &sPort);

		memset(szBuf, 0, BUFF_SIZE);
		iRcvLen = recv(iClientFd, szBuf, BUFF_SIZE - 1, 0);
		cout << "iRcvLen=" << iRcvLen << endl;

		char reply[512] = {0};
		strcat_s(reply, "I got your msg[");
		strcat_s(reply, szBuf);
		strcat_s(reply, "], Thank you.");


		if (send(iClientFd, reply, strlen(reply) + 1, 0) < 0) {
			cout << "Replay failed" << endl;
		}

		cout << "Receive message from ";
		cout << szIpAddr << ":" << (sPort & 0xFFFF) << szBuf << endl;

	}
	closesocket(iFd);
	WSACleanup();
	return OK;


}


int startClient() {

	cout << "1028 client starting..." << endl;

	WSADATA stWsa;
	SOCKET iFd;
	SOCKADDR_IN stAddr = { 0 };
	char szSendMsg[BUFF_SIZE] = "Hello Rose.";
	char szRcvMsg[BUFF_SIZE] = { 0 };

	stAddr.sin_family = AF_INET;
	stAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	stAddr.sin_port = htons(SERVER_PORT);

	if (WSAStartup(SOCKET_VERSION, &stWsa) != OK) {
		cout << "WSAStartup failed." << endl;
		return ERR;
	}

	if ((iFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		cout << "create socket error" << endl;
		return ERR;
	}

	if (connect(iFd, (SOCKADDR*)&stAddr, sizeof(SOCKADDR)) != OK) {
		cout << "connect error." << endl;
		closesocket(iFd);
		WSACleanup();
		return ERR;
	}

	while (1) {
		printf("Send:");
		memset(szSendMsg, 0, BUFF_SIZE);
		cin.getline(szSendMsg, BUFF_SIZE);
		if (strcmp(szSendMsg, "exit") == 0) {
			break;
		}

		if (send(iFd, szSendMsg, strlen(szSendMsg) + 1, 0) < 0) {
			cout << "send msg err" << endl;
			closesocket(iFd);
			WSACleanup();
			return ERR;
		}

		else {
			cout << "send [" << szSendMsg << "] success!!" << endl;
		}

		memset(szRcvMsg, 0, BUFF_SIZE);
		if (recv(iFd, szRcvMsg, BUFF_SIZE - 1, 0) > 0) {
			cout << "Receive: " << szRcvMsg << endl;
		}
		else {
			cout << "Receive NOTHING." << endl;
		}
	}

	closesocket(iFd);
	WSACleanup();


	return OK;
}


int socketLaunch(int argc, char* argv[]) {

	if (argc == 2) {
		char cmd = *argv[1];

		switch (cmd)
		{
		case 'c':
			startClient();
			break;
		case 's':
			startServer();
			break;
		default:
			cout << "error input: [" << cmd << "]" << endl;
			break;
		}
	}
	else
	{
		cout << "input 'c' for client, and 's' for server." << endl;
	}


	return OK;
}
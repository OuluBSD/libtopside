#ifdef flagPOSIX
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#endif

#include "Core.h"

NAMESPACE_UPP_BEGIN

#if defined flagWIN32

#if defined flagCLANG || defined flagGCC
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
	struct sockaddr_storage ss;
	unsigned long s = size;
	
	ZeroMemory(&ss, sizeof(ss));
	ss.ss_family = af;
	
	switch (af) {
	case AF_INET:
		((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
		break;
	case AF_INET6:
		((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
		break;
	default:
		return NULL;
	}
	/* cannot directly use &size because of strict aliasing rules */
	return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0) ?
		   dst : NULL;
}
#endif

WSADATA TcpSocket::wsaData;
bool TcpSocket::is_initialized;
TcpSocket::Uninitializer TcpSocket::uninit;


TcpSocket::TcpSocket() {
	if (!is_initialized) {
		int res = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (res == 0)
			is_initialized = true;
	}
	
}

bool TcpSocket::IsOpen() const {return sock && is_open;}

bool TcpSocket::Listen(int port, int max_conn) {
	Close();
	
	struct addrinfo hints;
	MemorySet(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    
    // Resolve the server address and port
    String portstr = IntStr(port);
	struct addrinfo *result = NULL;
    int iResult = getaddrinfo(NULL, portstr.Begin(), &hints, &result);
    if ( iResult != 0 ) {
        return false;
    }
	
	// Create a SOCKET for connecting to server
    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock == INVALID_SOCKET) {
        //printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        return false;
    }
    
	// Setup the TCP listening socket
    iResult = bind(sock, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        //printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(sock);
        result = 0;
        return false;
    }
    
    freeaddrinfo(result);

    iResult = listen(sock, max_conn);
    if (iResult == SOCKET_ERROR) {
        //printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(sock);
        return false;
    }
    
    is_open = true;
    return true;
}

bool TcpSocket::Accept(TcpSocket& sock) {
	Close();
	
	this->sock = accept(sock.sock, NULL, NULL);
    if (this->sock == INVALID_SOCKET) {
        //printf("accept failed with error: %d\n", WSAGetLastError());
        return false;
    }
    
    is_open = true;
    return true;
}

void TcpSocket::Close() {
	if (sock){
		shutdown(sock, SD_SEND);
		closesocket(sock);
		sock = 0;
		is_open = false;
	}
}

String TcpSocket::GetLine(int max_len) {
	if (!IsOpen())
		return "";
	
	String out;
	while (out.GetCount() < max_len) {
		char chr;
		int received = recv(sock, &chr, 1, 0);
		if (!received) {
			Close();
			break;
		}
		if (chr == '\n')
			break;
		out.Cat(chr);
	}
	return out;
}

String TcpSocket::GetPeerAddr() {
	if (!IsOpen()) return "";
	sockaddr_in client_info = {0};
	int len = sizeof(client_info);
	getpeername(sock, (struct sockaddr*)&client_info, &len);
	char buf[1024];
	buf[0] = 0;
	inet_ntop(client_info.sin_family, (const void*)&client_info.sin_addr, buf, 1024);
	return buf;
}

int TcpSocket::Put(const void* data, int size) {
	if (!IsOpen()) return 0;
	int sent = send(sock, (const char*)data, size, 0);
	if (sent != size) {
		Close();
	}
	return sent;
}

int TcpSocket::Get(void* data, int size) {
	if (!IsOpen()) return 0;
	int got = recv(sock, (char*)data, size, 0);
	if (got != size) {
		Close();
	}
	return got;
}

String TcpSocket::Get(int size) {
	Vector<char> buf;
	buf.SetCount(size);
	int got = Get(buf.Begin(), size);
	buf.SetCount(got);
	return String(buf.Begin(), got);
}

bool TcpSocket::Connect(String addr, int port) {
	Close();
	
	// Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

	struct addrinfo hints;
	MemorySet(&hints, 0, sizeof(struct addrinfo));
	
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    String portstr = IntStr(port);
	struct addrinfo *result = NULL;
    iResult = getaddrinfo(addr.Begin(), portstr.Begin(), &hints, &result);
    if ( iResult != 0 ) {
        //printf("getaddrinfo failed with error: %d\n", iResult);
        return false;
    }
    for(struct addrinfo *ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
	
	    sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	    if (sock == INVALID_SOCKET) {
	        //printf("socket failed with error: %ld\n", WSAGetLastError());
	        continue;
	    }
	
	    // Connect to server.
	    iResult = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
	    if (iResult == SOCKET_ERROR) {
	        closesocket(sock);
	        sock = 0;
	        continue;
	    }
		
		is_open = true;
		freeaddrinfo(result);
		return true;
    }
    
    Close();
    freeaddrinfo(result);
    return false;
}

void TcpSocket::Shutdown() {
	shutdown(sock, SD_BOTH);
}

void TcpSocket::Timeout(int ms) {
	int timeout = ms;
	if (sock) {
		setsockopt(sock, IPPROTO_TCP, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
		setsockopt(sock, IPPROTO_TCP, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
	}
}

#endif










#ifdef flagPOSIX

TcpSocket::TcpSocket() {
	timeout = 100;
}

bool TcpSocket::IsOpen() const {
	return listenfd >= 0 || connfd >= 0;
}

bool TcpSocket::Listen(int port, int max_conn) {
	if (IsOpen())
		Close();
	
	char sendBuff[1025];
	time_t ticks;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, '0', sizeof(addr));
	memset(sendBuff, '0', sizeof(sendBuff));
	
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	
	bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
	
	if (timeout)
		Timeout(timeout);
	
	int n = listen(listenfd, 10);
	return n >= 0;
}

bool TcpSocket::Accept(TcpSocket& sock) {
	if (IsOpen())
		Close();
	
	memset(&addr, 0, sizeof(addr));
	socklen_t len = sizeof(addr);
	
	if (timeout)
		Timeout(timeout);
	
	connfd = accept(sock.listenfd, (struct sockaddr*)&addr, &len);
	
	return IsOpen();
}

void TcpSocket::Shutdown() {
	if (connfd >= 0) {
		shutdown(connfd, SHUT_RDWR);
	}
	if (listenfd >= 0) {
		shutdown(listenfd, SHUT_RDWR);
	}
}

void TcpSocket::Close() {
	if (connfd >= 0) {
		close(connfd);
		connfd = -1;
	}
	if (listenfd >= 0) {
		close(listenfd);
		listenfd = -1;
	}
}

String TcpSocket::GetLine(int max_len) {
	String s;
	while (s.GetCount() < max_len) {
		char c = 0;
		int n = read(connfd, &c, 1);
		if (n <= 0 || c == 0 || c == '\n')
			break;
		
		s.Cat(c);
	}
	return s;
}

String TcpSocket::GetPeerAddr() {
	const char* c = inet_ntoa(addr.sin_addr);
	String s(c);
	return s;
}

int TcpSocket::Put(const void* data, int size) {
	if (connfd < 0)
		return 0;
	
	int sent = write(connfd, data, size);
	
	if (sent < 0)
		Close();
	
	return sent > 0 ? sent : 0;
}

int TcpSocket::Get(void* data, int size) {
	if (connfd < 0)
		return 0;
	
	int got = read(connfd, data, size);
	
	if (got < 0)
		Close();
	
	return got > 0 ? got : 0;
}

String TcpSocket::Get(int size) {
	char recvBuff[1024];
	String s;
	while (s.GetCount() < size) {
		int remaining = min(1024, size - s.GetCount());
		
		int n = read(connfd, recvBuff, remaining);
		if (n <= 0)
			break;
		
		s.Cat(recvBuff, n);
	}
	return s;
}

bool TcpSocket::Connect(String addr_str, int port) {
	if (IsOpen())
		Close();
	
	int n = 0;
	if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		last_error = "could not create socket";
		return false;
	}
	
	memset(&addr, '0', sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	
	const char* c = addr_str.Begin();
	if (inet_pton(AF_INET, c, &addr.sin_addr) <= 0) {
		last_error = "inet_pton error occured";
		return false;
	}

	n = connect(connfd, (struct sockaddr *)&addr, sizeof(addr));
	
	return n >= 0;
}

void TcpSocket::Timeout(int ms) {
	timeout = ms;
	if (connfd >= 0) {
		setsockopt(connfd, IPPROTO_TCP, SO_RCVTIMEO, &timeout, sizeof(timeout));
		setsockopt(connfd, IPPROTO_TCP, SO_SNDTIMEO, &timeout, sizeof(timeout));
	}
	if (listenfd >= 0) {
		setsockopt(listenfd, IPPROTO_TCP, SO_RCVTIMEO, &timeout, sizeof(timeout));
		setsockopt(listenfd, IPPROTO_TCP, SO_SNDTIMEO, &timeout, sizeof(timeout));
	}
}

#endif


NAMESPACE_UPP_END

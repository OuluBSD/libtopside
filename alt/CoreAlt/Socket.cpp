#include "Core.h"

NAMESPACE_UPP_BEGIN

#if defined flagWIN32
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

bool TcpSocket::IsOpen() {return sock && is_open;}

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

#endif










#ifdef flagPOSIX

TcpSocket::TcpSocket() {
	TODO
}

bool TcpSocket::IsOpen() {
	TODO
}

bool TcpSocket::Listen(int port, int max_conn) {
	TODO
}

bool TcpSocket::Accept(TcpSocket& sock) {
	TODO
}

void TcpSocket::Close() {
	TODO
}

String TcpSocket::GetLine(int max_len) {
	TODO
}

String TcpSocket::GetPeerAddr() {
	TODO
}

int TcpSocket::Put(const void* data, int size) {
	TODO
}

int TcpSocket::Get(void* data, int size) {
	TODO
}

String TcpSocket::Get(int size) {
	TODO
}

bool TcpSocket::Connect(String addr, int port) {
	TODO
}

void TcpSocket::Timeout(int ms) {
	TODO
}

#endif


NAMESPACE_UPP_END

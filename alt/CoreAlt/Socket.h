#ifndef _CoreAlt_Socket_h_
#define _CoreAlt_Socket_h_

/*#ifdef flagWIN32
#include <ws2tcpip.h>
#endif*/

NAMESPACE_UPP_BEGIN


class TcpSocket {
	#ifdef flagWIN32
	static WSADATA wsaData;
	static bool is_initialized;
	SOCKET sock = 0;
	
	struct Uninitializer {
		~Uninitializer() {WSACleanup();}
	};
	static Uninitializer uninit;
	#else
	
	#endif
	
	bool is_open = false;
public:
	TcpSocket();
	~TcpSocket() {Close();}
	
	bool Listen(int port, int max_conn);
	bool Accept(TcpSocket& sock);
	bool IsOpen();
	void Close();
	String GetLine(int max_len = UINT16_MAX);
	String GetPeerAddr();
	int Put(String str) {return Put((void*)str.Begin(), str.GetCount());}
	int Put(const void* data, int size);
	int Get(void* data, int size);
	String Get(int size);
	bool Connect(String addr, int port);
	void Timeout(int ms);
};

NAMESPACE_UPP_END

#endif

#ifndef _CoreAlt_Socket_h_
#define _CoreAlt_Socket_h_

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
	struct sockaddr_in addr;
	int listenfd = -1;
	int connfd = -1;
	int timeout = 0;
	String last_error;
	#endif
	
	bool is_open = false;
public:
	TcpSocket();
	~TcpSocket() {Close();}
	
	bool Listen(int port, int max_conn=5);
	bool Accept(TcpSocket& sock);
	bool IsOpen() const;
	void Shutdown();
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

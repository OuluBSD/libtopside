// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IInternet_TmplClasses_h_
#define _IInternet_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Net> struct InternetSocketT;


template <class Net>
struct InternetSocketT : NetSocket {
	typename Net::NativeSocket sock;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Net::Socket_Initialize(sock, *this, ws))
			return false;
		return true;
	}

	void Uninitialize() override {
		Net::Socket_Uninitialize(sock);
	}

	bool ProcessPacket(PacketValue& v) override {
		if (!Net::Socket_ProcessPacket(sock, v))
			return false;
		return true;
	}

	bool CreateSocket() {
		return Net::Socket_CreateSocket(this->sock);
	}
	
	void ClearSocket() {
		Net::Socket_ClearSocket(this->sock);
	}
	
	
};

using PosixSocket = InternetSocketT<NetPosix>;
using Win32Socket = InternetSocketT<NetWin32>;
using EnetSocket = InternetSocketT<NetEnet>;
using NullSerialSocket = InternetSocketT<NetNullSerial>;


NAMESPACE_PARALLEL_END



#endif


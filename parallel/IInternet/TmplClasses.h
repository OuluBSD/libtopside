// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.7 20:44:33

#ifndef _IInternet_TmplClasses_h_
#define _IInternet_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Net> struct InternetSocketT;


template <class Net>
struct InternetSocketT : NetSocket {
	using CLASSNAME = InternetSocketT<Net>;
	RTTI_DECL1(CLASSNAME, NetSocket)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<NetSocket>(this);}
	
	typename Net::NativeSocket sock;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Net::Socket_Initialize(sock, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Net::Socket_PostInitialize(sock, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Net::Socket_Start(sock, *this);
	}

	void Stop() override {
		Net::Socket_Stop(sock, *this);
	}

	void Uninitialize() override {
		Net::Socket_Uninitialize(sock, *this);
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Net::Socket_ProcessPacket(sock, *this, in, out))
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

#if 0
using PosixSocket = InternetSocketT<NetPosix>;
#endif

#if 0
using Win32Socket = InternetSocketT<NetWin32>;
#endif

#if 0
using EnetSocket = InternetSocketT<NetEnet>;
#endif

#if 0
using NullSerialSocket = InternetSocketT<NetNullSerial>;
#endif


NAMESPACE_PARALLEL_END



#endif


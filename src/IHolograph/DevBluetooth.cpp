#include "IHolograph.h"


#if defined flagHACK && ((defined flagLINUX) || (defined flagFREEBSD))

#include <ports/hcidump/hcidump.h>

/*
	If data can't be read, run:
		setcap 'cap_net_raw,cap_net_admin+eip' /path/to/compiled/executable
*/


extern "C" {
int hcidump_device(int device);
}

NAMESPACE_PARALLEL_BEGIN




struct HoloDevBluetooth::NativeSinkDevice {
	SimpleBluetoothConnection bt[2];
	Vector<byte> data[2];
	TcpSocket sock;
	int mode;
	int ctrl_idx[2];
};



bool HoloDevBluetooth::SinkDevice_Create(NativeSink*& dev) {
	dev = new NativeSink;
	return true;
}

void HoloDevBluetooth::SinkDevice_Destroy(NativeSink*& dev) {
	delete dev;
}

void HoloDevBluetooth::SinkDevice_Visit(NativeSinkDevice&, AtomBase&, RuntimeVisitor& vis) {
	
}

bool HoloDevBluetooth::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.ctrl_idx[0] = ws.GetInt(".controller.left.idx", -1);
	dev.ctrl_idx[1] = ws.GetInt(".controller.right.idx", -1);
	
	if (dev.ctrl_idx[0] < 0 && dev.ctrl_idx[1] < 0) {
		LOG("HoloDevBluetooth::SinkDevice_Initialize: error: no controller arguments given");
		return false;
	}
	
	int port = ws.GetInt(".remote.port", -1);
	
	if (port < 0) {
		dev.mode = 0;
		
		for(int i = 0; i < 2; i++) {
			if (dev.ctrl_idx[i] < 0)
				continue;
			
			if (!dev.bt[i].Open(dev.ctrl_idx[i])) {
				LOG("HoloDevBluetooth::SinkDevice_Initialize: error: could not open controller #" << i << " for reading (device index " << dev.ctrl_idx[i] << ")");
				return false;
			}
		}
	}
	else {
		dev.mode = 1;
		
		String addr = ws.GetString(".remote.addr", "127.0.0.1");
		if (!dev.sock.Connect(addr, port)) {
			LOG("HoloDevBluetooth::SinkDevice_Initialize: error: could not connect remote bluetooth daemon in " << addr << ":" << port);
			return false;
		}
	}
	
	return true;
}

bool HoloDevBluetooth::SinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

bool HoloDevBluetooth::SinkDevice_Start(NativeSinkDevice& dev, AtomBase& a) {
	return true;
}

void HoloDevBluetooth::SinkDevice_Stop(NativeSinkDevice& dev, AtomBase& a) {
	
}

void HoloDevBluetooth::SinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase& a) {
	for(int i = 0; i < 2; i++)
		dev.bt[i].Close();
}

bool HoloDevBluetooth::SinkDevice_Send(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

bool HoloDevBluetooth::SinkDevice_Recv(NativeSinkDevice& dev, AtomBase& a, int sink_ch, const Packet& in) {
	TODO
}

void HoloDevBluetooth::SinkDevice_Finalize(NativeSinkDevice& dev, AtomBase& a, RealtimeSourceConfig& cfg) {
	TODO
}


/*
	02 47 20 32
	00 2E 00 41
	00 A1 01 00
	
	E6 77 8F 00
	FF FF 81 B2
	93 FE F4 D6
	F9 A1 1D 04
	
	E1 0A C8 F8
	FF 1C 0E 00
	3C FC FF 22
	7A 36 85 9E
	
	FF 8C 01 2E
	
	01 03 00 00
	00 00 00
	
	11 buttons
	12 thumb-x
	13,14 thumb-y
	15 grasp
	16 touchpad-x
	17 touchpad-y
	21 accel-x
	24 accel-z
	27 accel-y
	31,32 accel-x (sensitive) (int16)
	34,35 accel-y (sensitive)
	37,38 accel-z (sensitive)
	41,42 time (ms, sec)
	43,44 roll
	45,46 yaw
	47,48 pitch
*/

struct WmrCtrlData {
	byte magic[4]; // 02 47 20 32 --> 2,"G 2"
	uint16 unknown0;
	uint16 unknown1;
	uint16 unknown2;
	byte unknown3;
	byte button_mask;
	#if 1
	float orientation[4];
	float position[4];
	float unknown4;
	#else
	int16 u16[18];
	#endif
	byte unknown5;
	byte unknown6;
	byte pad[6];
	
	
	void Process() {
		#if 0
		for(int i = 0; i < 4; i++) {
			EndianSwap(orientation[i]);
			EndianSwap(position[i]);
		}
		EndianSwap(unknown4);
		#endif
	}
	void CheckKnown() {
		ASSERT(magic[0] == 2);
		ASSERT(magic[1] == 'G');
		ASSERT(magic[2] == ' ');
		ASSERT(magic[3] == '2');
		ASSERT(unknown0 == 0x2E00);
		ASSERT(unknown1 == 0x4100);
		ASSERT(unknown2 == 0xA100);
		ASSERT(unknown3 == 0x1);
		ASSERT(unknown5 == 0x1);
		ASSERT(unknown6 == 0x3);
		
		
	}
	
	String ToString() const {
		String s;
		for(int i = 0; i < 8; i++) {
			if (button_mask & (1 << i)) {
				if (s.GetCount()) s << ", ";
				s << "button #" << i;
			}
		}
		#if 1
		s << " [";
		for(int i = 0; i < 4; i++) {
			if (i) s << ", ";
			s << orientation[i];
		}
		s << "], [";
		for(int i = 0; i < 4; i++) {
			if (i) s << ", ";
			s << position[i];
		}
		s << "]";
		s << " " << unknown4;
		#else
		s << "[";
		for(int i = 0; i < 18; i++) {
			int j = u16[i];
			if (i) s << ", ";
			s << j;
		}
		s << "]";
		#endif
		return s;
	}
};

bool HoloDevBluetooth::SinkDevice_IsReady(NativeSinkDevice& dev, AtomBase& a, PacketIO& io) {
	if (dev.mode == 0) {
		for(int i = 0; i < 2; i++) {
			if (dev.bt[i].ReadPacket(dev.data[i])) {
				
				TODO
				
			}
			
		}
		TODO
	}
	else if (dev.mode == 1) {
		
		for(int i = 0; i < 2; i++) {
			int conn_i = dev.ctrl_idx[i];
			if (conn_i >= 0) {
				dev.sock.Put(&conn_i, sizeof(conn_i));
				
				int len = 0;
				dev.sock.Get(&len, sizeof(len));
				int dlen = sizeof(WmrCtrlData);
				int dlen_4 = dlen / 4;
				int len_4 = len / 4;
				if (len_4 == dlen_4 || len_4 + 1 == dlen_4) {
					WmrCtrlData d;
					dev.sock.Get(&d, sizeof(WmrCtrlData));
					
					d.Process();
					DUMP(d);
					d.CheckKnown();
					
				}
				else {
					String data = dev.sock.Get(len);
					LOG("Unexpected data: size " << len << " hash " << IntStr(data.GetHashValue()));
				}
			}
		}
	}
	return true;
}





NAMESPACE_PARALLEL_END
#endif


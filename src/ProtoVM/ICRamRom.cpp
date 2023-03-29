#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


ICMem8Base::ICMem8Base(byte* data, int size, bool writable) {
	this->data = data;
	this->size = size;
	this->writable = writable;
	
	memset(data, 0, size);
	
	// NOTE: incorrect order for any real package
	
	AddSink("A0"); // 0
	AddSink("A1");
	AddSink("A2");
	AddSink("A3");
	AddSink("A4");
	AddSink("A5");
	AddSink("A6");
	AddSink("A7");
	AddSink("A8");
	AddSink("A9");
	AddSink("A10");
	AddSink("A11");
	AddSink("A12");
	AddSink("A13");
	AddSink("A14");
	AddSink("A15");
	AddBidirectional("D0"); // 16
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	AddSink("~OE"); // 24
	AddSink("~CS");
	
	if (writable)
		AddSink("~WR");
	
}

bool ICMem8Base::Tick() {
	bool verbose = 1;
	addr = in_addr;
	writing = in_writing;
	reading = in_reading;
	enabled = in_enabled;
	if (writing && addr < size) {
		data[addr] = in_data;
	}
	if (verbose) {
		LOG("ICMem8Base::Tick: r=" << (int)in_reading << ", w=" << (int)in_writing << ", addr=" << HexStr(in_addr) << ", data=" << HexStr(in_data));
	}
	in_data = 0;
	in_addr = 0;
	return true;
}

bool ICMem8Base::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	union {
		byte tmp[2];
		uint16 tmp16;
	};
	/*if (type == READ) {
		if (writable) {
			ProcessType dest_type = ProcessType::INVALID;
			switch(type) {
				case READ:      dest_type = WRITE;  break;
				case RW:        dest_type = WRITE; break;
				default: break;
			}
			processing = true;
			bool ret = dest.Process(dest_type, bytes, bits, dest_conn_id, *this, conn_id);
			processing = false;
			return ret;
		}
	}*/
	/*if (type == BYTE_WRITE) {
		switch (conn_id) {
		case 0:
			if (reading && enabled) {
				tmp[0] = this->addr < size ? this->data[this->addr] : 0;
				return dest.PutRaw(dest_conn_id, &tmp[0], 1);
			}
			break;
		case 8:
			break;
		default:
			LOG("error: ICMem8Base: unimplemented conn-id");
			return false;
		}
	}*/
	if (type == WRITE) {
		switch (conn_id) {
		case A0:
		case OE:
		case CS:
		case WR:
			// skip (write of RW)
			break;
		case D0:
			if (reading && enabled) {
				tmp[0] = this->addr < size ? this->data[this->addr] : 0;
				return dest.PutRaw(dest_conn_id, &tmp[0], 1, 0);
			}
			break;
		default:
			LOG("error: ICMem8Base::Process: unimplemented connection-id");
		return false;
		}
	}
	else {
		LOG("error: ICMem8Base::Process: unimplemented ProcessType");
		return false;
	}
	return true;
}

bool ICMem8Base::PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) {
	int off;
	uint16 mask;
	uint16 data16;
	
	switch (conn_id) {
		#include "D8A16.inl"
	case OE: // ~OE
		in_reading = !*data;
		break;
	case CS: // ~CS
		in_enabled = !*data;
		break;
	case WR:
		ASSERT(writable);
		ASSERT(data_bytes == 0 && data_bits == 1);
		in_writing = !*data;
		break;
		
	default:
		LOG("error: ICMem8Base::PutRaw: unimplemented conn-id");
		return false;
	}
	return true;
}





NAMESPACE_TOPSIDE_END

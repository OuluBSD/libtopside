#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


IC62256::IC62256() {
	memset(data, 0, size);
	
	// NOTE: incorrect order for any real package
	
	AddBidirectional("D0"); // 0
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	AddSink("A0"); // 8
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
	AddSink("~WR"); // 24
	AddSink("~OE");
	AddSink("~CS");
	
}

bool IC62256::Tick() {
	addr = in_addr;
	writing = in_writing;
	reading = in_reading;
	enabled = in_enabled;
	if (writing && addr < size) {
		data[addr] = in_data;
	}
	return true;
}

bool IC62256::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	union {
		byte tmp[2];
		uint16 tmp16;
	};
	if (type == WRITE) {
		switch (conn_id) {
		case 0:
			if (reading && enabled) {
				tmp[0] = this->addr < size ? this->data[this->addr] : 0;
				return dest.PutRaw(dest_conn_id, &tmp[0], 1, 0);
			}
			break;
		case 8:
			/*if (reading && enabled) {
				tmp16 = addr;
				return dest.PutRaw(dest_conn_id, &tmp[0], 2);
			}*/
			break;
		/*case 24:
			return dest.PutRaw(dest_conn_id, &writing, 1);
		case 25:
			tmp[0] = !writing;
			return dest.PutRaw(dest_conn_id, &tmp[0], 1);
		case 26:
			tmp[0] = false;
			return dest.PutRaw(dest_conn_id, &tmp[0], 1);*/
		default:
			LOG("error: IC62256: unimplemented conn-id");
			return false;
		}
	}
	else {
		LOG("error: IC62256: unimplemented ProcessType");
		return false;
	}
	return true;
}

bool IC62256::PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) {
	switch (conn_id) {
	case 0: // D0
		ASSERT(data_bytes == 1 && data_bits == 0);
		in_data = *data;
		break;
	case 8: // A0
		ASSERT(data_bytes == 2 && data_bits == 0);
		in_addr = *(uint16*)data;
		break;
	case 24: // ~WR
		ASSERT(data_bytes == 0 && data_bits == 1);
		in_writing = !*data;
		break;
	case 25: // ~OE
		ASSERT(data_bytes == 0 && data_bits == 1);
		in_reading = !*data;
		break;
	case 26: // ~CS
		in_enabled = !*data;
		ASSERT(data_bytes == 0 && data_bits == 1);
		break;
	default:
		LOG("unimplemented conn-id");
		return false;
	}
	return true;
}


IC27256::IC27256() {
	AddBidirectional("D0"); // 0
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	AddSink("A0"); // 8
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
	AddSink("~OE"); // 24
	AddSink("~CS");
	//AddSource("Vpp");
	
}

bool IC27256::Tick() {
	addr = in_addr;
	reading = in_reading;
	enabled = in_enabled;
	return true;
}

bool IC27256::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	union {
		byte tmp[2];
		uint16 tmp16;
	};
	if (type == READ) {
		TODO
	}
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
			LOG("error: IC27256: unimplemented conn-id");
			return false;
		}
	}*/
	else if (type == WRITE) {
		switch (conn_id) {
		case 0:
			if (reading && enabled) {
				tmp[0] = this->addr < size ? this->data[this->addr] : 0;
				return dest.PutRaw(dest_conn_id, &tmp[0], 1, 0);
			}
			break;
		case 8:
			// skip
			break;
		default:
			LOG("error: IC27256::Process: unimplemented connection-id");
		return false;
		}
	}
	else {
		LOG("error: IC27256::Process: unimplemented ProcessType");
		return false;
	}
	return true;
}

bool IC27256::PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) {
	switch (conn_id) {
	case 0: // D0
		ASSERT(data_bytes == 1 && data_bits == 0);
		in_data = *data;
		break;
	case 8: // A0
		ASSERT(data_bytes * 8 + data_bits <= 16 && data_bytes * 8 + data_bits > 0);
		if (data_bits != 0) {
			in_addr = 0;
			// Note: optimized (16 bits max)
			uint16 data16 = *(uint16*)data;
			uint16 mask =	((data_bytes & 2) ? 0xFFFF : 0x0) |
							((data_bytes & 1) ?   0xFF : 0x0) |
							(((1<<(data_bits+1))-1) << (data_bytes * 8));
			in_addr =		data16 & mask;
		}
		else {
			in_addr = *(uint16*)data;
		}
		break;
	case 24: // ~OE
		in_reading = !*data;
		break;
	case 25: // ~CS
		in_enabled = !*data;
		break;
	default:
		LOG("error: IC27256::PutRaw: unimplemented conn-id");
		return false;
	}
	return true;
}







IC27128::IC27128() {
	
}


NAMESPACE_TOPSIDE_END

#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


Pin::Pin() {
	AddBidirectional("bi");
	
}





Pin& Pin::SetReference(bool is_high) {
	this->is_high = is_high;
	Clear();
	AddBidirectional("0").SetMultiConn();
	return *this;
}

bool Pin::Tick() {
	return true;
}

bool Pin::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	if (type == WRITE) {
		ASSERT(bytes == 0 && bits == 1);
		return dest.PutRaw(dest_conn_id, &is_high, 0, 1);
	}
	else {
		LOG("error: Pin: unimplemented ProcessType");
		return false;
	}
	return true;
}


bool Pin::PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) {
	// this can be put if it's high, because... that's the order of connections
	return is_high;
}

int Pin::GetFixedPriority() const {
	return is_high ? INT_MAX : 0;
}







FlipFlopJK::FlipFlopJK() {
	AddSink("Ck");
	AddSource("~Pr").SetMultiConn();
	AddSource("~Clr").SetMultiConn();
	AddSource("D").SetMultiConn();
	AddSource("~Q").SetMultiConn();
	
}




Crystal::Crystal() {
	AddSink("I");
	AddSource("O").SetMultiConn();
	
}

ElcNor::ElcNor() {
	AddSink("I0");
	AddSink("I1");
	AddSource("C").SetMultiConn();
	
}

ElcNand::ElcNand() {
	AddSink("I0");
	AddSink("I1");
	AddSource("O").SetMultiConn();
	
}

bool ElcNand::Tick() {
	out = !(in0 && in1);
	LOG("ElcNand::Tick(" << GetName() << "): " << 1*in0 << ", " << 1*in1 << ", " << 1*out);
	return true;
}

bool ElcNand::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	/*if (type == READ) {
		TODO
	}
	else*/ if (type == WRITE) {
		switch (conn_id) {
		case 0:
		case 1:
			// skip (write of RW)
			break;
		case 2:
			return dest.PutRaw(dest_conn_id, (byte*)&out, 0, 1);
			break;
		default:
			LOG("error: ElcNand: unimplemented conn-id");
			return false;
		}
	}
	else {
		LOG("error: ElcNand: unimplemented ProcessType");
		return false;
	}
	return true;
}

bool ElcNand:: PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) {
	switch (conn_id) {
	case 0: // I0
		ASSERT(data_bytes == 0 && data_bits == 1);
		in0 = *data & 1;
		break;
	case 1: // I1
		ASSERT(data_bytes == 0 && data_bits == 1);
		in1 = *data & 1;
		break;
	default:
		LOG("error: ElcNand: unimplemented conn-id");
		return false;
	}
	return true;
}

ElcNot::ElcNot() {
	AddSink("I");
	AddSource("O").SetMultiConn();
	
}

ElcCapacitor::ElcCapacitor() {
	AddSink("I");
	AddSource("O").SetMultiConn();
	
}


NAMESPACE_TOPSIDE_END

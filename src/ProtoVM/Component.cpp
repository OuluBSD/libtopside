#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


Pin::Pin() {
	AddBidirectional("bi");
	
}

Pin& Pin::SetReference(bool is_high) {
	is_ref_volt = true;
	this->is_high = is_high;
	Clear();
	AddBidirectional("0").SetMultiConn();
	return *this;
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
	return true;
}

bool ElcNand::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	if (type == READ) {
		TODO
	}
	else if (type == WRITE) {
		switch (conn_id) {
		case 2:
			return dest.PutRaw(dest_conn_id, (byte*)&out, 1, 0);
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
		ASSERT(data_bytes == 1 && data_bits == 0);
		in0 = *data;
		break;
	case 1: // I1
		ASSERT(data_bytes == 1 && data_bits == 0);
		in1 = *data;
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

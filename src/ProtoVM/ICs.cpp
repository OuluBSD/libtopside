#include "ProtoVM.h"


IC6502::IC6502() {
	AddSink("~Res");
	AddSource("~NMI");
	AddSource("~IRQ");
	AddSource("Rdy");
	AddBidirectional("D0");
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	AddSource("~RW");
	AddSource("Phi2 out");
	AddSource("A0");
	AddSource("A1");
	AddSource("A2");
	AddSource("A3");
	AddSource("A4");
	AddSource("A5");
	AddSource("A6");
	AddSource("A7");
	AddSource("A8");
	AddSource("A9");
	AddSource("A10");
	AddSource("A11");
	AddSource("A12");
	AddSource("A13");
	AddSource("A14");
	AddSource("A15");
	AddSink("Phi in");
	
	
}


Z80::Z80() {
	AddSink("CLK");
	AddSink("~RESET");
	AddSink("~NMI");
	AddSink("~WAIT");
	AddSink("~WR");
	AddSink("~RD");
	AddSink("~IORQ");
	AddSink("~MREQ");
	AddSource("~BUSAK");
	AddSource("~BUSRQ");
	AddSource("~INT");
	AddSource("~HALT");
	AddSource("~RFSH");
	AddSource("~M1");
	AddSource("BA0");
	AddSource("BA1");
	AddSource("BA2");
	AddSource("BA3");
	AddSource("BA4");
	AddSource("BA5");
	AddSource("BA6");
	AddSource("BA7");
	AddSource("BA8");
	AddSource("BA9");
	AddSource("BA10");
	AddSource("BA11");
	AddSource("BA12");
	AddSource("BA13");
	AddSource("BA14");
	AddSource("BA15");
	AddSource("vcc");
	AddBidirectional("BD0");
	AddBidirectional("BD1");
	AddBidirectional("BD2");
	AddBidirectional("BD3");
	AddBidirectional("BD4");
	AddBidirectional("BD5");
	AddBidirectional("BD6");
	AddBidirectional("BD7");
	
}

IC6850::IC6850() {
	AddSink("Rx clk");
	AddSink("Tx clk");
	AddSink("CS0");
	AddSink("~CS2");
	AddSink("RS");
	AddSink("~RW");
	AddSink("E");
	AddSink("~CTS");
	AddSink("~DCD");
	AddSink("Rx");
	AddBidirectional("D0");
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	AddSource("CS1");
	AddSource("Tx");
	
}


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

bool IC62256::Process(ProcessType type, byte sz, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	union {
		byte tmp[2];
		uint16 tmp16;
	};
	if (type == BYTE_WRITE) {
		switch (conn_id) {
		case 0:
			if (reading && enabled) {
				tmp[0] = this->addr < size ? this->data[this->addr] : 0;
				return dest.PutRaw(dest_conn_id, &tmp[0], 1);
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

bool IC62256::PutRaw(uint16 conn_id, byte* data, int data_sz) {
	switch (conn_id) {
	case 0: // D0
		ASSERT(data_sz == 1);
		in_data = *data;
		break;
	case 8: // A0
		ASSERT(data_sz == 2);
		in_addr = *(uint16*)data;
		break;
	case 24: // ~WR
		in_writing = !*data;
		break;
	case 25: // ~OE
		in_reading = !*data;
		break;
	case 26: // ~CS
		in_enabled = !*data;
		break;
	default:
		LOG("unimplemented conn-id");
		return false;
	}
	return true;
}


IC27256::IC27256() {
	AddBidirectional("D0");
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	AddSink("A0");
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
	AddSink("~OE");
	AddSink("~CS");
	AddSource("Vpp");
	
}


IC74LS138::IC74LS138() {
	AddSink("A");
	AddSink("B");
	AddSink("C");
	AddSink("G1");
	AddSink("~G2b");
	AddSink("~G2a");
	AddSource("~0");
	AddSource("~1");
	AddSource("~2");
	AddSource("~3");
	AddSource("~4");
	AddSource("~5");
	AddSource("~6");
	AddSource("~7");
	
}


IC74LS163::IC74LS163() {
	AddSink("Clk");
	AddSink("Da");
	AddSink("Db");
	AddSink("Dc");
	AddSink("Dd");
	AddSource("Ep");
	AddSource("Et");
	AddSource("~Ld");
	AddSource("Qd");
	AddSource("Qc");
	AddSink("~Clr");
	
}


ICMAX232::ICMAX232() {
	AddSink("-V");
	AddSource("+V");
	AddSink("+C1");
	AddSink("+C2");
	AddSink("T2I");
	AddSink("T2O");
	AddSink("Vcc");
	AddSource("Gnd");
	AddSource("-C1");
	AddSource("-C2");
	AddSource("R20");
	AddSource("R1I");
	
}


IC74LS245::IC74LS245() {
	
}

IC8085::IC8085() {
	
}

IC74F573::IC74F573() {
	
}

IC27128::IC27128() {
	
}

ICDS1210::ICDS1210() {
	
}

IC8251A::IC8251A() {
	
}

ICGAL16V8::ICGAL16V8() {
	
}


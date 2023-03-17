#include "ProtoVM.h"


// https://github.com/floooh/chips-test/blob/master/tests/m6502-int.c


NAMESPACE_TOPSIDE_BEGIN


IC6502::IC6502()
{
	AddBidirectional("A0");
	AddBidirectional("A1");
	AddBidirectional("A2");
	AddBidirectional("A3");
	AddBidirectional("A4");
	AddBidirectional("A5");
	AddBidirectional("A6");
	AddBidirectional("A7");
	AddBidirectional("A8");
	AddBidirectional("A9");
	AddBidirectional("A10");
	AddBidirectional("A11");
	AddBidirectional("A12");
	AddBidirectional("A13");
	AddBidirectional("A14");
	AddBidirectional("A15");
	
	AddBidirectional("D0");
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	
	AddSource("R~W");
	AddSource("PHI2 OUT");
	AddSink("~IRQ");
	AddSink("~NMI");
	AddSink("RDY");
	AddSink("AEC");
	AddSink("~Res");
	//AddSink("PHI IN");
	
	in_pins = 0;
	in_pins_mask = M6502_IRQ | M6502_NMI | M6502_RDY | M6510_AEC | M6502_RES;
}

bool IC6502::Tick() {
	pins = (pins & 0xFFFFFFFFFF000000ULL) | (uint64)in_addr | ((uint64)in_data << 16ULL);
	pins = (pins & ~in_pins_mask) | in_pins;
	
    pins = m6502_tick(&cpu, pins);
	
    const uint16_t addr = M6502_GET_ADDR(pins);
    
    reading = (pins & M6502_RW);
    sync = !(pins & M6502_SYNC);
    
    if (verbose) {
        String s;
	    s << "  A: " << HexStr(cpu.A) << "\n";
	    s << "  X: " << HexStr(cpu.X) << "\n";
	    s << "  Y: " << HexStr(cpu.Y) << "\n";
	    s << "  S: " << HexStr(cpu.S) << "\n";
	    const uint8_t f = cpu.P;
	    char f_str[9] = {
	        (f & M6502_NF) ? 'N':'-',
	        (f & M6502_VF) ? 'V':'-',
	        (f & M6502_XF) ? 'X':'-',
	        (f & M6502_BF) ? 'B':'-',
	        (f & M6502_DF) ? 'D':'-',
	        (f & M6502_IF) ? 'I':'-',
	        (f & M6502_ZF) ? 'Z':'-',
	        (f & M6502_CF) ? 'C':'-',
	        0
	    };
	    s << "  P:  " << HexStr(f) << " " << String(f_str) << "\n";
	    s << "  PC: " << HexStr(cpu.PC) << "\n";
	    s << "  6510 I/O Port:\n";
	    s << "    DDR:    " << HexStr(cpu.io_ddr) << "\n";
	    s << "    Input:  " << HexStr(cpu.io_inp) << "\n";
	    s << "    Output: " << HexStr(cpu.io_out) << "\n";
	    s << "    Drive:  " << HexStr(cpu.io_drive) << "\n";
	    s << "    Float:  " << HexStr(cpu.io_floating) << "\n";
	    s << "    Pullup: " << HexStr(cpu.io_pullup) << "\n";
	    s << "    Pins:   " << HexStr(cpu.io_pins) << "\n";
	    s << "    ExtPin: " << HexStr(pins);
	    LOG("IC6502::Tick:\n" << s);
    }
    
	in_addr = 0;
	in_data = 0;
	in_pins = 0;
    return true;
}

bool IC6502::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	union {
		byte tmp[2];
		uint16 tmp16;
	};
	bool true_value = true;
	if (type == WRITE) {
		switch (conn_id) {
		case A0:
		case A0+1:
		case A0+2:
		case A0+3:
		case A0+4:
		case A0+5:
		case A0+6:
		case A0+7:
		case A0+8:
		case A0+9:
		case A0+10:
		case A0+11:
		case A0+12:
		case A0+13:
		case A0+14:
		case A0+15:
			if (sync) {
				tmp16 = (pins >> (uint64)(conn_id));
				if (conn_id == A0 && bytes == 2) {LOG("IC6502::Process: sent addr: " << HexStr(tmp16));}
				return dest.PutRaw(dest_conn_id, tmp, bytes, bits);
			}
			break;
		case D0:
		case D0+1:
		case D0+2:
		case D0+3:
		case D0+4:
		case D0+5:
		case D0+6:
		case D0+7:
			if (!reading && sync) {
				tmp[0] = (pins >> (uint64)(conn_id));
				if (conn_id == D0 && bytes == 1) {LOG("IC6502::Process: sent data: " << HexStr(tmp[0]));}
				return dest.PutRaw(dest_conn_id, tmp, bytes, bits);
			}
			break;
		case IRQ:
		case NMI:
		case RES:
			true_value = false; // negate pin
		case RW:
		case SYNC:
		case RDY:
		case AEC:
			tmp[0] = ((pins >> (uint16)conn_id) & 1) == true_value;
			return dest.PutRaw(dest_conn_id, tmp, 0, 1);
			
		default:
			LOG("error: IC6502::Process: unimplemented connection-id");
			return false;
		}
	}
	
	/*if (type == READ) {
		ProcessType dest_type = WRITE;
		return dest.Process(dest_type, bytes, bits, dest_conn_id, *this, conn_id);
	}*/
	return true;
}

bool IC6502::PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) {
	int off;
	uint16 mask;
	uint16 data16;
	bool value;
	bool true_value = true;
	if (conn_id == 0 && data_bytes == 2) {
		LOG("IC6502::Process: got addr: " << HexStr(*(uint16*)data));
	}
	if (conn_id == 16 && data_bytes == 1) {
		LOG("IC6502::Process: got data: " << HexStr(*data));
	}
	switch (conn_id) {
		#include "D8A16.inl"
		case IRQ:
		case NMI:
		case RES:
			true_value = false; // negate pin
		case RW:
		case SYNC:
		case RDY:
		case AEC:
			ASSERT(data_bytes == 0 && data_bits == 1);
			value = (*data & 0x1) == true_value;
			SetPin(conn_id, value);
			break;
	default:
		LOG("IC6502::PutRaw: error: unsupported conn-id");
		return false;
	};
	return true;
}

void IC6502::SetPin(int i, bool b) {
	uint64 mask = 1ULL << (uint64)i;
	if (b)
		in_pins |= mask;
	else
		in_pins &= ~mask;
}

NAMESPACE_TOPSIDE_END

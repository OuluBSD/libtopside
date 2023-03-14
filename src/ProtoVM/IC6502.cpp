#include "ProtoVM.h"


// https://github.com/floooh/chips-test/blob/master/tests/m6502-int.c


NAMESPACE_TOPSIDE_BEGIN

void IC6502_BusWrite(uint16_t addr, uint8_t data, void* p) {
	((IC6502*)p)->Write(addr, data);
}

uint8_t IC6502_BusRead(uint16_t addr, void* p) {
	return ((IC6502*)p)->Read(addr);
}

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
	AddBidirectional("~IRQ");
	AddBidirectional("~NMI");
	AddBidirectional("RDY");
	AddBidirectional("AEC");
	AddBidirectional("~Res");
	//AddSink("PHI IN");
	
	
}

void IC6502::Write(uint16 addr, uint8 data) {
	TODO
}

byte IC6502::Read(uint16 addr) {
	TODO
}

bool IC6502::Tick() {
    pins = m6502_tick(&cpu, pins);
    const uint16_t addr = M6502_GET_ADDR(pins);
    
    #if 0
    reading = M6502_RW == (pins & (M6502_SYNC|M6502_RW));
    sync = (M6502_SYNC|M6502_RW) == (pins & (M6502_SYNC|M6502_RW));
    #else
    reading = (pins & M6502_RW);
    sync = (pins & M6502_SYNC);
    #endif
    
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
    
    return true;
}

bool IC6502::Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	union {
		byte tmp[2];
		uint16 tmp16;
	};
	if (type == WRITE || type == ProcessType::RW) {
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
				tmp16 = (pins >> (conn_id - A0));
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
				tmp[0] = (pins >> (conn_id - D0)) & 0xFF;
				return dest.PutRaw(dest_conn_id, tmp, bytes, bits);
			}
			break;
		case RW:
		case SYNC:
		case IRQ:
		case NMI:
		case RDY:
		case AEC:
		case RES:
			tmp[0] = pins & (1 << conn_id);
			return dest.PutRaw(dest_conn_id, &tmp[0], 0, 1);
			
		default:
			LOG("error: IC6502::Process: unimplemented connection-id");
			return false;
		}
	}
	
	if (type == READ || type == ProcessType::RW) {
		ProcessType dest_type = ProcessType::INVALID;
		switch(type) {
			case ProcessType::READ:      dest_type = WRITE;  break;
			case ProcessType::RW:        dest_type = WRITE; break;
			default: break;
		}
		return dest.Process(dest_type, bytes, bits, dest_conn_id, *this, conn_id);
	}
	return true;
}

bool IC6502::PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) {int off;
	uint16 mask;
	uint16 data16;
	
	switch (conn_id) {
		#include "D8A16.inl"
		default: TODO
	};
	return true;
}


NAMESPACE_TOPSIDE_END

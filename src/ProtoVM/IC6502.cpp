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
	AddBidirectional("D0");
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
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
	AddSink("~Res");
	AddSource("~NMI");
	AddSource("~IRQ");
	AddSource("~SO");
	AddSource("RDY");
	AddSource("R~W");
	AddSource("PHI2 OUT");
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
    if (pins & M6502_RW) {
        M6502_SET_DATA(pins, mem[addr]);
    }
    else {
        mem[addr] = M6502_GET_DATA(pins);
    }
    
    writing = M6502_RW == (pins & (M6502_SYNC|M6502_RW));
    reading = 0 == (pins & (M6502_SYNC|M6502_RW));
    
    return true;
}

bool IC6502::Process(ProcessType type, byte sz, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	TODO
}

bool IC6502::PutRaw(uint16 conn_id, byte* data, int data_sz) {
	TODO
}


NAMESPACE_TOPSIDE_END

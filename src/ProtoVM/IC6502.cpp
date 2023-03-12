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

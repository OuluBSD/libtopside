#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN

void IC6502_BusWrite(uint16_t addr, uint8_t data, void* p) {
	((IC6502*)p)->Write(addr, data);
}

uint8_t IC6502_BusRead(uint16_t addr, void* p) {
	return ((IC6502*)p)->Read(addr);
}

IC6502::IC6502() :
	cpu(&IC6502_BusRead, &IC6502_BusWrite, this)
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
	return cpu.Step();
}

bool IC6502::Process(ProcessType type, byte sz, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) {
	TODO
}

bool IC6502::PutRaw(uint16 conn_id, byte* data, int data_sz) {
	TODO
}


NAMESPACE_TOPSIDE_END

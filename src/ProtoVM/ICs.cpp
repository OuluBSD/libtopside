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
	AddSink("~WR");
	AddSink("~OE");
	AddSink("~CS");
	
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


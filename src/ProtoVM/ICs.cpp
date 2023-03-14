#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


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

ICDS1210::ICDS1210() {
	
}

IC8251A::IC8251A() {
	
}

ICGAL16V8::ICGAL16V8() {
	
}


NAMESPACE_TOPSIDE_END

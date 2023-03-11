#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


InterakBus::InterakBus() {
	AddBidirectional("+5V_0");
	AddBidirectional("+5V_1");
	AddBidirectional("GND_0");
	AddBidirectional("GND_1");
	AddBidirectional("-12V_0");
	AddBidirectional("-12V_1");
	AddBidirectional("+12V_0");
	AddBidirectional("+12V_1");
	AddBidirectional("WAIT");
	AddBidirectional("RCLK");
	AddBidirectional("NRFSH");
	AddBidirectional("NENOUT");
	AddBidirectional("NENIN");
	AddBidirectional("D0");
	AddBidirectional("D1");
	AddBidirectional("D2");
	AddBidirectional("D3");
	AddBidirectional("D4");
	AddBidirectional("D5");
	AddBidirectional("D6");
	AddBidirectional("D7");
	AddBidirectional("~RESET");
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
	AddBidirectional("~RD");
	AddBidirectional("~WR");
	AddBidirectional("MEMREQ");
	AddBidirectional("IORQ");
	
	AddBidirectional("+5V_2");
	AddBidirectional("+5V_3");
	AddBidirectional("GND_2");
	AddBidirectional("GND_3");
	AddBidirectional("-12V_2");
	AddBidirectional("-12V_3");
	AddBidirectional("+12V_2");
	AddBidirectional("+12V_3");
	AddBidirectional("CLK(x2)");
	AddBidirectional("NBAO");
	AddBidirectional("NBAI");
	AddBidirectional("NIEO");
	AddBidirectional("NIEI");
	AddBidirectional("DB8");
	AddBidirectional("DB9");
	AddBidirectional("DB10");
	AddBidirectional("DB11");
	AddBidirectional("DB12");
	AddBidirectional("DB13");
	AddBidirectional("DB14");
	AddBidirectional("DB15");
	AddBidirectional("NBUSREQ");
	
	// AB is originally in inverted order
	AddBidirectional("AB16");
	AddBidirectional("AB17");
	AddBidirectional("AB18");
	AddBidirectional("AB19");
	AddBidirectional("AB20");
	AddBidirectional("AB21");
	AddBidirectional("AB22");
	AddBidirectional("AB23");
	
	AddBidirectional("NINTC");
	AddBidirectional("NINTB");
	AddBidirectional("NINTA");
	AddBidirectional("NNMI");
	AddBidirectional("NZCMAINS");
	AddBidirectional("NC2");
	AddBidirectional("NC");
	AddBidirectional("NMI(OCF)M1");
	AddBidirectional("NDIRIN");
	AddBidirectional("NADS");
	AddBidirectional("NEOMREQ");
	AddBidirectional("NEIREQ");
	
	
	
}


NAMESPACE_TOPSIDE_END

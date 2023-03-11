#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN

// http://searle.x10host.com/6502/Simple6502.html

void SetupTest2_6502(Machine& mach) {
	
	Pcb& b = mach.AddPcb();
	
	Port& power = mach.GetPower();
	power.SetCount(2);
	Pin& ground = power.GetPin(0).SetReference(0);
	Pin& vcc = power.GetPin(1).SetReference(1);
	ground.SetName("ground");
	vcc.SetName("vcc");
	
	IC6502& cpu = b.Add<IC6502>();
	IC27256& rom = b.Add<IC27256>();
	IC62256& ram32k = b.Add<IC62256>();
	Bus8& data_bus = b.Add<Bus8>();
	Bus16& addr_bus = b.Add<Bus16>();
	
	
	try {
		cpu["A0,16"] >> addr_bus;
		cpu["D0,8"] >> data_bus;
		addr_bus >> rom["A0,16"];
		data_bus >> rom["D0,8"];
		addr_bus >> ram32k["A0,16"];
		data_bus >> ram32k["D0,8"];
		
		/*tester["~WRITE"]  >> ram32k["~WR"];
		tester["~READ"]   >> ram32k["~OE"];
		tester["~ENABLE"] >> ram32k["~CS"];*/
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
}

NAMESPACE_TOPSIDE_END

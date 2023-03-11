#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


void SetupInterak(Machine& mach) {
	
	// CPU-CF Issue 4
	{
		Pcb& b = mach.AddPcb();
		
		Port& power = mach.GetPower();
		power.SetCount(2);
		Pin& ground = power.GetPin(0).SetReference(0);
		Pin& vcc = power.GetPin(1).SetReference(1);
		ground.SetName("ground");
		vcc.SetName("vcc");
		
		Z80& cpu = b.Add<Z80>();
		IC74LS245& u6 = b.Add<IC74LS245>();
		IC74LS245& u2 = b.Add<IC74LS245>();
		IC74LS245& u3 = b.Add<IC74LS245>();
		IC74LS245& u4 = b.Add<IC74LS245>();
		ResistorPack& rn1 = b.Add<ResistorPack>(8);
		ResistorPack& rn3 = b.Add<ResistorPack>(8);
		ENode& cpu_mreq = b.AddNode("cpu mreq");
		ENode& cpu_iorq = b.AddNode("cpu iorq");
		ENode& cpu_rd = b.AddNode("cpu rd");
		ENode& cpu_wr = b.AddNode("cpu wr");
		ENode& cpu_wait = b.AddNode("cpu wait");
		ENode& cpu_nmi = b.AddNode("cpu nmi");
		ENode& cpu_clk = b.AddNode("cpu clk");
		ENode& cpu_ba0 = b.AddNode("cpu ba0");
		ENode& cpu_ba1 = b.AddNode("cpu ba1");
		ENode& cpu_ba2 = b.AddNode("cpu ba2");
		Bus8& data_bus = b.Add<Bus8>();
		Bus16& addr_bus = b.Add<Bus16>();
		Bus16& iface_addr_bus = b.Add<Bus16>();
		Bus8& cf_addr_bus = b.Add<Bus8>();
		InterakBus& iface = b.Add<InterakBus>();
		
		// Pull-ups
		cpu["~M1"] >> rn3[1];
		cpu["~RFSH"] >> rn3[2];
		cpu["~HALT"] >> rn3[3];
		cpu["~INT"] >> rn3[4];
		cpu["~BUSRQ"] >> rn3[5];
		cpu["~BUSAK"] >> rn3[6];
		
		// Address bus
		cpu["BA0,16"] >> addr_bus;
		addr_bus["0,3"] >> cf_addr_bus["0,3"];
		addr_bus["15,-8"] >> u2["A0,8"];
		addr_bus["7,-8"] >> u3["A0,8"];
		
		// Data bus
		cpu["BD0,8"] >> data_bus;
		data_bus["7,-8"] >> u4["a0,8"];
		data_bus["0,8"] >> rn1["0,8"];
		
		// Interface
		u4["B0,8"] >> iface["D0,8"]; // data
		u3["B0,8"] >> iface_addr_bus["7,-8"];
		u2["B0,8"] >> iface_addr_bus["15,-8"];
		iface_addr_bus >> iface["A0,16"];
		
		
		TODO
	}
	/*PushButtonComp& reset = b.Add<PushButtonComp>();
	Resistor4k7& r4k7 = b.Add<Resistor4k7>();
	Resistor& crystal_r0 = b.Add<Resistor>();
	Resistor& crystal_r1 = b.Add<Resistor>();
	ENode& reset_ground = b.AddNode("reset ground");
	ENode& reset_vcc = b.AddNode("reset vcc");
	ENode& cpu_rw = b.AddNode("cpu rw");
	ENode& ram_read = b.AddNode("cpu rw");
	ENode& comm_cs0 = b.AddNode("comm cs");
	ENode& ram_cs = b.AddNode("ram cs");
	ENode& phi_in = b.AddNode("phi in");
	ENode& phi_out = b.AddNode("phi out");
	ENode& counter_qd = b.AddNode("counter qd");
	ENode& master_clk = b.AddNode("master clk");
	ENode& crystal_a = b.AddNode("crystal a");
	ENode& crystal_b = b.AddNode("crystal b");
	ENode& crystal_c = b.AddNode("crystal c");
	ENode& crystal_d = b.AddNode("crystal d");
	ENode& master_ck = b.AddNode("master ck");
	ElcNand& ram_read_nand = b.Add<ElcNand>();
	ElcNand& ram_write_nand = b.Add<ElcNand>();
	ElcNand& eprom32k_cs_nand = b.Add<ElcNand>();
	ElcNand& counter_nand = b.Add<ElcNand>();
	ElcNor& eprom32k_cs_nor0 = b.Add<ElcNor>();
	ElcNor& eprom32k_cs_nor1 = b.Add<ElcNor>();
	ElcNot& ram_write_not = b.Add<ElcNot>();
	ElcNot& comm_not = b.Add<ElcNot>();
	ElcNot& eprom32k_cs_not = b.Add<ElcNot>();
	ElcNot& crystal_not0 = b.Add<ElcNot>();
	ElcNot& crystal_not1 = b.Add<ElcNot>();
	ElcNot& crystal_not2 = b.Add<ElcNot>();
	ElcCapacitor& serial_gnd_cap = b.Add<ElcCapacitor>();
	ElcCapacitor& serial_vcc_cap = b.Add<ElcCapacitor>();
	ElcCapacitor& serial_cap1 = b.Add<ElcCapacitor>();
	ElcCapacitor& serial_cap2 = b.Add<ElcCapacitor>();
	ElcCapacitor& serial_cap3 = b.Add<ElcCapacitor>();
	ElcCapacitor& crystal_cap = b.Add<ElcCapacitor>();
	Bus8& data_bus = b.Add<Bus8>();
	Bus16& addr_bus = b.Add<Bus16>();
	FlipFlopJK& master_ff0 = b.Add<FlipFlopJK>();
	FlipFlopJK& master_ff1 = b.Add<FlipFlopJK>();
	IC6502& cpu = b.Add<IC6502>();
	IC6850& comm = b.Add<IC6850>();
	IC62256& ram32k = b.Add<IC62256>();
	IC27256& eprom32k = b.Add<IC27256>();
	IC74LS138& demux = b.Add<IC74LS138>();
	IC74LS163& count4bit = b.Add<IC74LS163>();
	ICMAX232& serial = b.Add<ICMAX232>();
	Crystal& crystal = b.Add<Crystal>();*/
	
	
}


NAMESPACE_TOPSIDE_END

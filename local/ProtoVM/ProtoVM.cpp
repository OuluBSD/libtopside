#include "ProtoVM.h"


CONSOLE_APP_MAIN {
	Machine		mach;
	int			max_ticks = 10;
	
	
	// http://searle.x10host.com/uk101/uk101.html
	// Next: http://searle.x10host.com/zx80/zx80.html
	
	Pcb& b = mach.AddPcb();
	
	Port& power = mach.GetPower();
	power.SetCount(2);
	Pin& ground = power.GetPin(0).SetReference(0);
	Pin& vcc = power.GetPin(1).SetReference(1);
	PushButtonComp& reset = b.Add<PushButtonComp>();
	Resistor4k7& r4k7 = b.Add<Resistor4k7>();
	ENode& reset_ground = b.AddNode("reset ground");
	ENode& reset_vcc = b.AddNode("reset vcc");
	ENode& cpu_rw = b.AddNode("cpu rw");
	ENode& ram_read = b.AddNode("cpu rw");
	ENode& comm_cs = b.AddNode("comm cs");
	ENode& ram_cs = b.AddNode("ram cs");
	ElcNand& ram_read_nand = b.Add<ElcNand>();
	ElcNand& ram_write_nand = b.Add<ElcNand>();
	ElcNand& eprom32k_cs_nand = b.Add<ElcNand>();
	ElcNor& eprom32k_cs_nor0 = b.Add<ElcNor>();
	ElcNor& eprom32k_cs_nor1 = b.Add<ElcNor>();
	ElcNot& ram_write_not = b.Add<ElcNot>();
	ElcNot& comm_not = b.Add<ElcNot>();
	ElcNot& eprom32k_cs_not = b.Add<ElcNot>();
	Bus8& data_bus = b.Add<Bus8>();
	Bus16& addr_bus = b.Add<Bus16>();
	IC6502& cpu = b.Add<IC6502>();
	IC6850& comm = b.Add<IC6850>();
	IC62256& ram32k = b.Add<IC62256>();
	IC27256& eprom32k = b.Add<IC27256>();
	IC74LS138& demux = b.Add<IC74LS138>();
	IC74LS163& count4bit = b.Add<IC74LS163>();
	ICMAX232& serial = b.Add<ICMAX232>();
	Crystal4& crystal = b.Add<Crystal4>();
	
	try {
		ground >> reset >> reset_ground;
		reset_ground >> r4k7 >> reset_vcc;
		reset_ground >> cpu["~Res"];
		
		reset_vcc >> vcc;
		cpu["~NMI"] >> reset_vcc;
		cpu["~IRQ"] >> reset_vcc;
		cpu["Rdy"] >> reset_vcc;
		
		cpu["D0,8"] >> data_bus;
		ram32k["D0,8"] >> data_bus;
		eprom32k["D0,8"] >> data_bus;
		comm["D0,8"] >> data_bus;
		
		cpu["A0,16"] >> addr_bus;
		ram32k["A0,16"] >> addr_bus;
		eprom32k["A0,16"] >> addr_bus;
		
		cpu["~RW"] >> cpu_rw >> comm["~RW"];
		cpu_rw >> ram_write_not >> ram_write_nand[0];
		cpu_rw >> ram_read_nand[0];
		
		ram_read_nand[2] >> ram_read;
		ram_read >> ram32k["~WR"];
		ram_read >> eprom32k["~OE"];
		
		// TODO >> cpu["Phi in"];
		// cpu phi2 out
		// comm E
		
		addr_bus[12] >> demux["A"];
		addr_bus[13] >> demux["B"];
		addr_bus[14] >> demux["C"];
		addr_bus[15] >> ram_cs;
		ram_cs >> demux["G1"];
		
		ground >> demux["~G2b"];
		ground >> demux["~G2a"];
		
		// SPARE DECODER O/P
		//demux["~0"] >>
		//demux["~1"] >>
		//demux["~4"] >>
		//demux["~5"] >>
		//demux["~6"] >>
		
		// Address 0000-7FFF (RAM)
		ram_cs >> ram32k["~CS"];
		
		// Address A000-BFFF (BASIC)
		demux["~2"] >> eprom32k_cs_nand[0];
		demux["~3"] >> eprom32k_cs_nand[1];
		eprom32k_cs_nand[2] >> eprom32k_cs_nor1[1];
		eprom32k_cs_nor1[2] >> eprom32k["~CS"];
		
		// Address F800-FFFF (MONITOR)
		demux["~7"] >> comm_cs;
		comm_cs >> comm_not >> comm["CS0"];
		comm_cs >> eprom32k_cs_nor0[1];
		eprom32k_cs_nor0[2] >> eprom32k_cs_nor1[0];
		addr_bus[11] >> eprom32k_cs_not >> eprom32k_cs_nor0[0];
		
		eprom32k["Vpp"] >> vcc;
		
		
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
	
	mach.Init();
	
	for(int i = 0; i < max_ticks; i++) {
		
		mach.Tick();
		
	}
}

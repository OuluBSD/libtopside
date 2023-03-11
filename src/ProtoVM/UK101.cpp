#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


void SetupUK101(Machine& mach) {

	// http://searle.x10host.com/uk101/uk101.html
	// Next: http://searle.x10host.com/zx80/zx80.html
	// Then: https://hackaday.io/project/168194-interak-z80-computer-documentation
	
	Pcb& b = mach.AddPcb();
	
	Port& power = mach.GetPower();
	power.SetCount(2);
	Pin& ground = power.GetPin(0).SetReference(0);
	Pin& vcc = power.GetPin(1).SetReference(1);
	ground.SetName("ground");
	vcc.SetName("vcc");
	
	PushButtonComp& reset = b.Add<PushButtonComp>();
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
	Crystal& crystal = b.Add<Crystal>();
	
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
		addr_bus >> ram32k["A0,16"];
		addr_bus >> eprom32k["A0,16"];
		
		cpu["~RW"] >> cpu_rw >> comm["~RW"];
		cpu_rw >> ram_write_not >> ram_write_nand[0];
		cpu_rw >> ram_read_nand[0];
		ram_write_nand[2] >> ram32k["~WR"];
		
		ram_read_nand[2] >> ram_read;
		ram_read >> ram32k["~OE"];
		ram_read >> eprom32k["~OE"];
		
		phi_in >> cpu["Phi in"];
		cpu["Phi2 out"] >> phi_out;
		phi_out >> ram_read_nand[1];
		phi_out >> ram_write_nand[1];
		phi_out >> comm["E"];
		
		addr_bus[12] >> demux["A"];
		addr_bus[13] >> demux["B"];
		addr_bus[14] >> demux["C"];
		addr_bus[15] >> ram_cs;
		ram_cs >> demux["G1"];
		
		ground >> demux["~G2b"];
		ground >> demux["~G2a"];
		
		// SPARE DECODER O/P
		demux.NotRequired("~0");
		demux.NotRequired("~1");
		demux.NotRequired("~4");
		demux.NotRequired("~5");
		demux.NotRequired("~6");
		
		// Address 0000-7FFF (RAM)
		ram_cs >> ram32k["~CS"];
		
		// Address A000-BFFF (BASIC)
		demux["~2"] >> eprom32k_cs_nand[0];
		demux["~3"] >> eprom32k_cs_nand[1];
		eprom32k_cs_nand[2] >> eprom32k_cs_nor1[1];
		eprom32k_cs_nor1[2] >> eprom32k["~CS"];
		
		// Address F800-FFFF (MONITOR)
		demux["~7"] >> comm_cs0;
		comm_cs0 >> comm_not >> comm["CS0"];
		comm_cs0 >> eprom32k_cs_nor0[1];
		eprom32k_cs_nor0[2] >> eprom32k_cs_nor1[0];
		addr_bus[11] >> eprom32k_cs_not >> eprom32k_cs_nor0[0];
		
		eprom32k["Vpp"] >> vcc;
		
		addr_bus[11] >> comm["~CS2"];
		addr_bus[0] >> comm["RS"];
		
		// Communications (6850) power
		ground >> comm["~DCD"];
		ground >> comm["~CTS"];
		comm["CS1"] >> vcc;
		
		
		// MAX232
		ground >> serial_gnd_cap >> serial["-V"];
		serial["+V"] >> serial_vcc_cap >> vcc;
		serial["R20"] >> comm["Rx"];
		comm["Tx"] >> serial["T2I"];
		serial["-C1"] >> serial_cap1 >> serial["+C1"];
		serial["-C2"] >> serial_cap2 >> serial["+C2"];
		serial["Gnd"] >> serial_cap3 >> serial["Vcc"]; // from internal charger
		serial.NotRequired("T2O");
		serial.NotRequired("R1I");
		
		// 4-bit counter
		ground >> count4bit["Da"];
		ground >> count4bit["Db"];
		ground >> count4bit["Dc"];
		ground >> count4bit["Dd"];
		count4bit["Ep"] >> vcc;
		count4bit["Et"] >> vcc;
		count4bit["~Ld"] >> vcc;
		count4bit["Qd"] >> counter_qd >> counter_nand[0];
		count4bit["Qc"] >> counter_nand[1];
		counter_nand >> count4bit["~Clr"];
		counter_qd >> comm["Rx clk"];
		counter_qd >> comm["Tx clk"];
		master_clk >> count4bit["Clk"];
		
		
		// Master clock
		master_clk >> master_ff0["Ck"];
		master_ff0["~Pr"] >> vcc;
		master_ff0["~Clr"] >> vcc;
		master_ff0["D"] >> master_ck;
		master_ff0["~Q"] >> master_ck;
		
		master_ck >> master_ff1["Ck"];
		master_ff1["~Pr"] >> vcc;
		master_ff1["~Clr"] >> vcc;
		master_ff1["D"] >> phi_in;
		master_ff1["~Q"] >> phi_in;
		
		// 4Mhz clock
		crystal >> crystal_a;
		crystal_a >> crystal_not0 >> crystal_b;
		crystal_a >> crystal_r0 >> crystal_b;
		crystal_b >> crystal_cap >> crystal_c;
		crystal_c >> crystal_not1 >> crystal_d;
		crystal_c >> crystal_r1 >> crystal_d;
		crystal_d >> crystal_not2 >> master_clk;
		crystal_d >> crystal;
		
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
}


NAMESPACE_TOPSIDE_END

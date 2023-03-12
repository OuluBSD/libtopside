#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN

/*
Links:
- http://searle.x10host.com/6502/Simple6502.html
- https://satoshinm.github.io/blog/180113_stm32_6502_pill_6502_8_bit_6502_cpu_and_6850_acia_emulation_on_the_stm32_blue_pill_to_run_microsoft_basic_from_1977.html
- https://hackaday.io/project/167711-3-chip-z80-design/log/170107-emulating-the-6850-with-a-psoc
*/

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
	IC62256& ram = b.Add<IC62256>();
	Bus8& data_bus = b.Add<Bus8>();
	Bus16& addr_bus = b.Add<Bus16>();
	
	ElcNand& mem_nread = b.Add<ElcNand>();
	ElcNand& ram_nwrite0 = b.Add<ElcNand>();
	ElcNand& ram_nwrite1 = b.Add<ElcNand>();
	ElcNand& rom_enable = b.Add<ElcNand>();
	
	try {
		cpu["A0,16"] >> addr_bus;
		cpu["D0,8"] >> data_bus;
		addr_bus >> rom["A0,14"];
		data_bus >> rom["D0,8"];
		addr_bus >> ram["A0,15"];
		data_bus >> ram["D0,8"];
		
		vcc >> cpu["~Res"]; // actually requires resistor
		vcc >> cpu["~NMI"];
		vcc >> cpu["~IRQ"];
		vcc >> cpu["~SO"];
		vcc >> cpu["RDY"];
		
		cpu["R~W"] >> mem_nread["I0"];
		cpu["PHI2 OUT"] >> mem_nread["I1"];
		mem_nread["O"] >> ram["~OE"];
		mem_nread["O"] >> rom["~OE"];
		
		cpu["R~W"] >> ram_nwrite0["I0"];
		cpu["R~W"] >> ram_nwrite0["I1"];
		ram_nwrite0["O"] >> ram_nwrite1["I1"];
		cpu["PHI2 OUT"] >> ram_nwrite1["I0"];
		ram_nwrite1["O"] >> ram["~WE"];
		
		cpu["A15"] >> ram["~CE"];
		
		cpu["A14"] >> rom_enable["I0"];
		cpu["A15"] >> rom_enable["I1"];
		rom_enable["O"] >> rom["~CE"];
	}
	catch (Exc e) {
		LOG("error: " << e);
	}
}

NAMESPACE_TOPSIDE_END

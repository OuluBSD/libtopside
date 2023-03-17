#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


void SetupMiniMax8085(Machine& mach) {
	
	// http://www.malinov.com/Home/sergeys-projects/minimax8085
	
	Pcb& b = mach.AddPcb();
	
	Pin& ground = b.Add<Pin>("ground").SetReference(0);
	Pin& vcc = b.Add<Pin>("vcc").SetReference(1);
	IC8085& cpu = b.Add<IC8085>();
	IC74F573& latch = b.Add<IC74F573>();
	IC27128& rom = b.Add<IC27128>();
	ICDS1210& nvram_ctrl = b.Add<ICDS1210>();
	IC62256& nvram = b.Add<IC62256>();
	IC8251A& usart_console_conn = b.Add<IC8251A>();
	ICMAX232& serial = b.Add<ICMAX232>();
	ICGAL16V8& spld_glue_logic = b.Add<ICGAL16V8>();
	
	Resistor4k7& pull_up = b.Add<Resistor4k7>();
	Resistor4k7& pull_down = b.Add<Resistor4k7>();
	
	{
		cpu["READY"] >> pull_up[1];
		cpu["HOLD"] >> pull_down[3];
		cpu["INTR"] >> pull_down[5];
		cpu["RST5_5"] >> pull_down[4];
		TODO/*cpu["RST6_5"] >> ;
		cpu["RST7_5"] >> pull_down[2];
		cpu["TRAP"] >> pull_down[1];
		cpu["~RES_IN"] >> ;
		cpu[""] >> ;
		
		cpu[""] >> pull_up[];
		cpu[""] >> pull_up[];*/
	}
}


NAMESPACE_TOPSIDE_END

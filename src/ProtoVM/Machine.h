#pragma once

NAMESPACE_TOPSIDE_BEGIN


struct Machine {
	Array<Pcb> pcbs;
	Port power;
	LinkMap l;
	
	bool Init();
	bool Tick();
	bool RunInitOps();
	bool RunRtOps();
	
	Pcb& AddPcb();
	Port& GetPower() {return power;}
	
};



NAMESPACE_TOPSIDE_END

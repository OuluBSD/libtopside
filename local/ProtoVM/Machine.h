#pragma once


struct Machine {
	Array<Pcb> pcbs;
	Port power;
	
	bool Init();
	void Tick();
	
	Pcb& AddPcb();
	Port& GetPower() {return power;}
	
};


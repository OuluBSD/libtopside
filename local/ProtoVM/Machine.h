#pragma once


/*#define IFACE_BUS_BW		8
#define IFACE_BUS_BYTES		1
#define IFACE_SLOTS			8
#define	COMPUTING_BUS_BW	8
#define	INS_DEC_COUNT		3
typedef byte msize;
typedef byte csize;



struct Board;

enum {
	IR_IRCTRL,
	IR_MEM,
	IR_DISKCTRL,
	ID_VIDEO,
	ID_CPU,
	
};

struct InterfaceBus {
	msize	addr;
	msize	value;
	byte	iface_id;
	Board*	slots[IFACE_SLOTS];
	bool	interrupt;
	
	
	void Attach(Board* b);
};

struct Backplane {
	InterfaceBus	ibus;
	
	
	
};

struct Board {
	InterfaceBus*	ibus = 0;
	
	
};

struct InterruptController : public Board {
	
	
	void Tick();
	
};

struct MemoryBoard : public Board {
	
	
	
	void Tick();
	
};

struct DiskControllerBoard : public Board {
	
	
	
	void Tick();
	
};

struct VideoBoard : public Board {
	
	
	
	void Tick();
	
};




struct ComputingBus {
	csize	addr;
	csize	value;
	
	
	void Tick();
	
};

struct ComputingCache1 {
	
	
};

struct DecodedInstruction {
	
	
};

struct ComputerBoard : public Board {
	ComputingBus			iface_bus;
	ComputingCache1			cache1;
	
	ComputingBus			pipeline_bus;
	DecodedInstruction		ins[INS_DEC_COUNT];
	
	void Tick();
	
};
*/

struct Machine {
	Array<Pcb> pcbs;
	Port power;
	
	bool Init();
	void Tick();
	
	Pcb& AddPcb();
	Port& GetPower() {return power;}
	
};


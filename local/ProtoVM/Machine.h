#pragma once

#if 0

#define IFACE_BUS_BW		8
#define IFACE_BUS_BYTES		1
#define IFACE_SLOTS			8
#define	COMPUTING_BUS_BW	8
#define	INS_DEC_COUNT		3
typedef byte msize;
typedef byte csize;

/*

Vesiputousmalli:
	- src/sink
	- väylää pitkin valutettaisiin ...
	- väylien hierarkia
		- cpu:ssa useampi
	- väylässä hierarkiset statusbitit
		- väylän interrupt olisi pudottamassa jotain
		- väylän 'virtuaaliväylä' varaa väylää
		- väylän väliltä pudotetaan jotain väylän ulkopuolelle
			- tai väylämanagerille (interrupt ctrl)
		- väylän väli on vapaa
		- väylän funktio-koodit kuuluu tiettyihin statusbitteihin
	
Hierarkia:
	interface bus
		bios
			board bus
				memory
		computer
			board bus
				cache1
				processing bus
					registers
					bit shifter
					add/sub
					multiplier
					divider
					floating point number math
		memory
			board bus
		disk controller
			board bus
		video
			board bus
*/

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

struct Machine {
	Backplane				back;
	InterruptController		ir;
	MemoryBoard				mem;
	DiskControllerBoard		disk;
	VideoBoard				video;
	ComputerBoard			computer;
	
	
	void Tick();
	
		
};

#endif

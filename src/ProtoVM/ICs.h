#ifndef _ProtoVM_ICs_h_
#define _ProtoVM_ICs_h_

NAMESPACE_TOPSIDE_BEGIN

// Resources:
//  - https://github.com/floooh/chips


// 8-bit microprocessor
// https://www.princeton.edu/~mae412/HANDOUTS/Datasheets/6502.pdf
class IC6502 : public Chip {
	RTTI_DECL1(IC6502, Chip)
	
	static constexpr int A0  =  0;
	static constexpr int D0  = 16;
	static constexpr int RW  = 24;     // out: memory read or write access
	static constexpr int SYNC = 25;    // out: start of a new instruction
	static constexpr int IRQ = 26;     // in: maskable interrupt requested
	static constexpr int NMI = 27;     // in: non-maskable interrupt requested
	static constexpr int RDY = 28;     // in: freeze execution at next read cycle
	static constexpr int AEC = 29;     // in, m6510 only, put bus lines into tristate mode, not implemented
	static constexpr int RES = 30;     // request RESET
	
	m6502_t cpu;
	uint64_t pins;
	uint64_t in_pins, in_pins_mask;
	
	bool reading = 0;
	bool sync = 0;
	byte in_data = 0;
	uint16 in_addr = 0;
	
	bool verbose = true;
	
	void SetPin(int i, bool b);
	
public:
	IC6502();
	
	bool Tick() override;
	bool Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) override;
	bool PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) override;
	
};

// 8-bit microprocessor
// https://datasheetspdf.com/pdf-file/1110522/Zilog/Z80/1
class Z80 : public Chip {
	RTTI_DECL1(Z80, Chip)
	
	
public:
	Z80();
	
	
};

// 8-bit microprocessor
// https://www.inf.pucrs.br/~calazans/undergrad/orgcomp_EC/mat_microproc/intel-8085_datasheet.pdf
class IC8085 : public Chip {
	RTTI_DECL1(IC8085, Chip)
	
public:
	IC8085();
	
};


// Asynchronous communications interface
// http://dunfield.classiccmp.org/r/6850.pdf
class IC6850 : public Chip {
	RTTI_DECL1(IC6850, Chip)
	
	
public:
	IC6850();
	
};

// IC 74LS138 is a 3 to 8 line decoder integrated circuit
// https://www.elprocus.com/3-to-8-line-decoder-74ls138-ic-pin-configuration-features-circuit-and-applications/
class IC74LS138 : public Chip {
	RTTI_DECL1(IC74LS138, Chip)
	
public:
	IC74LS138();
	
};

// Synchronous 4-bit Binary Counters
// https://www.futurlec.com/74LS/74LS163.shtml
class IC74LS163 : public Chip {
	RTTI_DECL1(IC74LS163, Chip)
	
	
public:
	IC74LS163();
	
	
};

// 5-V dual channel 120kbps RS-232 line driver/receiver with +/-9V output & +/-2-kV ESD protection
// https://www.ti.com/lit/ds/symlink/max232.pdf?ts=1678466760327&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FMAX232%253Futm_source%253Dgoogle%2526utm_medium%253Dcpc%2526utm_campaign%253Dasc-null-null-GPN_EN-cpc-pf-google-wwe%2526utm_content%253DMAX232%2526ds_k%253DMAX232%2526DCM%253Dyes%2526gclid%253DCj0KCQiAx6ugBhCcARIsAGNmMbg84coiHawwpM5Iy0DyHvvFKjYU8STcvydLQyb_oyOmdpGVFv6lxbIaApqBEALw_wcB%2526gclsrc%253Daw.ds
class ICMAX232 : public Chip {
	RTTI_DECL1(ICMAX232, Chip)
	
	
public:
	ICMAX232();
	
	
};

// 3-STATE Octal Bus Transceiver
// https://www.futurlec.com/74LS/74LS245.shtml
class IC74LS245 : public Chip {
	RTTI_DECL1(IC74LS245, Chip)
	
	
public:
	IC74LS245();
	
	
	
};

// Octal D-Type Latch with 3-STATE Outputs
// https://www.mouser.com/datasheet/2/149/74F573-91054.pdf
class IC74F573 : public Chip {
	RTTI_DECL1(IC74F573, Chip)
	
public:
	IC74F573();
	
};

// Nonvolatile Controller Chip
// https://www.analog.com/media/en/technical-documentation/data-sheets/ds1210.pdf
class ICDS1210 : public Chip {
	RTTI_DECL1(ICDS1210, Chip)
	
public:
	ICDS1210();
	
};

// Programmable Communication Interface
// https://pdf1.alldatasheet.com/datasheet-pdf/view/66096/INTEL/8251A.html
class IC8251A : public Chip {
	RTTI_DECL1(IC8251A, Chip)
	
public:
	IC8251A();
	
};

// High Performance E 2 CMOS PLD Generic Array Logic
// https://ece-classes.usc.edu/ee459/library/datasheets/16v8.pdf
class ICGAL16V8 : public Chip {
	RTTI_DECL1(ICGAL16V8, Chip)
	
public:
	ICGAL16V8();
	
};


NAMESPACE_TOPSIDE_END

#endif

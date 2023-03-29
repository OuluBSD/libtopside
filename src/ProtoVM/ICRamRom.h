#ifndef _ProtoVM_ICRamRom_h_
#define _ProtoVM_ICRamRom_h_

NAMESPACE_TOPSIDE_BEGIN


class ICMem8Base : public Chip {
	RTTI_DECL1(ICMem8Base, Chip)
	
	static constexpr int A0 = 0;
	static constexpr int D0 = 16;
	static constexpr int OE = 24;
	static constexpr int CS = 25;
	static constexpr int WR = 26;
	
	byte* data = 0;
	int size = 0;
	
	uint16 addr = 0;
	bool writing = 0;
	bool reading = 0;
	bool enabled = 0;
	bool writable = 0;
	
	byte in_data = 0;
	uint16 in_addr = 0;
	bool in_writing = 0;
	bool in_reading = 0;
	bool in_enabled = 0;
	
public:
	ICMem8Base(byte* data, int size, bool writable);
	
	bool Tick() override;
	bool Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) override;
	bool PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) override;
};


template <int I, bool WRITABLE>
class ICMem8T : public ICMem8Base {
	RTTI_DECL1(ICMem8T, ICMem8Base)
	using MemCls = ICMem8T<I,WRITABLE>;
	
	static constexpr int size = I;
	
	byte data[I];
	
	
public:
	ICMem8T() : ICMem8Base(data, size, WRITABLE) {}
	
};




// 32Kx8 bit Low Power CMOS Static RAM
// https://www.futurlec.com/Memory/62256.shtml
class IC62256 : public ICMem8T<32768, true> {
public:
	RTTI_DECL1(IC62256, MemCls)
	IC62256() {}
};

// NMOS 256 Kbit (32Kb x 8) UV EPROM
// https://www.futurlec.com/Memory/27256_Datasheet.shtml
class IC27256 : public ICMem8T<32768, false> {
public:
	RTTI_DECL1(IC27256, MemCls)
	IC27256() {}
};

// 128K (16kb x 8) 150ns NMOS EPROM
// https://www.futurlec.com/Memory/27128-150.shtml
class IC27128 : public ICMem8T<16384, false> {
public:
	RTTI_DECL1(IC27128, Chip)
	IC27128() {}
};


NAMESPACE_TOPSIDE_END

#endif

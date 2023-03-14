#ifndef _ProtoVM_Bus_h_
#define _ProtoVM_Bus_h_

NAMESPACE_TOPSIDE_BEGIN


template <int Width>
class Bus : public ElcBase {
	RTTI_DECL1(Bus, ElcBase);
	
	static constexpr int BYTES = Width / 8 + ((Width % 8) ? 1 : 0);
	static constexpr int BITS = Width % 8;
	
	bool processing = false;
	byte data[BYTES];
	bool verbose = 1;
	
public:
	Bus() {
		for(int i = 0; i < Width; i++)
			AddBidirectional(IntStr(i)).SetMultiConn();
	}
	
	Bus& Verbose(bool b=true) {verbose = b; return *this;}
	
	int GetMemorySize() const override {return Width / 8 + ((Width % 8) == 0 ? 0 : 1);}
	
	bool Tick() override {
		if (verbose) {
			LOG("Bus::Tick(" << GetName() << "): " << HexString((const char*)data, BYTES));
		}
		for(int i = 0; i < BYTES; i++)
			data[i] = 0;
		return true;
	}
	
	bool Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) override {
		if (processing) {
			LOG("error: recursive processing");
			return false;
		}
		
		if (type == WRITE || type == RW) {
			if (!dest.PutRaw(dest_conn_id, this->data, bytes, bits))
				return false;
		}
		
		if (type == READ || type == RW) {
			ProcessType dest_type = ProcessType::INVALID;
			switch(type) {
				case READ:      dest_type = WRITE;  break;
				case RW:        dest_type = WRITE; break;
				default: break;
			}
			processing = true;
			bool ret = dest.Process(dest_type, bytes, bits, dest_conn_id, *this, conn_id);
			processing = false;
			return ret;
		}
		return true;
	}
	
	bool PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) override {
		if (conn_id == 0) {
			if (BITS == 0) {
				ASSERT(data_bytes == BYTES && data_bits == 0);
				int copy_bytes = min(data_bytes, BYTES);
				memcpy(this->data, data, copy_bytes);
				return true;
			}
			else {
				TODO
			}
		}
		LOG("error: Bus: unexpected conn id");
		return false;
	}
};


using Bus8 = Bus<8>;
using Bus16 = Bus<16>;


class InterakBus : public ElcBase {
	RTTI_DECL1(InterakBus, ElcBase);
	
	
public:
	InterakBus();
	
};


NAMESPACE_TOPSIDE_END

#endif

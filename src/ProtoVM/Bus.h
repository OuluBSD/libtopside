#ifndef _ProtoVM_Bus_h_
#define _ProtoVM_Bus_h_


template <int Width>
class Bus : public ElcBase {
	RTTI_DECL1(Bus, ElcBase);
	
	static constexpr int bytes = Width / 8 + ((Width % 8) ? 1 : 0);
	
	bool processing = false;
	byte data[bytes];
	bool verbose = false;
	
public:
	Bus() {
		for(int i = 0; i < Width; i++)
			AddBidirectional(IntStr(i)).SetMultiConn();
	}
	
	Bus& Verbose(bool b=true) {verbose = b; return *this;}
	
	int GetMemorySize() const override {return Width / 8 + ((Width % 8) == 0 ? 0 : 1);}
	
	bool Tick() override {
		if (verbose) {
			LOG("Bus::Tick: value " << HexString((const char*)data, bytes));
		}
		return true;
	}
	
	bool Process(ProcessType type, byte sz, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) override {
		if (processing) {
			LOG("error: recursive processing");
			return false;
		}
		
		if (type == BYTE_WRITE || type == BIT_WRITE ||
			type == BYTE_RW    || type == BIT_RW) {
			if (!dest.PutRaw(dest_conn_id, this->data, bytes))
				return false;
		}
		
		if (type == BYTE_READ || type == BIT_READ ||
			type == BYTE_RW    || type == BIT_RW) {
			ProcessType dest_type;
			switch(type) {
				case BYTE_READ: dest_type = BYTE_WRITE; break;
				case BIT_READ:  dest_type = BIT_WRITE;  break;
				case BYTE_RW:   dest_type = BYTE_WRITE; break;
				case BIT_RW:    dest_type = BIT_WRITE;  break;
				default: break;
			}
			processing = true;
			bool ret = dest.Process(dest_type, sz, dest_conn_id, *this, conn_id);
			processing = false;
			return ret;
		}
		return true;
	}
	
	bool PutRaw(uint16 conn_id, byte* data, int data_sz) override {
		if (conn_id == 0) {
			ASSERT(data_sz == bytes);
			int copy_sz = min(data_sz, bytes);
			memcpy(this->data, data, copy_sz);
			return true;
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


#endif

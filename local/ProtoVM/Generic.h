#ifndef _ProtoVM_Generic_h_
#define _ProtoVM_Generic_h_

/*
typedef enum {
	FN_NULL,
	
	MEM_WRITE_LEVEL0,
	MEM_WRITE_LEVEL1,
	MEM_WRITE_LEVEL2,
	MEM_WRITE_LEVEL_MAX = MEM_WRITE_LEVEL2,
	
} BusFunction;


class BusClient;
class BusData;

struct IfaceFlags {
	bool		interrupt = false;
	bool		write = false;
	
	BusClient*	client = 0;
	
	
	void		ClearTick();
};


class BusClient {
	
public:
	
	
	typedef enum {
		IDLE,
		WAITING_HOST,
		USER_FN0,
		USER_FN1,
		USER_FN2,
		USER_FN3,
		
	} Status;
	
	Bus*		bus = 0;
	Status		bus_status = IDLE;
	int			iface = -1;
	String		name;
	
	
	virtual			~BusClient() {}
	
	virtual void	Tick() {}
	
	void			RequestWrite();
	IfaceFlags&		GetIface();
	
protected:
	friend class Bus;
	
	
};

class BusData {
	union {
		uint64	a64;
		uint32	a32;
		uint16	a16;
		uint8	a8;
	};
	
	union {
		uint64	v64;
		uint32	v32;
		uint16	v16;
		uint8	v8;
	};
	BusFunction fn_code = FN_NULL;
	
	
	byte bw = 16;
public:
	
	void Set8(uint8 addr, uint8 value) {ASSERT(bw == 8); a8 = addr; v8 = value;}
	void Set16(uint16 addr, uint16 value) {ASSERT(bw == 16); a16 = addr; v16 = value;}
	void SetFunction(BusFunction fn) {fn_code = fn;}
	
	void Get16(uint16& addr, uint16& value) {ASSERT(bw == 16); addr = a16; value = v16;}
	BusFunction GetFunction() const {return fn_code;}
	
};

class Bus {
	
public:
	typedef enum {
		IDLE,
		WAITING_HOST,
		WAITING_USER,
		WAITING_USER_BUS_FN,
		
	} Status;
	
	
	Array<Bus>			sub;
	Array<BusClient>	clients;
	
	
	static const int MAX_COUNT = 16;
	
	IfaceFlags	ifaces[MAX_COUNT];
	String		name;
	BusData		data;
	Status		bus_status = IDLE;
	int			write_iface = -1;
	bool		interrupt = false;
	
	
	void		ClearTick();
	void		Tick();
	Bus&		Add(String name);
	int			FindInterruptIface() const;
	
	template <class T> T& AddClient(String name) {
		for(int i = 0; i < MAX_COUNT; i++) {
			IfaceFlags& f = ifaces[i];
			if (!f.client) {
				T* o = new T();
				o->iface = i;
				o->bus = this;
				clients.Add(o);
				return *o;
			}
		}
		Panic("all interfaces full");
		TODO
	}
	
};

struct Rom : public BusClient {
	
	
};

struct Memory : public BusClient {
	
	
};

struct RegisterVec : public BusClient {
	
	
};

struct BitShifter : public BusClient {
	
	
};

struct BinaryMath : public BusClient {
	
	
};

struct FloatMath : public BusClient {
	
	
};

struct VideoOutput : public BusClient {
	
	
};

struct TestSender : public BusClient {
	
	void Tick() override;
	
};

struct TestReceiver : public BusClient {
	
	void Tick() override;
	
};*/

/*struct Machine {
	Bus bus;
	
	
	void Init();
	void Tick();
	
};*/


#endif

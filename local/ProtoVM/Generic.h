#ifndef _ProtoVM_Generic_h_
#define _ProtoVM_Generic_h_


struct BusClient {
	
	
	
};



struct Bus {
	Array<Bus>			sub;
	Array<BusClient>	clients;
	
	struct BusIface {
		bool	interrupt = false;
		bool	write_lock = false;
	};
	
	static const int MAX_COUNT = 16;
	
	BusIface	ifaces[MAX_COUNT];
	bool		interrupt = false;
	
	
	Bus&		Add(String name);
	
	template <class T> T& AddClient(String name);
	
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

struct Machine {
	Bus bus;
	
	
	void Init() {
		Bus& iface_bus = bus;
		
		{
			Bus& bios_board = iface_bus.Add("bios board");
			{
				Rom& rom = bios_board.AddClient<Rom>("bios memory");
				
			}
			
			Bus& comp_board = iface_bus.Add("computer board");
			{
				Memory& cache1 = comp_board.AddClient<Memory>("cache1");
				
				Bus& proc_bus = comp_board.Add("processing bus");
				{
					RegisterVec& regs = proc_bus.AddClient<RegisterVec>("register vector");
					BitShifter& bshift = proc_bus.AddClient<BitShifter>("bit shifter");
					BinaryMath& bmath = proc_bus.AddClient<BinaryMath>("binary math");
					FloatMath& fmath = proc_bus.AddClient<FloatMath>("float math");
					
				}
			}
			
			Bus& mem_board = iface_bus.Add("memory board");
			{
				int chip_count = 10;
				
				for(int i = 0; i < chip_count; i++) {
					Memory& mem = mem_board.AddClient<Memory>("memory chip #" + IntStr(i));
					
					
				}
				
				
			}
			
			Bus& diskctl_board = iface_bus.Add("disk controller board");
			{
				Bus& disk_bus = diskctl_board.Add("disk bus");
				{
					
					
				}
				
			}
			
			Bus& video_board = iface_bus.Add("video board");
			{
				Bus& memory_bus = video_board.Add("memory bus");
				{
					VideoOutput& vout = memory_bus.AddClient<VideoOutput>("video output");
					Memory& mem = memory_bus.AddClient<Memory>("memory");
					
				}
				
				
			}
			
		}
		
	}
	
	
	void Tick();
	
};


#endif

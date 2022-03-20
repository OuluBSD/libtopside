#include "ProtoVM.h"


/*
void IfaceFlags::ClearTick() {
	interrupt = false;
	// not this: write = false;
}


void BusClient::RequestWrite() {
	ASSERT(bus_status == IDLE);
	IfaceFlags& bi = GetIface();
	bi.interrupt = true;
	bus_status = WAITING_HOST;
}

IfaceFlags& BusClient::GetIface() {
	return bus->ifaces[iface];
}




void Bus::ClearTick() {
	interrupt = false;
	
	for(int i = 0; i < MAX_COUNT; i++)
		ifaces[i].ClearTick();
	
	data.SetFunction(FN_NULL);
}

void Bus::Tick() {
	ClearTick();
	
	for (Bus& b : sub) {
		b.Tick();
	}
	
	for (BusClient& c : clients) {
		c.Tick();
	}
	
	if (bus_status == IDLE) {
		if (write_iface < 0) {
			write_iface = FindInterruptIface();
			if (write_iface >= 0) {
				ifaces[write_iface].write = true;
				bus_status = WAITING_USER_BUS_FN;
			}
		}
	}
	else if (bus_status == WAITING_USER_BUS_FN) {
		BusFunction fn = data.GetFunction();
		
		if (fn == FN_NULL) {
			// pass
		}
		else if (fn > MEM_WRITE_LEVEL0 && fn <= MEM_WRITE_LEVEL_MAX) {
			TODO
		}
		else {
			TODO // ignore explicitly
		}
	}
	else if (bus_status == WAITING_USER) {
		TODO
	}
	else {
		TODO
	}
}

Bus& Bus::Add(String name) {
	Bus& b = sub.Add();
	b.name = name;
	return b;
}

int Bus::FindInterruptIface() const {
	for(int i = 0; i < MAX_COUNT; i++) {
		const IfaceFlags& f = ifaces[i];
		if (f.interrupt && !f.write)
			return i;
	}
	return -1;
}
*/





/*void Machine::Init() {
	Bus& iface_bus = bus;
	
	{
		Bus& bios_board = iface_bus.Add("bios board");
		{
			Rom& rom = bios_board.AddClient<Rom>("bios memory");
			
			TestReceiver& test_recv = bios_board.AddClient<TestReceiver>("bus receiving tester");
			
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
				
				TestSender& test_send = proc_bus.AddClient<TestSender>("bus sending tester");
				
				
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

void Machine::Tick() {
	
	bus.Tick();
	
}*/




/*
void TestSender::Tick() {
	if (bus_status == IDLE) {
		RequestWrite();
		GetIface().interrupt = true;
	}
	else if (bus_status == WAITING_HOST) {
		IfaceFlags& f = GetIface();
		f.interrupt = true;
		if (f.write)
			bus_status = USER_FN0;
	}
	else if (bus_status == USER_FN0) {
		bus->data.SetFunction(MEM_WRITE_LEVEL2);
		bus_status = USER_FN1;
	}
	else TODO;
}

void TestReceiver::Tick() {
	if (bus_status == IDLE) {
		
	}
	else TODO
}
*/
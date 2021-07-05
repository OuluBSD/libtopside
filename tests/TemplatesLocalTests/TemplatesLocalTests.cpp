#include "TemplatesLocalTests.h"

NAMESPACE_TOPSIDE_BEGIN
using namespace TS::ECS;



bool SimpleDebugInitializer() {
	SetCoutLog();
	
	return true;
}



/*
To debug reference bugs, uncomment:
	- SetDebugRefVisits
	- RefDebugVisitor::Static().DumpUnvisited();
You'll see something like this in log
	0:	[0x7FFFFFFFE488]
	1:	[0x7FFFFFFFE478]
	2:	[0x7FFFFFFFE460]
	3:	[0x80AE80688]
	4:	[0x80AE57610]
	5:	[0x80AE43230]
	6:	[0x7FFFFFFFE2A8]
	7:	[0x7FFFFFFFE200]
	8:	[0x7FFFFFFFE138]
Take any address and put to BreakRefAdd
*/





void Main() {
	SetCoutLog();
	const auto& cmd = CommandLine();
	if (cmd.IsEmpty()) {
		LOG("App requires eon arguments");
		return;
	}
	String eon_file = cmd[0];
	
	Ecs::Factory::Dump();
	
	TypeExtCls t;
	
	REG_EXT(TestCustomer,			CUSTOMER,		CENTER,RECEIPT,		CENTER,ORDER,	CENTER,ORDER);
	REG_EXT(TestInputCustomer,		CUSTOMER,		CENTER,RECEIPT,		CENTER,ORDER,	CENTER,ORDER);
	REG_EXT(TestOutputCustomer,		CUSTOMER,		CENTER,RECEIPT,		CENTER,ORDER,	CENTER,ORDER);
	REG_EXT(TestRealtimeSrc,		INPUT,			CENTER,ORDER,		CENTER,AUDIO,	CENTER,AUDIO);
	REG_EXT(TestRealtimeSink,		OUTPUT,			CENTER,AUDIO,		CENTER,AUDIO,	CENTER,RECEIPT);
	
	
	//BreakRefAdd(0x802859038);
	
	
	if (!SimpleDebugInitializer())
		Exit(1);
	
	MAKE_STATIC(MachineVerifier, verifier);
	{
		verifier.AddSystem<RegistrySystem>();
		verifier.AddSystem<EntityStore>();
		verifier.AddSystem<ComponentStore>();
		verifier.AddSystem<ExtSystem>();
		verifier.AddSystem<EonLoader>();
		
		auto& ent		= verifier.GetRoot().AddPool("tester").AddPool("generator").AddEntity();
		auto& customer	= ent.AddExtComponentWith<TestCustomer>		(VD(CENTER,ORDER));
		auto& src		= ent.AddExtComponentWith<TestRealtimeSrc>	(VD(CENTER,AUDIO));
		auto& sink		= ent.AddExtComponentWith<TestRealtimeSink>	(VD(CENTER,RECEIPT));
		customer << src << sink << customer;
		src.SetSourceFormat(GetDefaultFormat(VD(CENTER,AUDIO)));
		sink.SetSinkFormat(GetDefaultFormat(VD(CENTER,AUDIO)));
		
	}
	
	VectorMap<String,Object> args;
	args.Add("MACHINE_TIME_LIMIT", 3);
	
	Ecs::DebugMain(eon_file, args, &verifier);
}














bool TestRealtimeSrc::Initialize(const Eon::WorldState& ws)  {
	internal_fmt.SetAudio(SoundSample::U8_LE, 2, 44100, 777);
	time = 0;
	return true;
}

void TestRealtimeSrc::Uninitialize()  {
	
}

void TestRealtimeSrc::Forward(FwdScope& fwd) {
	RTLOG("TestRealtimeSrc::Forward");
}

void TestRealtimeSrc::StorePacket(Packet& p) {
	RTLOG("TestRealtimeSrc::StorePacket: time=" << time << ", fmt=" << internal_fmt.ToString());
	ASSERT_(!p->GetFormat().IsValid(), "Packed shouldn't be initialized before this");
	PacketValue& pv = *p;
	pv.SetFormat(internal_fmt);
	
	Vector<byte>& data = pv.Data();
	data.SetCount(internal_fmt.GetFrameSize());
	for(byte& dst : data)
		dst = rolling_value++;
	
	time += internal_fmt.GetFrameSeconds();
}









bool TestRealtimeSink::Initialize(const Eon::WorldState& ws) {
	
	flag.Start(1);
	Thread::Start(THISBACK(IntervalSinkProcess));
	return true;
}

void TestRealtimeSink::Uninitialize() {
	flag.Stop();
}

void TestRealtimeSink::IntervalSinkProcess() {
	RTLOG("TestRealtimeSink::IntervalSinkProcess: starts");
	ExtComponent& base = GetParent();
	Ecs::Format fmt =  base.GetValue().GetFormat();
	Ecs::AudioFormat& afmt = fmt;
	Vector<byte> data;
	data.SetCount(fmt.GetFrameSize());
	double step_s = fmt.GetFrameSeconds();
	TimeStop ts;
	bool do_log = false;
	#ifdef DEBUG_RT_PIPE
	do_log = true;
	#endif
	int dbg_total_samples = 0;
	int dbg_total_bytes = 0;
	bool fail = false;
	
	while (flag.IsRunning()) {
		double t = ts.Seconds();
		
		if (t < step_s) {
			Sleep(1);
			continue;
		}
		ts.Reset();
		
		RTLOG("TestRealtimeSink::IntervalSinkProcess: trying to consume " << data.GetCount());
		
		if (do_log) {
			Ecs::Value& sink = base.GetSinkValue();
			Ecs::PacketBuffer& sink_buf = sink.GetBuffer();
			int total_bytes = 0;
			int total_ch_samples = 0;
			for(Packet& p : sink_buf) {
				total_bytes += p->GetSizeBytes();
				total_ch_samples += p->GetSizeChannelSamples();
			}
			String s;
			s   << "TestRealtimeSink::IntervalSinkProcess: sink has "
				<< sink_buf.GetCount() << " packets, "
				<< total_bytes << " total bytes, "
				<< total_ch_samples << " total ch samples";
			RTLOG(s);
		}
		
		if (!base.ForwardMem(data.Begin(), data.GetCount())) {
			RTLOG("TestRealtimeSink::IntervalSinkProcess: error: could not get consumable data");
			fail = true;
			break;
		}
		
		// Verify data
		if (afmt.type == ts::Ecs::BinarySample::FLT_LE) {
			float* it = (float*)(void*)data.begin();
			float* end = (float*)(void*)data.end();
			int dbg_i = 0;
			int dbg_count = end - it;
			for (; it != end; ++it, ++dbg_i) {
				float f0 = *it;
				float f1 = rolling_value++ / 255.0 * 2.0 - 1.0;
				ASSERT(IsClose(f0, f1));
			}
			dbg_total_samples += dbg_count;
			dbg_total_bytes += dbg_count * 4;
		}
	}
	RTLOG("TestRealtimeSink::IntervalSinkProcess: stops. total-samples=" << dbg_total_samples << ", total-bytes=" << dbg_total_bytes);
	if (!fail) {LOG("TestRealtimeSink::IntervalSinkProcess: success!");}
	else       {LOG("TestRealtimeSink::IntervalSinkProcess: fail :(");}
	
	flag.DecreaseRunning();
}

void TestRealtimeSink::Forward(FwdScope& fwd) {
	RTLOG("TestRealtimeSink::Forward");
	
}

void TestRealtimeSink::StorePacket(Packet& p) {
	RTLOG("TestRealtimeSink::StorePacket");
	p->SetFormat(GetParent()->GetSourceValue().GetFormat());
}









	
NAMESPACE_TOPSIDE_END

#ifdef flagGUI
GUI_APP_MAIN {TS::Main();}
#else
CONSOLE_APP_MAIN {TS::Main();}
#endif


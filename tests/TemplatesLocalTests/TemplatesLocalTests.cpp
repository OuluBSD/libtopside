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




/*
 1:
    - customer
    - AudioInputComponent
    - AudioOutputComponent
*/
const char* center_str = R"EON_CODE(

loop tester.generator: {
	customer.id.ABCD: true;
	customer.id.EFGH: true;
	center.audio.src: true;
	center.audio.sink: true;
	center.audio.sink.realtime: true;
};

)EON_CODE";


/*
1:
	- customer
    - AudioInputComponent
    - CenterSideOutput(Perma)
2:
	- customer
	- PermaSideInput(Center)
	- FileWriter
*/
const char* perma_str = R"EON_CODE(

sidechain tester: {
	
	loop generator: {
		center.audio.generator: true;
		center.perma.audio.side.out: true;
		
		return has.generator: true;
	};
	
	loop writer: {
		has.generator: true;
		
		perma.center.audio.side.in: true;
		perma.audio.sink.realtime: true;
		
		return has.writer: true;
	};
	
};

)EON_CODE";


/*
 1:
    - customer
    - CenterAccelSideOutput
 2:
    - customer
	- AccelCenterSideInput
	- AccelAudioPipeComponent
	- AccelCenterSideOutput
 3:
	- customer
	- CenterAccelSideInput
	- TestRealtimeSink

*/

const char* accel_str = R"EON_CODE(

sidechain tester: {
	
	loop center.audio.sync: {
		center.accel.order.side.out: true;
	};
	
	loop accel.audio.output: {
		accel.center.order.side.in: true;
		accel.filename: "$FILEPATH";
		accel.center.audio.side.out: true;
	};
	
	loop center.audio.output: {
		center.accel.audio.side.in: true;
		center.audio.sink.realtime: true;
	};
	
};

)EON_CODE";


/*
1: local center
	- customer
    - CenterSideOutput(Net)
2: local net
	- customer
	- NetSideInput(Center)
	- NetSingleLinkOutput
3: remote net
	- customer
	- NetSingleLinkInput
	- NetSideOutput(Center)
4: remote center
	- customer
	- CenterSideInput(Net)
    - AudioInputComponent
    - AudioOutputComponent
	- CenterSideOutput(Net)
5: local net
	- customer
	- NetSideInput(Center)
	- NetSingleLinkOutput
6: local net
	- customer
	- CenterSideInput(Net)
	- TestRealtimeSink
	
*/
const char* net_str = R"EON_CODE(

sidechain local_in: {
	loop local_in: {
		center.net.order.side.out: true;
	};
	loop link_out: {
		net.center.order.side.in: true;
		net.order.remote.src: true;
	};
	loop link_in: {
		net.audio.remote.src: true;
		net.center.audio.side.out: true;
	};
	loop local_out: {
		center.net.audio.side.in: true;
		center.audio.sink.realtime: true;
	};
};

net_sidechain remote: {
	loop remote_link_in: {
		net.order.remote.sink: true;
		net.audio.generator: true;
		net.audio.side.out: true;
	};
	loop remote_link_out: {
		net.audio.side.in: true;
		net.audio.remote.src: true;
	};
};


)EON_CODE";


bool TestParser() {
	if (!TestParseEonCode(center_str)) return false;
	if (!TestParseEonCode(perma_str)) return false;
	if (!TestParseEonCode(accel_str)) return false;
	if (!TestParseEonCode(net_str)) return false;
	return true;
}

void Main() {
	SetCoutLog();
	Ecs::Factory::Dump();
	
	if (!TestParser())
		return;
	
	TypeExtCls t;
	
	REG_EXT(TestCustomer,		CUSTOMER,	CENTER,RECEIPT,		CENTER,ORDER,	CENTER,ORDER);
	REG_EXT(TestRealtimeSrc,	INPUT,		CENTER,ORDER,		CENTER,AUDIO,	CENTER,AUDIO);
	REG_EXT(TestRealtimeSink,	OUTPUT,		CENTER,AUDIO,		CENTER,AUDIO,	CENTER,RECEIPT);
	
	
	//BreakRefAdd(0x802859038);
	
	
	if (!SimpleDebugInitializer())
		Exit(1);
	
	MAKE_STATIC(Machine, mach);
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
	
	verifier.Attach(mach);
	
	//SetDebugRefVisits();
	RuntimeDiagnostics::Static().SetRoot(mach);
	
    #ifdef flagSTDEXC
    try {
    #endif
		bool fail = false;
		{
			RegistrySystemRef reg		= mach.Add<RegistrySystem>();
			EntityStoreRef es			= mach.Add<EntityStore>();
			ComponentStoreRef compstore	= mach.Add<ComponentStore>();
		    //ConnectorStoreRef connstore	= mach.Add<ConnectorStore>();
		    ExtSystemRef cust			= mach.Add<ExtSystem>();
		    EonLoaderRef eon			= mach.Add<EonLoader>();
		    
		    mach.Add<PacketTracker>();
			
			PoolRef root = es->GetRoot();
			
			String eon_code;
			int test_i = 0;
			if      (test_i == 0)	eon_code = center_str;
			else if (test_i == 1)	eon_code = perma_str;
			else if (test_i == 2)	eon_code = accel_str;
			else if (test_i == 3)	eon_code = net_str;
			else
				Exit(1);
			
			LOG(GetLineNumStr(eon_code, 1));
	        eon->PostLoadString(eon_code);
	    }
	    
	    if (!fail && mach.Start()) {
		    int iter = 0;
		    TimeStop t, total;
		    while (mach.IsRunning()) {
		        double dt = ResetSeconds(t);
		        mach.Update(dt);
		        
		        if (!iter++)
		            mach.Get<EntityStore>()->GetRoot()->Dump();
		        
		        Sleep(1);
		        
		        if (total.Seconds() > 3)
		            mach.SetNotRunning();
		    }
		    
		    RuntimeDiagnostics::Static().CaptureSnapshot();
	    }
	#ifdef flagSTDEXC
    }
    catch (Exc e) {
        LOG("error: " << e);
        Exit(1);
    }
    #endif
    
    mach.Stop();
	mach.Clear();
    //RefDebugVisitor::Static().DumpUnvisited();
}














void TestRealtimeSrc::Initialize()  {
	internal_fmt.SetAudio(SoundSample::U8_LE, 2, 44100, 777);
	time = 0;
}

void TestRealtimeSrc::Uninitialize()  {
	
}

void TestRealtimeSrc::Forward(FwdScope& fwd) {
	RTLOG("TestRealtimeSrc::Forward");
}

void TestRealtimeSrc::StorePacket(Packet& p) {
	RTLOG("TestRealtimeSrc::StorePacket: time=" << time);
	ASSERT_(!p->GetFormat().IsValid(), "Packed shouldn't be initialized before this");
	PacketValue& pv = *p;
	pv.SetFormat(internal_fmt);
	
	Vector<byte>& data = pv.Data();
	data.SetCount(internal_fmt.GetFrameSize());
	for(byte& dst : data)
		dst = rolling_value++;
	
	time += internal_fmt.GetFrameSeconds();
}









void TestRealtimeSink::Initialize() {
	
	flag.Start(1);
	Thread::Start(THISBACK(IntervalSinkProcess));
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


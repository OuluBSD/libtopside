#include "NativeAtomDemo.h"

NAMESPACE_TOPSIDE_BEGIN
using namespace Parallel;
using namespace Serial;


const char* eon = R"3ON(
loop tester.generator:
	center.customer:
		dummy = "value"
	center.audio.src.test
	center.audio.sink.test.realtime:
		dbg_limit = 100
)3ON";


LinkBase* CreateLink(Atom& a) {
	/*Machine& mach = a.GetMachine();
	LinkTypeCls link_type = a.GetLinkType();
	LinkBase* lb = mach.CreateLinkTypeCls(link_type);
	
	return lb;
	*/
	TODO
}


bool RunAudioGenTest() {
	Machine mach;
	
	RegistrySystemRef reg = mach.Add<RegistrySystem>();
    reg->SetAppName("AudioGenTest");
	
    mach.Add<AtomSystem>();
	mach.Add<LinkSystem>();
	mach.Add<AtomStore>();
	mach.Add<LinkStore>();
	mach.Add<SpaceStore>();
	mach.Add<LoopStore>();
	ScriptLoaderRef script = mach.FindAdd<ScriptLoader>();
	mach.Add<PacketTracker>();
	
	if (1) {
		ScriptLoaderRef script = mach.Find<ScriptLoader>();
		if (!script) {
			LOG("No ScriptLoader added to machine and the machine is already started");
			return false;
		}
		script->PostLoadString(eon);
	}
	else {
		CenterCustomer customer;
		TestRealtimeSrc src;
		TestRealtimeSink sink;
		
		One<Link> customer_link = CreateLink(customer);
	}
	
    if (!mach.Start())
		return false;
	
	DebugMainLoop(mach);
	
	mach.Stop();
	mach.Clear();
	
	return true;
}

NAMESPACE_TOPSIDE_END

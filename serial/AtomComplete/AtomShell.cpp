#include "AtomComplete.h"


NAMESPACE_TOPSIDE_BEGIN


using ObjMap = VectorMap<String,Object>;
MAKE_STATIC(ObjMap, __def_args)
MAKE_STATIC(String, eon_script)
MAKE_STATIC(String, eon_file)


bool DefaultInitializer() {
	SetCoutLog();
	
	CommandLineArguments cmd;
	cmd.AddArg('e', "The path for the eon file", true, "path");
	if (!cmd.Parse()) {
		cmd.PrintHelp();
		return false;
	}
	
	const auto& inputs = cmd.GetInputs();
	for(const auto& in : inputs) {
		if (in.key == 'e') eon_file = in.value;
	}
	if (eon_file.IsEmpty()) {
		cmd.PrintHelp();
		LOG("");
		LOG("\te.g. -e play_audio_file.eon -MACHINE_TIME_LIMIT=3 -FILE=/home/user/some.mp3");
		return false;
	}
	
	__def_args <<= cmd.GetVariables();
	
	
	eon_file = Serial::RealizeEonFile(eon_file);
	
	
	if (GetFileExt(eon_file) == ".toy") {
		ShadertoyContextLoader toy_loader;
		Object o;
		if (!toy_loader.Load(eon_file, o)) {
			LOG("Toy file loading failed: " << eon_file);
			return false;
		}
		
		Serial::ToyLoader ser_loader;
		if (!ser_loader.Load(o)) {
			LOG("Toy object loading failed");
			return false;
		}
		
		eon_script = ser_loader.GetResult();
		//DUMP(eon_script);
	}
	
	return true;
}


size_t break_addr = 0;
bool verify = false;
MAKE_STATIC(Serial::MachineVerifier, verifier);


void DefaultSerialInitializer() {
	using namespace Serial;
	
	SetCoutLog();
	//Serial::Factory::Dump();
	
	
	if (1)
		verify = true;
	
	if (0)
		break_addr = 0x806A81E68;
	
	
	if (!DefaultInitializer())
		return;
	
	if (verify) {
		verifier.AddSystem<RegistrySystem>();
		verifier.AddSystem<LoopStore>();
		verifier.AddSystem<AtomStore>();
		verifier.AddSystem<AtomSystem>();
		verifier.AddSystem<ScriptLoader>();
		
		auto& ent		= verifier.GetRoot().AddLoop("tester").AddLoop("generator").AddEntity();
		auto& customer	= ent.AddAtomWith<CenterCustomer>	(VD(CENTER,ORDER));
		auto& src		= ent.AddAtomWith<TestRealtimeSrc>	(VD(CENTER,AUDIO));
		auto& sink		= ent.AddAtomWith<TestRealtimeSink>	(VD(CENTER,RECEIPT));
		customer << src << sink << customer;
		src.SetSourceFormat(GetDefaultFormat(VD(CENTER,AUDIO)));
		sink.SetSinkFormat(GetDefaultFormat(VD(CENTER,AUDIO)));
		
	}
}


void DefaultRunner(String app_name) {
	//DUMP(eon_script);
	//DUMP(eon_file);
	//DUMPC(args);
	if (!break_addr)
		Serial::DebugMain(eon_script, eon_file, __def_args, verify ? &verifier : 0);
	else
		Serial::DebugMain(eon_script, eon_file, __def_args, verify ? &verifier : 0, 1, break_addr);
}

void DefaultStartup() {
	LOG("<-- Startup -->");
}

NAMESPACE_TOPSIDE_END


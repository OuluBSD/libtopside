#include "AtomDebug.h"


NAMESPACE_TOPSIDE_BEGIN


using ObjMap = VectorMap<String,Object>;
MAKE_STATIC(ObjMap, __def_args)
MAKE_STATIC(String, eon_script)
MAKE_STATIC(String, eon_file)


bool DefaultInitializer(bool skip_eon_file) {
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
	
	__def_args <<= cmd.GetVariables();
	
	if (!skip_eon_file && eon_file.IsEmpty()) {
		cmd.PrintHelp();
		LOG("");
		LOG("\te.g. -e play_audio_file.eon -MACHINE_TIME_LIMIT=3 -FILE=/home/user/some.mp3");
		return false;
	}
	
	eon_file = Serial::RealizeEonFile(eon_file);
	
	
	if (GetFileExt(eon_file) == ".toy") {
		TODO // use some extension thingy here to allow later file extension hooks
		#if 0
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
		#endif
	}
	
	return true;
}


size_t break_addr = 0;
bool verify = false;
MAKE_STATIC(Serial::MachineVerifier, verifier);


void DefaultSerialInitializer() {DefaultSerialInitializer0(false);}

void DefaultSerialInitializer0(bool skip_eon_file) {
	using namespace Serial;
	
	SetCoutLog();
	//Serial::Factory::Dump();
	
	
	if (1)
		verify = true;
	
	if (0)
		break_addr = 0x806A81E68;
	
	
	if (!DefaultInitializer(skip_eon_file))
		return;
	
	if (verify) {
		TODO // some extension thing is required here to work with only AtomDebug
		#if 0
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
		#endif
	}
}

void DefaultSerialInitializerInternalEon() {
	DefaultSerialInitializer0(true);
}

void DefaultRunner(String app_name, String override_eon_file, VectorMap<String,Object>* extra_args, const char* extra_str) {
	//DUMP(eon_script);
	//DUMP(eon_file);
	//DUMPC(args);
	
	if (!override_eon_file.IsEmpty())
		eon_file = override_eon_file;
	
	if (extra_args) {
		for(int i = 0; i < extra_args->GetCount(); i++)
			__def_args.GetAdd(
				extra_args->GetKey(i),
				(*extra_args)[i]
			);
	}
	
	if (extra_str) {
		Vector<String> args = Split(extra_str, ";");
		for (String& arg : args) {
			int i = arg.Find("=");
			if (i >= 0) {
				String a = arg.Left(i);
				String b = arg.Mid(i+1);
				__def_args.Add(a, b);
			}
		}
	}
	
	if (!break_addr)
		Serial::DebugMain(eon_script, eon_file, __def_args, verify ? &verifier : 0);
	else
		Serial::DebugMain(eon_script, eon_file, __def_args, verify ? &verifier : 0, 1, break_addr);
}

void DefaultStartup() {
	LOG("<-- Startup -->");
}

NAMESPACE_TOPSIDE_END


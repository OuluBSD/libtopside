#include "SerialLib.h"


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
	
	eon_file = Parallel::RealizeEonFile(eon_file);
	
	
	if (GetFileExt(eon_file) == ".toy") {
		eon_script = SerialLoaderFactory::LoadFile(eon_file);
		//DUMP(eon_script);
		if (eon_script.IsEmpty())
			return false;
	}
	
	return true;
}


size_t break_addr = 0;
bool verify = false;
//MAKE_STATIC(Serial::MachineVerifier, verifier);


void DefaultSerialInitializer() {DefaultSerialInitializer0(false);}

void DefaultSerialInitializer0(bool skip_eon_file) {
	using namespace Serial;
	
	SetCoutLog();
	//Serial::Factory::Dump();
	
	
	if (0)
		verify = true;
	
	if (0)
		break_addr = 0x1;
	
	
	if (!DefaultInitializer(skip_eon_file))
		return;
	
	if (verify) {
		TODO // some extension thing is required here to work with only AtomMinimal
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

void DefaultRunner(bool main_loop, String app_name, String override_eon_file, VectorMap<String,Object>* extra_args, const char* extra_str) {
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
		//Serial::DebugMain(eon_script, eon_file, __def_args, verify ? &verifier : 0);
		DebugMain(main_loop, eon_script, eon_file, __def_args, 0);
	else
		//Serial::DebugMain(eon_script, eon_file, __def_args, verify ? &verifier : 0, 1, break_addr);
		DebugMain(main_loop, eon_script, eon_file, __def_args, 0, 1, break_addr);
}

void DefaultStartup() {
	LOG("<-- Startup -->");
}




int __dbg_time_limit;


void DebugMainLoop() {
	using namespace Parallel;
	
	Machine& mach = GetActiveMachine();
	int iter = 0;
    TimeStop t, total;
    double sleep_dt_limit = 1.0 / 300.0;
    while (mach.IsRunning()) {
        double dt = ResetSeconds(t);
        mach.Update(dt);
        
        //if (!iter++) mach.Get<LoopStore>()->GetRoot()->Dump();
		
		if (dt < sleep_dt_limit)
			Sleep(1);
        
        double total_seconds = total.Seconds();
        if (__dbg_time_limit > 0 && total_seconds >= __dbg_time_limit)
            mach.SetNotRunning();
    }
    
    RuntimeDiagnostics::Static().CaptureSnapshot();
}

void DebugMain(bool main_loop, String script_content, String script_file, VectorMap<String,Object>& args, Serial::MachineVerifier* ver, bool dbg_ref_visits, uint64 dbg_ref) {
	using namespace Parallel;
	
	SetCoutLog();
	//Serial::Factory::Dump();
	
	if (script_content.IsEmpty() && script_file.IsEmpty()) {
		LOG("No script file given");
		return;
	}
	
	if (dbg_ref)
		BreakRefAdd(dbg_ref);
	
	__dbg_time_limit = args.Get("MACHINE_TIME_LIMIT", 0).ToDouble();
	
	{
		Machine& mach = GetActiveMachine();
		
		if (ver)
			ver->Attach(mach);
		
		
		if (dbg_ref_visits)
			SetDebugRefVisits();
		RuntimeDiagnostics::Static().SetRoot(mach);
		
	    #ifdef flagSTDEXC
	    try {
	    #endif
			bool fail = false;
			{
				if (!mach.IsStarted()) {
					RegistrySystemRef reg	= mach.FindAdd<RegistrySystem>();
					LoopStoreRef ls			= mach.FindAdd<LoopStore>();
					AtomStoreRef as			= mach.FindAdd<AtomStore>();
				    AtomSystemRef asys		= mach.FindAdd<AtomSystem>();
				    ScriptLoaderRef script	= mach.FindAdd<ScriptLoader>();
				    
				    mach.FindAdd<PacketTracker>();
				}
				
				LoopStoreRef ls			= mach.Find<LoopStore>();
				if (!ls) {
					LOG("No LoopStore added to machine and the machine is already started");
					return;
				}
				
				ScriptLoaderRef script	= mach.Find<ScriptLoader>();
				if (!script) {
					LOG("No ScriptLoader added to machine and the machine is already started");
					return;
				}
				
				LoopRef root = ls->GetRoot();
				
				String path = RealizeEonFile(script_file);
				
				String script_str;
				if (script_content.IsEmpty()) {
					script_str = LoadFile(path);
					if (script_str.IsEmpty()) {
						LOG("Empty file in " << path);
						return;
					}
				}
				else
					script_str = script_content;
				//script_str.DebugFollow();
				
				if (script_str.IsEmpty()) {
					LOG("No script");
					return;
				}
				for(int i = 0; i < args.GetCount(); i++) {
					String key = "${" + args.GetKey(i) + "}";
					String value = args[i].ToString();
					value = EscapeString(value);
					script_str.Replace(key, value);
				}
				LOG(script_str);
				
		        script->PostLoadString(script_str);
		    }
		        
		    if (!fail) {
		        if (!mach.IsStarted())
					fail = !mach.Start();
		    }
		    
		    if (!fail && main_loop) {
		        DebugMainLoop();
		    }
		#ifdef flagSTDEXC
	    }
	    catch (Exc e) {
	        LOG("error: " << e);
	        Exit(1);
	    }
	    #endif
	    
	    if (main_loop) {
		    mach.Stop();
		    mach.Clear();
	    }
	}
    
    //RefDebugVisitor::Static().DumpUnvisited();
}

void DefaultRunnerStop() {
	using namespace Parallel;
	Machine& mach = GetActiveMachine();
	mach.SetNotRunning();
	mach.Stop();
	mach.Clear();
}



NAMESPACE_TOPSIDE_END


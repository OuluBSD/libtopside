// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.5 17:55:33

#ifndef _IScript_TmplClasses_h_
#define _IScript_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Scr> struct ScriptRunnerT;
template <class Scr> struct ScriptThreadT;


template <class Scr>
struct ScriptRunnerT : ScrRunner {
	using CLASSNAME = ScriptRunnerT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrRunner)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ScrRunner>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

template <class Scr>
struct ScriptThreadT : ScrThread {
	using CLASSNAME = ScriptThreadT<Scr>;
	RTTI_DECL1(CLASSNAME, ScrThread)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ScrThread>(this);}
	
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		return true;
	}

	
};

#if 0
using EscRunner = ScriptRunnerT<ScrEsc>;
using EscThread = ScriptThreadT<ScrEsc>;
#endif

#if 0
using PythonRunner = ScriptRunnerT<ScrPython>;
using PythonThread = ScriptThreadT<ScrPython>;
#endif

#if 0
using DuktapeRunner = ScriptRunnerT<ScrDuktape>;
using DuktapeThread = ScriptThreadT<ScrDuktape>;
#endif


NAMESPACE_PARALLEL_END



#endif


// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IScript_TmplClasses_h_
#define _IScript_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Scr> struct ScriptRunnerT;
template <class Scr> struct ScriptThreadT;


template <class Scr>
struct ScriptRunnerT : ScrRunner {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Scr>
struct ScriptThreadT : ScrThread {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

using EscRunner = ScriptRunnerT<ScrEsc>;
using EscThread = ScriptThreadT<ScrEsc>;
using PythonRunner = ScriptRunnerT<ScrPython>;
using PythonThread = ScriptThreadT<ScrPython>;
using DuktapeRunner = ScriptRunnerT<ScrDuktape>;
using DuktapeThread = ScriptThreadT<ScrDuktape>;


NAMESPACE_PARALLEL_END



#endif


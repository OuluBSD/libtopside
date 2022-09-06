#ifndef _AtomDebug_Verifier_h_
#define _AtomDebug_Verifier_h_

NAMESPACE_SERIAL_BEGIN

struct VerifierAtom {
	VerifierAtom* src = 0;
	SerialTypeCls type;
	Format sink_fmt;
	Format src_fmt;
	
	
	void SetSourceFormat(Format fmt);
	void SetSinkFormat(Format fmt);
	void LinkTo(VerifierAtom& comp);
	
	
	VerifierAtom& operator<<(VerifierAtom& c) {
		LinkTo(c);
		return c;
	}
	
};

struct VerifierEntity {
	Array<VerifierAtom> ext;
	
	
	VerifierAtom& AddAtomWith(SerialTypeCls t);
	template <class T> VerifierAtom& AddAtomWith(ValDevCls vd) {return AddAtomWith(AsSerialTypeCls<T>(vd));}
	
};

struct VerifierLoop {
	ArrayMap<String, VerifierLoop> pools;
	Array<VerifierEntity> ents;
	
	
	VerifierEntity& AddEntity() {return ents.Add();}
	VerifierLoop& AddLoop(String key) {ASSERT(pools.Find(key) < 0); return pools.Add(key);}
	VerifierLoop& GetAddLoop(String key) {return pools.GetAdd(key);}
	
};

struct VerifierSystem {
	TypeCls			type;
	SerialTypeCls	ecs_type;
	
};

class MachineVerifier {
	Machine* mach = 0;
	AtomSystem* ext_sys = 0;
	VerifierLoop root;
	Array<VerifierSystem> sys;
	
	
protected:
	typedef enum {
		ROOT,
		UPDATE,
		SYSTEM_UPDATE,
		ONCE_FORWARD,
		EXTCOMP_FORWARD,
		FWDSCOPE_FORWARD,
		PROCESS_PACKETS,
		CREATE_EMPTY_PACKET,
		VALEXPT_FWD,
		SCRIPT_LOAD,
		TERMINAL_TEST,
		LOOPLOADER_FORWARD_BEGINNING,
		LOOPLOADER_FORWARD_RETRY,
		LOOPLOADER_SEARCH_NEW_SEGMENT,
		LOOPLOADER_FORWARD_SIDES,
	} Type;
	
	struct ExpectedAction : Moveable<ExpectedAction> {
		Type type;
	};
	
	struct Scope : Moveable<Scope> {
		Vector<ExpectedAction> enter;
		Type type;
		bool may_leave = false;
		
		ExpectedAction& AddEnter(Type t) {auto& a = enter.Add(); a.type = t;  return a;}
		void MayLeave(bool b) {may_leave = b;}
		bool CanEnter(Type t) const;
	};
	
	struct PacketData {
		int count;
		int bytes;
		int ch_samples;
		
		void Clear() {count = 0; bytes = 0; ch_samples = 0;}
		void Add(Packet& p);
	};
	
	Vector<Scope> stack;
	PacketData cur_pk;
	AtomBase* c;
	DefaultExchangePoint* vep;
	
	void SetDefaultExpected();
	void Enter(Type t);
	void Leave(Type t);
	void MayLeaveTop();
	
protected:
	
	struct LoopAtomSideData {
		ValDevCls			vd;
		bool				has_link = false;
		bool				is_required = false;
	};
	
	struct LoopAtomData {
		AtomTypeCls			type;
		Array<LoopAtomSideData>	src_sides, sink_sides;
		
	};
	
	struct LoopLoaderData {
		ScriptLoopLoader*	ll;
		ScriptStatus		status0 = UNASSIGNED;
		ScriptStatus		status1 = UNASSIGNED;
		Array<LoopAtomData>	atoms;
		
		bool MayCreateAtoms() const;
	};
	ArrayMap<size_t, LoopLoaderData>		loop_loaders;
	
public:
	typedef MachineVerifier CLASSNAME;
	MachineVerifier();
	
	
	void Attach(Machine& mach);
	void Attach(ScriptLoader& sl);
	void Clear();
	
	void OnEnterUpdate();
	void OnEnterSystemUpdate(SystemBase& base);
	void OnEnterOnceForward(PacketForwarder*);
	void OnEnterAtomForward(AtomBase* c);
	void OnEnterFwdScopeForward(FwdScope& c);
	void OnEnterProcessPackets(AtomBase&, PacketIO& p);
	void OnEnterCreatedEmptyPacket(Packet& p);
	void OnEnterValExPtForward(DefaultExchangePoint& p);
	void OnEnterScriptLoad(SystemBase& base);
	void OnEnterTerminalTest(size_t call_id);
	void OnEnterSearchNewSegment(size_t call_id);
	void OnEnterScriptLoopLoaderForwardBeginning(size_t call_id);
	void OnEnterScriptLoopLoaderForwardRetry(size_t call_id);
	void OnEnterScriptLoopLoaderForwardSides(size_t call_id);
	
	void OnLeaveUpdate();
	void OnLeaveSystemUpdate();
	void OnLeaveOnceForward();
	void OnLeaveAtomForward();
	void OnLeaveFwdScopeForward();
	void OnLeaveProcessPackets(AtomBase&, PacketIO& p);
	void OnLeaveCreatedEmptyPacket();
	void OnLeaveValExPtForward();
	void OnLeaveScriptLoad();
	void OnLeaveTerminalTest(size_t call_id);
	void OnLeaveSearchNewSegment(size_t call_id);
	void OnLeaveScriptLoopLoaderForwardBeginning(size_t call_id);
	void OnLeaveScriptLoopLoaderForwardRetry(size_t call_id);
	void OnLeaveScriptLoopLoaderForwardSides(size_t call_id);
	
	void OnLoopLoader_Status(ScriptLoopLoader* ll);
	void OnLoopLoader_RealizeAtoms(ScriptLoopLoader* ll);
	void OnLoopLoader_AtomLinked(ScriptLoopLoader* ll);
	void OnLoopLoader_SearchNewSegment(ScriptLoopLoader* ll);
	
	void UpdateLoopData(ScriptLoopLoader* ll);
	
	VerifierLoop& GetRoot() {return root;}
	
	VerifierSystem& AddSystem(TypeCls t, SerialTypeCls et);
	template<class T> VerifierSystem& AddSystem() {return AddSystem(AsTypeCls<T>(), AsSerialTypeCls<T>(VD(CENTER,ORDER)));}
	
};

NAMESPACE_SERIAL_END

#endif

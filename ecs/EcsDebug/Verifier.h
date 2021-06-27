#ifndef _EcsDebug_Verifier_h_
#define _EcsDebug_Verifier_h_

NAMESPACE_ECS_BEGIN

struct VerifierExtComponent {
	VerifierExtComponent* src = 0;
	EcsTypeCls type;
	Format sink_fmt;
	Format src_fmt;
	
	
	void SetSourceFormat(Format fmt);
	void SetSinkFormat(Format fmt);
	void LinkTo(VerifierExtComponent& comp);
	
	
	VerifierExtComponent& operator<<(VerifierExtComponent& c) {
		LinkTo(c);
		return c;
	}
	
};

struct VerifierEntity {
	Array<VerifierExtComponent> ext;
	
	
	VerifierExtComponent& AddExtComponentWith(EcsTypeCls t);
	template <class T> VerifierExtComponent& AddExtComponentWith(ValDevCls vd) {return AddExtComponentWith(AsEcsTypeCls<T>(vd));}
	
};

struct VerifierPool {
	ArrayMap<String, VerifierPool> pools;
	Array<VerifierEntity> ents;
	
	
	VerifierEntity& AddEntity() {return ents.Add();}
	VerifierPool& AddPool(String key) {ASSERT(pools.Find(key) < 0); return pools.Add(key);}
	VerifierPool& GetAddPool(String key) {return pools.GetAdd(key);}
	
};

struct VerifierSystem {
	TypeCls			type;
	EcsTypeCls		ecs_type;
	
};

class MachineVerifier {
	Machine* mach = 0;
	ExtSystem* ext_sys = 0;
	VerifierPool root;
	Array<VerifierSystem> sys;
	
	
protected:
	typedef enum {
		ROOT,
		UPDATE,
		SYSTEM_UPDATE,
		ONCE_FORWARD,
		EXTCOMP_FORWARD,
		FWDSCOPE_FORWARD,
		STORE_PACKET,
		CREATE_EMPTY_PACKET,
		VALEXPT_FWD,
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
	ExtComponent* c;
	ValExchangePoint* vep;
	
	void SetDefaultExpected();
	void Enter(Type t);
	void Leave(Type t);
	void MayLeaveTop();
	
public:
	typedef MachineVerifier CLASSNAME;
	MachineVerifier();
	
	
	void Attach(Machine& mach);
	void Clear();
	
	void OnEnterUpdate();
	void OnEnterSystemUpdate(SystemBase& base);
	void OnEnterOnceForward(PacketForwarder*);
	void OnEnterExtComponentForward(ExtComponent* c);
	void OnEnterFwdScopeForward(FwdScope& c);
	void OnEnterStorePacket(ComponentExtBase&, Packet& p);
	void OnEnterCreatedEmptyPacket(Packet& p);
	void OnEnterValExPtForward(ValExchangePoint& p);
	
	void OnLeaveUpdate();
	void OnLeaveSystemUpdate();
	void OnLeaveOnceForward();
	void OnLeaveExtComponentForward();
	void OnLeaveFwdScopeForward();
	void OnLeaveStorePacket(Packet& p);
	void OnLeaveCreatedEmptyPacket();
	void OnLeaveValExPtForward();
	
	VerifierPool& GetRoot() {return root;}
	
	VerifierSystem& AddSystem(TypeCls t, EcsTypeCls et);
	template<class T> VerifierSystem& AddSystem() {return AddSystem(AsTypeCls<T>(), AsEcsTypeCls<T>(VD(CENTER,ORDER)));}
	
};


NAMESPACE_ECS_END

#endif

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
	
public:
	typedef MachineVerifier CLASSNAME;
	MachineVerifier();
	
	
	void Attach(Machine& mach);
	void Clear();
	
	void OnUpdate();
	void OnSystemUpdate(SystemBase& base);
	void OnOnceForward(PacketForwarder*);
	void OnExtComponentForward(ExtComponent* c);
	void OnFwdScopeForward(FwdScope& c);
	void OnStorePacket(ComponentExtBase&, Packet& p);
	void OnCreatedEmptyPacket(Packet& p);
	
	VerifierPool& GetRoot() {return root;}
	
	VerifierSystem& AddSystem(TypeCls t, EcsTypeCls et);
	template<class T> VerifierSystem& AddSystem() {return AddSystem(AsTypeCls<T>(), AsEcsTypeCls<T>(VD(CENTER,ORDER)));}
	
};


NAMESPACE_ECS_END

#endif

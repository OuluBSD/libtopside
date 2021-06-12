#ifndef _EcsLib_Eon_h_
#define _EcsLib_Eon_h_

NAMESPACE_TOPSIDE_BEGIN










struct EonPlan : Moveable<EonPlan> {
	Vector<Eon::ActionNode*> plan;
	
	EonPlan() {}
	EonPlan(const EonPlan& ep) {*this = ep;}
	void operator=(const EonPlan& ep) {
		plan <<= ep.plan;
	}
};

class EonState {
	
	
};


class EonScope {
	EonState const_state;
	EonState final_state;
	
public:
	EonScope() {}
	
	void SetConstantState(const EonState& s) {const_state = s;}
	
	EonState& GetFinalState() {return final_state;}
	
	
};






class EonLoader :
	public System<EonLoader>
{
	LinkedList<EonScope> scopes;
	
	LinkedList<PathwayRouterRef> pathways;
	Vector<String> post_load_file;
	Eon::CompilationUnit root;
	EntityStoreRef es;
	
	
	void Visit(RuntimeVisitor& vis) override {
		(vis && pathways) & es;
	}
	
public:
	SYS_RTTI(EonLoader)
	SYS_CTOR(EonLoader);
	
	void PostLoadFile(String path) {post_load_file << path;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
	bool LoadFile(String path);
	bool Load(String content, String filepath="temp");
	bool LoadCompilationUnit(Eon::CompilationUnit& cunit);
	bool LoadCustomerDefinition(Eon::CustomerDefinition& def);
	EntityRef ResolveEntity(Eon::Id& id);
	
	void AddError(String msg);
	
	
};

using EonLoaderRef = Ref<EonLoader, RefParent1<Machine>>;



NAMESPACE_TOPSIDE_END

#endif

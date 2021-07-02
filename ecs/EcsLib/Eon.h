#ifndef _EcsLib_Eon_h_
#define _EcsLib_Eon_h_

NAMESPACE_ECS_BEGIN


class EonLoader;










class EonScope {
protected:
	friend class EonLoader;
	friend class EonLoopLoader;
	
	Eon::WorldState current_state;
	Eon::SidechainDefinition* def = 0;
	
public:
	EonScope() {}
	
	void SetCurrentState(const Eon::WorldState& s) {current_state = s;}
	
	
};



class EonLoopLoader {
public:
	typedef enum {
		NOT_READY,
		WAITING_SIDE_INPUT,
		WAITING_SIDE_OUTPUT,
		READY,
		FAILED,
	} Status;
	
protected:
	friend class EonLoader;
	
	EonLoader& loader;
	Eon::LoopDefinition& def;
	
	Eon::ActionPlanner planner;
	AStar<Eon::ActionNode> as;
	Eon::Plan ep;
	Status status = NOT_READY;
	EonLoopLoader* side_conn = 0;
	
public:
	EonLoopLoader(EonLoader* loader, Eon::LoopDefinition& def) : loader(*loader), def(def) {}
	
	
	bool Parse();
	bool Forward();
	bool Load();
	bool IsFailed() const {return status == FAILED;}
	bool IsReady() const {return status == READY;}
	bool IsWaitingSideInput() const {return status == WAITING_SIDE_INPUT;}
	bool IsWaitingSideOutput() const {return status == WAITING_SIDE_OUTPUT;}
	bool AcceptOutput(EonLoopLoader& out);
	void SetSideConnection(EonLoopLoader* c) {side_conn = c;}
	
	void AddError(String msg);
	
	
};



bool TestParseEonCode(String code);

class EonLoader :
	public System<EonLoader>
{
protected:
	friend class EonLoopLoader;
	
	LinkedList<EonScope> scopes;
	Array<EonLoopLoader> loops;
	
	Vector<String> post_load_file;
	Vector<String> post_load_string;
	Eon::CompilationUnit root;
	EntityStoreRef es;
	
	
	void AddError(String msg);
	
public:
	SYS_RTTI(EonLoader)
	SYS_CTOR(EonLoader);
	SYS_DEF_VISIT_(vis & es)
	
	void PostLoadFile(String path) {post_load_file << path;}
	void PostLoadString(String s) {post_load_string << s;}
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::SYS_EON;}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    bool DoPostLoad();
	bool LoadFile(String path);
	bool Load(String content, String filepath="temp");
	bool LoadCompilationUnit(Eon::CompilationUnit& cunit);
	bool LoadSidechainDefinition(Eon::SidechainDefinition& def);
	EntityRef ResolveEntity(Eon::Id& id);
	bool SolveLoops(Eon::SidechainDefinition& def);
	
	
	
	
	
};

using EonLoaderRef = Ref<EonLoader, RefParent1<Machine>>;



NAMESPACE_ECS_END

#endif

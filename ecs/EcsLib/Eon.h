#ifndef _EcsLib_Eon_h_
#define _EcsLib_Eon_h_

NAMESPACE_ECS_BEGIN













class EonScope {
protected:
	friend class EonLoader;
	
	Eon::WorldState current_state;
	Eon::SidechainDefinition* def = 0;
	
public:
	EonScope() {}
	
	void SetCurrentState(const Eon::WorldState& s) {current_state = s;}
	
	
};




bool TestParseEonCode(String code);

class EonLoader :
	public System<EonLoader>
{
	LinkedList<EonScope> scopes;
	
	Vector<String> post_load_file;
	Vector<String> post_load_string;
	Eon::CompilationUnit root;
	EntityStoreRef es;
	
	
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
	bool LoadLoopDefinition(Eon::LoopDefinition& def);
	EntityRef ResolveEntity(Eon::Id& id);
	
	void AddError(String msg);
	
	
	
	
};

using EonLoaderRef = Ref<EonLoader, RefParent1<Machine>>;



NAMESPACE_ECS_END

#endif

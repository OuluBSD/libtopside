#ifndef _ParallelCore_SpaceStore_h_
#define _ParallelCore_SpaceStore_h_

NAMESPACE_PARALLEL_BEGIN


class SpaceStore : public System<SpaceStore> {
	SpaceVec		root;
	
	Mutex			lock;
	
	enum {
		READ,
		WRITE
	};
	
	void InitRoot();
public:
	SYS_RTTI(SpaceStore)
	SYS_CTOR_(SpaceStore) {InitRoot();}
	SYS_DEF_VISIT_(vis || root)
	
	SpaceRef GetRoot() {
		if (root.IsEmpty())
			return SpaceRef();
		Space& l = root.GetFirst();
		return l;
	}
	SpaceVec& GetRootVec()	{return root;}
	
	
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::LOOP_STORE;}
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Stop() override;
	void Uninitialize() override;
	
	
};

using SpaceStoreRef = Ref<SpaceStore>;


NAMESPACE_PARALLEL_END

#endif

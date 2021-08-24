#ifndef _SerialCore_LoopStore_h_
#define _SerialCore_LoopStore_h_

NAMESPACE_SERIAL_BEGIN


class LoopStore : public System<LoopStore> {
	LoopVec							root;
	
	Mutex							lock;
	
	enum {
		READ,
		WRITE
	};
	
	void InitRoot();
public:
	SYS_RTTI(LoopStore)
	SYS_CTOR_(LoopStore) {InitRoot();}
	SYS_DEF_VISIT_(vis || root)
	
	LoopRef GetRoot() {
		if (root.IsEmpty())
			return LoopRef();
		Loop& l = root.GetFirst();
		return l.AsRefT();
	}
	LoopVec& GetRootVec()	{return root;}
	
	
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Uninitialize() override;
	
	
};


NAMESPACE_SERIAL_END

#endif

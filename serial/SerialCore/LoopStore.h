#ifndef _SerialCore_LoopStore_h_
#define _SerialCore_LoopStore_h_

NAMESPACE_SERIAL_BEGIN


class Loop : public System<Loop> {
	LoopVec							root;
	
	Mutex							lock;
	
	enum {
		READ,
		WRITE
	};
	
	void InitRoot();
public:
	SYS_RTTI(Loop)
	SYS_CTOR_(Loop) {InitRoot();}
	SYS_DEF_VISIT_(vis || root)
	
	LoopRef GetRoot()		{return *root.begin();}
	LoopVec& GetRootVec()	{return root;}
	
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Uninitialize() override;
	
	
};


NAMESPACE_SERIAL_END

#endif

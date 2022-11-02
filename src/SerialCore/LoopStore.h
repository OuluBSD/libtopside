#ifndef _SerialCore_LoopStore_h_
#define _SerialCore_LoopStore_h_

NAMESPACE_SERIAL_BEGIN


class LoopStore : public System<LoopStore> {
	LoopVec				root;
	
	Mutex				lock;
	
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
		return l;
	}
	LoopVec& GetRootVec()	{return root;}
	
	
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::LOOP_STORE;}
	
protected:
	void Update(double) override;
	bool Initialize() override;
	void Uninitialize() override;
	
	
};

using LoopStoreRef = Ref<LoopStore>;


NAMESPACE_SERIAL_END

#endif

#ifndef _IPhysics_TSpace_h_
#define _IPhysics_TSpace_h_

NAMESPACE_PARALLEL_BEGIN


template <class Fys>
struct SpaceT : NodeT<Fys> {
	using Base = SpaceT<Fys>;
	using Node = NodeT<Fys>;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	
protected:
	NativeSpace space;
	bool is_root = false;
	
public:
	RTTI_DECL1(SpaceT, Node)
	
	SpaceT() {space = Null;}
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Node)}
	
	void OnAttach() override {
		Fys::CreateSpace(this->GetNativeWorld(), space, this->owner ? &this->owner->GetNativeWorldSpace(false) : 0, is_root);
	}
	
	void SetRoot(bool b=true) {is_root = b;}
	const NativeSpace& GetNative(bool dbg_chk=true) const {ASSERT(!dbg_chk || space); return space;}
	NativeSpace& GetNative(bool dbg_chk=true) {ASSERT(!dbg_chk || space); return space;}
	
	String ToString() const override {return Fys::Id() + "Space";}
	
};


NAMESPACE_PARALLEL_END

#endif

#ifndef _Physics_TSpace_h_
#define _Physics_TSpace_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Fys>
struct SpaceT : NodeT<Fys> {
	using Base = SpaceT<Fys>;
	using Node = NodeT<Fys>;
	using NativeWorld = typename Fys::NativeWorld;
	using NativeSpace = typename Fys::NativeSpace;
	
protected:
	NativeSpace space = NULL;
	bool is_root = false;
	
public:
	RTTI_DECL1(SpaceT, Node)
	
	
	void OnAttach() override {
		Fys::CreateSpace(space, this->owner ? &this->owner->GetWorldSpace() : 0, is_root);
	}
	
	void SetRoot(bool b=true) {is_root=b;}
	const NativeSpace& GetSpace() const {ASSERT(space); return space;}
	
	String ToString() const override {return Fys::Id() + "Space";}
	
};


NAMESPACE_TOPSIDE_END

#endif

#ifndef _IPhysics_FysClasses_h_
#define _IPhysics_FysClasses_h_

NAMESPACE_PARALLEL_BEGIN


struct FysNode : RTTIBase {
	RTTI_DECL0(FysNode)
	
	virtual ~FysNode() {}
	
	virtual String ToString() const = 0;
	virtual bool LoadModel(GfxDataState& s) {return false;}
	virtual void Refresh() {}
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void Visit(RuntimeVisitor& vis) {}
	
};

/*struct FysObject : FysNode {
	RTTI_DECL1(FysObject, FysNode)
	
	
};

struct FysJoint : FysNode {
	RTTI_DECL1(FysJoint, FysNode)
	
};

struct FysSpace : FysNode {
	RTTI_DECL1(FysSpace, FysNode)
	
};*/



NAMESPACE_PARALLEL_END

#endif

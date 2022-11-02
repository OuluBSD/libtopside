#ifndef _Physics_FysClasses_h_
#define _Physics_FysClasses_h_

NAMESPACE_TOPSIDE_BEGIN

using namespace Parallel;


struct FysNode : RTTIBase {
	RTTI_DECL0(FysNode)
	
	virtual ~FysNode() {}
	
	virtual String ToString() const = 0;
	
};

struct FysObject : FysNode {
	RTTI_DECL1(FysObject, FysNode)
	
	virtual void LoadModel(GfxDataState& s) = 0;
	virtual void Refresh() = 0;
	
};

struct FysJoint : FysNode {
	RTTI_DECL1(FysJoint, FysNode)
	
};

struct FysSpace : FysNode {
	RTTI_DECL1(FysSpace, FysNode)
	
};



NAMESPACE_TOPSIDE_END

#endif

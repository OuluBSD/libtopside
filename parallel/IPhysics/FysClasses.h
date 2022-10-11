#ifndef _IPhysics_FysClasses_h_
#define _IPhysics_FysClasses_h_

NAMESPACE_PARALLEL_BEGIN


struct FysNode : RTTIBase {
	RTTI_DECL0(FysNode)
	
	virtual ~FysNode() {}
	
	virtual String ToString() const = 0;
	virtual bool LoadModel(GfxModelState& s) {return false;}
	virtual void Refresh() {}
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void Visit(RuntimeVisitor& vis) {}
	
};



NAMESPACE_PARALLEL_END

#endif

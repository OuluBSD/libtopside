// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IOptimizer_BaseClasses_h_
#define _IOptimizer_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct OptSolver : public Atom {
	RTTI_DECL1(OptSolver, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~OptSolver() {}

};

NAMESPACE_PARALLEL_END



#endif


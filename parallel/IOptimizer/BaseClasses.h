// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.8 19:22:44

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


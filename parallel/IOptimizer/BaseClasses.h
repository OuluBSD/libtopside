// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

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


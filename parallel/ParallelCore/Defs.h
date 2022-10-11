#ifndef _ParallelCore_Defs_h_
#define _ParallelCore_Defs_h_


#define VIS_THIS(t) vis.VisitThis<t>(this);

#define ATOM_DEF_VISIT void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this);}
#define ATOM_DEF_VISIT_(x) void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this); x;}
#define ATOM_DEF_MAKE_ACTION static bool MakeAction(Script::Action& act) {return false;}


#endif

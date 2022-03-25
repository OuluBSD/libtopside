#ifndef _ParallelCore_Defs_h_
#define _ParallelCore_Defs_h_


#define VIS_THIS(t) vis.VisitThis<t>(this);

#define ATOM_DEF_VISIT void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this);}
#define ATOM_DEF_VISIT_(x) void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AltBaseT>(this); x;}
#define ATOM_DEF_MAKE_ACTION static bool MakeAction(Script::Action& act) {return false;}

#define ATOM_MAKE_ACTION_BEGIN \
	static bool MakeAction(const AtomTypeCls& cls, Script::Action& act) {\
		bool fail = false, any_changes = false;\
		const ValDevCls& vd = cls.iface.content;
#define ATOM_MAKE_ACTION_END return !fail && any_changes;}
#define ATOM_MAKE_ACTION_UNDEF_TO_TRUE(x) if (act.Pre().IsUndefined(x)) {act.Post().SetTrue(x); any_changes = true;} else fail = true;
#define ATOM_MAKE_ACTION_TO_TRUE(x) act.Post().SetTrue(x); any_changes = true;
#define ATOM_MAKE_ACTION_TRUE_TO_FALSE(x) if (act.Pre().IsTrue(x)) {act.Post().SetFalse(x); any_changes = true;} else fail = true;
//#define ATOM_MAKE_ACTION_REQ_TRUE_TO_TRUE(x, y) if (act.Pre().IsTrue(x)) {act.Post().SetTrue(y); any_changes = true;} else fail = true;


#endif

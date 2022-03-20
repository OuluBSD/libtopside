#include "HighLib.h"

NAMESPACE_TOPSIDE_BEGIN

#define ContextAnimProxy(x) \
	void HiAnimContext::x(HiEscape& e) \
	{ \
		HiAnimProgram* prog = FindProgram(e); \
		ASSERT(prog); \
		if (!prog) Panic("script called from different context"); \
		prog->x(e); \
	}

ContextAnimProxy(HI_DrawText)


void HiAnimProgram::HI_DrawText(HiEscape& e) {
	int x = e[0];
	int y = e[1];
	String str = e[2];
	int ms = e[3];
	
	//TODO
	LOG(x << "," << y << ": " << str);
	
	Animation& a = ctx->a;
	AnimPlayer& p = ctx->p;
	
	AnimScene& s = a.GetActiveScene();
	AnimObject& parent = s.GetRoot();
	AnimObject& o = parent.Add();
	o.SetPosition(Point(x,y));
	o.SetText(str, 20, Color(47, 98, 158));
	p.Recompile(parent);
	
	p.AddTimedRemoveObject(1000, o, THISBACK(ContinueVm));
	
	//e.esc.hi.SleepReleasing(ms);
	vm->SleepInfiniteReleasing();
}



NAMESPACE_TOPSIDE_END

#include "HighLib.h"

NAMESPACE_TOPSIDE_BEGIN


HiAnimContext::HiAnimContext() {
	
	
	
}

void HiAnimContext::Clear() {
	code.Clear();
	global.Clear();
	progs.Clear();
	p.Clear();
	a.Clear();
	op_limit = 1000000;
	
	
	
	p.SetAnimation(a);
}

void HiAnimContext::Init() {
	
	if (!code.IsEmpty()) {
	    HighCall(global, "DrawText(x,y,str,sleep)", THISBACK(HI_DrawText));
	    StdLib(global);
	    
		try {
			for(int i = 0; i < code.GetCount(); i++)
				Scan(global, code[i], code.GetKey(i));
		}
	    catch(Exc e) {
	        LOG("ERROR: " << e << "\n");
	        return;
	    }
		
		CreateProgram("main");
	}
	
	p.Compile();
	p.Play();
}

void HiAnimContext::CreateProgram(String name) {
	
	int i = global.Find("main");
	if (i >= 0) {
		HiValue lambda = global[i];
		if (lambda.IsLambda()) {
			HiAnimProgram& prog = progs.Add();
			prog.ctx = this;
			prog.Init(lambda);
		}
	}
	
}

HiAnimProgram* HiAnimContext::FindProgram(HiEscape& e) {
	for (HiAnimProgram& prog : progs)
		if (prog.IsVm() && &prog.GetVm() == &e.esc.hi)
			return &prog;
	return 0;
}

void HiAnimContext::Iterate() {
	if (IsRunning()) {
		for (HiAnimProgram& prog : progs)
			prog.Iterate();
		
		p.Data();
		
		if (!IsRunning())
			WhenStop();
	}
}

bool HiAnimContext::IsRunning() const {
	if (p.IsRunning())
		return true;
	
	for (const HiAnimProgram& prog : progs)
		if (prog.IsRunning())
			return true;
	
	return false;
}


NAMESPACE_TOPSIDE_END

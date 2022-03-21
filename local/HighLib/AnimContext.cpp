#include "HighLib.h"

NAMESPACE_TOPSIDE_BEGIN


HiAnimContext::HiAnimContext() {
	Clear();
}

void HiAnimContext::Clear() {
	code.Clear();
	global.Clear();
	progs.Clear();
	p.Clear();
	a.Clear();
	op_limit = 1000000;
	keep_running = false;
	
	
	p.SetAnimation(a);
}

bool HiAnimContext::Init(bool run_main) {
	
	if (!code.IsEmpty()) {
	    HighCall(global, "DrawText(x,y,str,sleep)", THISBACK(HI_DrawText));
	    StdLib(global);
	    
		try {
			for(int i = 0; i < code.GetCount(); i++)
				Scan(global, code[i], code.GetKey(i));
		}
	    catch(Exc e) {
	        LOG("ERROR: " << e << "\n");
	        return false;
	    }
		
		if (run_main)
			CreateProgram("main");
	}
	
	p.Compile();
	p.Play();
	
	return true;
}

void HiAnimContext::CreateProgram(String name) {
	
	int i = global.Find(name);
	if (i >= 0) {
		HiValue lambda = global[i];
		if (lambda.IsLambda()) {
			HiAnimProgram& prog = progs.Add();
			prog.ctx = this;
			prog.fn_name = name;
			prog.Init(lambda);
		}
	}
	
}

bool HiAnimContext::AddCodePath(String path) {
	String content = LoadFile(path);
	if (content.IsEmpty()) {
		LOG("error: empty script");
		return false;
	}
	
	code.GetAdd(path) = content;
	
	return true;
}

HiAnimProgram* HiAnimContext::FindProgram(HiEscape& e) {
	for (HiAnimProgram& prog : progs)
		if (prog.IsVm() && &prog.GetVm() == &e.esc.hi)
			return &prog;
	return 0;
}

void HiAnimContext::InitializeEmptyScene() {
	ASSERT(a.scenes.IsEmpty());
	AnimScene& s = a.AddScene("empty");
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
	if (keep_running)
		return true;
	
	if (p.IsRunning())
		return true;
	
	for (const HiAnimProgram& prog : progs)
		if (prog.IsRunning())
			return true;
	
	return false;
}

void HiAnimContext::ProcessAndRemoveGroup(int group) {
	int i = 0;
	Vector<int> rm_list;
	for (HiAnimProgram& p : progs) {
		if (p.user_group == group) {
			p.Process();
			
			if (!p.IsRunning())
				rm_list << i;
		}
		i++;
	}
	
	if (rm_list.GetCount())
		progs.Remove(rm_list);
}

void HiAnimContext::StopProgram(HiAnimProgram& p) {
	TODO
}

void HiAnimContext::RemoveProgramGroup(int group) {
	if (group < 0)
		return;
	Vector<int> rm_list;
	int i = 0;
	for (HiAnimProgram& prog : progs) {
		if (prog.user_group == group)
			rm_list << i;
		i++;
	}
	if (!rm_list.IsEmpty())
		progs.Remove(rm_list);
}

void HiAnimContext::RemoveStopped() {
	Vector<int> rm_list;
	int i = 0;
	for (HiAnimProgram& prog : progs) {
		if (!prog.IsRunning())
			rm_list << i;
		i++;
	}
	if (!rm_list.IsEmpty())
		progs.Remove(rm_list);
}

void HiAnimContext::RemoveStoppedGroup(int group) {
	if (group < 0)
		return;
	Vector<int> rm_list;
	int i = 0;
	for (HiAnimProgram& prog : progs) {
		if (!prog.IsRunning() && prog.user_group == group)
			rm_list << i;
		i++;
	}
	if (!rm_list.IsEmpty())
		progs.Remove(rm_list);
}

Vector<HiAnimProgram*> HiAnimContext::FindGroupPrograms(int group) {
	Vector<HiAnimProgram*> v;
	for (HiAnimProgram& prog : progs) {
		if (prog.user_group == group)
			v.Add(&prog);
	}
	return v;
}



NAMESPACE_TOPSIDE_END

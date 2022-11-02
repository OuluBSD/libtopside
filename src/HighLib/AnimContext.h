#ifndef _HighLib_AnimContext_h_
#define _HighLib_AnimContext_h_

NAMESPACE_TOPSIDE_BEGIN


class HiAnimContext {
	
	
public:
	VectorMap<String, String>	code;
	ArrayMap<String, HiValue>	global;
	Array<HiAnimProgram>		progs;
	Animation	a;
	AnimPlayer	p;
	
	int op_limit = 1000000;
	
	bool keep_running = false;
	
	
	
public:
	typedef HiAnimContext CLASSNAME;
	HiAnimContext();
	
	void Clear();
	bool Init(bool run_main=true);
	void Iterate();
	void InitializeEmptyScene();
	void CreateProgram(String name);
	bool AddCodePath(String path);
	bool IsRunning() const;
	void StopProgram(HiAnimProgram& p);
	void RemoveProgramGroup(int group);
	void RemoveStopped();
	void RemoveStoppedGroup(int group);
	void ProcessAndRemoveGroup(int group);
	void KeepRunning(bool b=true) {keep_running = b;}
	bool HasProgram(HiAnimProgram& p);
	HiValue GetGlobal(String key);
	
	void HI_DrawText(HiEscape& e);
	
	HiAnimProgram* FindProgram(HiEscape& e);
	Vector<HiAnimProgram*> FindGroupPrograms(int group);
	
	template <class T>
	T& CreateProgramT(String name, int group) {
		T* o = new T();
		o->ctx = this;
		o->user_group = group;
		progs.Add(o);
		return *o;
	}
	
	
	Callback WhenStop;
	
};


NAMESPACE_TOPSIDE_END

#endif

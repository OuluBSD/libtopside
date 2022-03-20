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
	
	
	
	
public:
	typedef HiAnimContext CLASSNAME;
	HiAnimContext();
	
	void Clear();
	void Init();
	void Iterate();
	void CreateProgram(String name);
	bool IsRunning() const;
	void StopProgram(HiAnimProgram& p);
	void RemoveProgramGroup(int group);
	
	void HI_DrawText(HiEscape& e);
	
	HiAnimProgram* FindProgram(HiEscape& e);
	
	template <class T>
	T& CreateProgramT(String name, int group);
	
	
	Callback1<HiAnimProgram&> WhenStopProgram;
	Callback WhenStop;
	
};


NAMESPACE_TOPSIDE_END

#endif

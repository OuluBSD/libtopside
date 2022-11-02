#ifndef _HighLib_AnimProgram_h_
#define _HighLib_AnimProgram_h_

NAMESPACE_TOPSIDE_BEGIN


class HiAnimContext;



class HiAnimProgram {
	
protected:
	friend class HiAnimContext;
	
	bool is_native = false;
	bool is_native_running = false;
	Gate0 native_fn;
	HiAnimContext* ctx = 0;
	One<Hi> vm;
	String code;
	String fn_name;
	
public:
	HiValue a0, a1; // main function arguments
	HiValue user;
	dword user_flags;
	int user_type;
	int user_group;
	
public:
	typedef HiAnimProgram CLASSNAME;
	HiAnimProgram();
	virtual ~HiAnimProgram() {}
	
	void Clear();
	
	void Init(HiValue lambda);
	void Continue();
	void Stop();
	bool Process();
	void Iterate();
	HiAnimProgram& Set(Gate0 cb, HiValue a0=HiValue(), HiValue a1=HiValue());
	HiAnimProgram& Set(HiValue *self, HiValue fn, HiValue a0=HiValue(), HiValue a1=HiValue());
	
	bool IsVm() const {return !vm.IsEmpty();}
	Hi& GetVm() {return *vm;}
	bool IsRunning() const;
	
	void HI_DrawText(HiEscape& e);
	
	Callback ContinueCallback() {return THISBACK(Continue);}
	
	
	
	Callback1<HiAnimProgram&> WhenStop;
	
};


NAMESPACE_TOPSIDE_END

#endif

#ifndef _HighLib_AnimProgram_h_
#define _HighLib_AnimProgram_h_

NAMESPACE_TOPSIDE_BEGIN


class HiAnimContext;


class HiAnimProgram {
	
protected:
	friend class HiAnimContext;
	
	HiAnimContext* ctx = 0;
	One<Hi> vm;
	String code;
	
	
public:
	typedef HiAnimProgram CLASSNAME;
	HiAnimProgram();
	
	void Clear();
	
	void Init(HiValue lambda);
	void ContinueVm();
	void Iterate();
	
	bool IsVm() const {return !vm.IsEmpty();}
	Hi& GetVm() {return *vm;}
	bool IsRunning() const;
	
	void HI_DrawText(HiEscape& e);
	
};


NAMESPACE_TOPSIDE_END

#endif

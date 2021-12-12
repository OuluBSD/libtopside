#ifndef _SoftRend_Program_h_
#define _SoftRend_Program_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftProgram {
	bool inited = false;
	String err;
	
	
public:
	typedef SoftProgram CLASSNAME;
	SoftProgram();
	
	void Clear();
	bool Create();
	bool LinkProgram();
	void Attach(SoftShader& s);
	
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	String GetLastError() const {return err;}
	int GetParamInt(GVar::ProgParamType type);
	int GetVarSize(int idx) const;
	int GetVarType(int idx) const;
	String GetVar(int idx) const;
	void SetParameter(GVar::ParamType type, int i);
	
};


NAMESPACE_TOPSIDE_END

#endif

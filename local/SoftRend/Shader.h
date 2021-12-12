#ifndef _SoftRend_Shader_h_
#define _SoftRend_Shader_h_

NAMESPACE_TOPSIDE_BEGIN


class SoftShader {
	bool inited = false;
	GVar::ShaderType type;
	String src;
	String err;
	
public:
	typedef SoftShader CLASSNAME;
	SoftShader();
	
	void Clear();
	bool Create(GVar::ShaderType t);
	
	void SetSource(String s);
	void SetVar(int idx, int i);
	void SetVar(int idx, float f);
	void SetVar(int idx, float f0, float f1);
	void SetVar(int idx, float f0, float f1, float f2);
	void SetVar(int idx, float f0, float f1, float f2, float f3);
	GVar::ShaderType GetType() const {return type;}
	
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	String GetLastError() const {return err;}
	
};


NAMESPACE_TOPSIDE_END

#endif

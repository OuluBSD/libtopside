#ifndef _SoftRend_Program_h_
#define _SoftRend_Program_h_

NAMESPACE_PARALLEL_BEGIN


struct SoftUniform : Moveable<SoftUniform> {
	
};


template <class Gfx>
class SoftProgramT {
	bool inited = false;
	String err;
	
protected:
	using SoftShader = SoftShaderT<Gfx>;
	friend class SoftRend;
	Vector<SoftShader*> shaders;
	Vector<SoftUniform> uniforms;
	GenericShaderArgs args;
	GenericVertexShaderArgs vargs;
	GenericFragmentShaderArgs fargs;
	
public:
	typedef SoftProgramT CLASSNAME;
	SoftProgramT();
	
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
	void SetVar(int idx, int i);
	void SetVar(int idx, float f);
	void SetVar(int idx, float f0, float f1);
	void SetVar(int idx, float f0, float f1, float f2);
	void SetVar(int idx, float f0, float f1, float f2, float f3);
	void SetVar(int idx, const mat4& mat);
	
	GenericShaderArgs& GetArgs() {return args;}
	GenericVertexShaderArgs& GetVertexArgs() {return vargs;}
	GenericFragmentShaderArgs& GetFragmentArgs() {return fargs;}
	Vector<SoftShader*>& GetShaders() {return shaders;}
	
};


NAMESPACE_PARALLEL_END

#endif

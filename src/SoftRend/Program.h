#ifndef _SoftRend_Program_h_
#define _SoftRend_Program_h_

NAMESPACE_TOPSIDE_BEGIN


struct SoftUniform : Moveable<SoftUniform> {
	
};

class SoftPipeline;


struct SoftProgram {
	bool inited = false;
	String err;
	
protected:
	friend class SoftRend;
	Vector<SoftShader*> shaders;
	ArrayMap<dword, SoftUniform> uniforms;
	GenericShaderArgs args;
	struct Object {
		GenericVertexShaderArgs vargs;
		GenericFragmentShaderArgs fargs;
		
		void Zero() {memset(this, 0, sizeof(Object));}
	};
	Array<Object> objs;
	int obj_i = -1;
	
public:
	typedef SoftProgram CLASSNAME;
	SoftProgram();
	
	void Begin();
	void BeginObject();
	void EndObject();
	void Clear();
	bool Create();
	bool LinkProgram();
	void Attach(SoftShader& s);
	
	void operator=(const Nuller&) {Clear();}
	void operator=(int i) {if (!i) Clear();}
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
	void SetVarArray(int idx, int arr_size, int count, float* f);
	void SetVar(int idx, const mat4& mat);
	void BindTexture(int tex, const ByteImage* buf);
	
	GenericShaderArgs& GetArgs() {return args;}
	GenericVertexShaderArgs& GetVertexArgs(int i) {return objs[i].vargs;}
	GenericFragmentShaderArgs& GetFragmentArgs(int i) {return objs[i].fargs;}
	Vector<SoftShader*>& GetShaders() {return shaders;}
	
	
	
	SoftPipeline* pipeline = 0;
	
};


NAMESPACE_TOPSIDE_END

#endif

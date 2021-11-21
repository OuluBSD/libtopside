#ifndef _Graphics_OglCompiler_h_
#define _Graphics_OglCompiler_h_

NAMESPACE_TOPSIDE_BEGIN


class OglCompiler {
	String err;
	
	bool CompileShader(String code, ShaderVar::Type type, GLuint& shader_out);
	
public:
	
	OglCompiler();
	
	bool Compile(OglFramebufferState& fb_state, OglShaderState& shd_state, ShaderVar::Type type, String code, String library);
	String GetError() const {return err;}
	
	static void HotfixWebGLSL(String& s);
};


class OglLinker {
	String err;
	bool log = false;
	
public:
	bool Link(OglFramebufferState& fb_state);
	
	void EnableLog() {log = true;}
	void DisableLog() {log = false;}
	String GetError() const {return err;}
	
};


NAMESPACE_TOPSIDE_END

#endif

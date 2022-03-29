#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN


PKG(Graphics, Gfx, G) {
	IfaceLib::Add(this);
	
	COLOR(64,161,0)
	MAINFLAG(Screen)
	DEPENDENCY(Geometry)
	DEPENDENCY(SoftRend)
	
	PKG_IFACE {
		NATIVE_CLASS(Texture)
		NATIVE_CLASS(Shader)
		NATIVE_CLASS(ColorBuffer)
		NATIVE_CLASS(DepthBuffer)
		NATIVE_CLASS(FrameBuffer)
		NATIVE_CLASS(VertexArray)
		NATIVE_CLASS(VertexBuffer)
		NATIVE_CLASS(ElementBuffr)
		NATIVE_CLASS(Program)
		NATIVE_CLASS(Pipeline)
		UTIL_CLASS(SystemFramebuffer)
		UTIL_CLASS(ValFormat)
		
		/*
		FUNCTION1V(BindProgramPipeline, NativePipeline&)
		FUNCTION1V(UseProgram, NativeProgram&)
		FUNCTION0V(UnbindProgramPipeline)
		FUNCTION1R(GetShaderTemplate, const char*, ShaderType)
		FUNCTION1V(HotfixShaderCode, String&)
		FUNCTION1V(DrawBuffers, RenderTarget)
		FUNCTION1V(ActiveTexture, in)
		FUNCTION2R(CreateShader, bool, ShaderType, NativeShader&)
		FUNCTION2V(ShaderSource, NativeShader&, String)
		FUNCTION1R(CompileShader, bool, NativeShader& s);
		FUNCTION1R(GetLastErrorS, String, NativeShader& s);
		FUNCTION1R(GetLastErrorP, String, NativeProgram& s);
		FUNCTION1R(CreateProgram, bool, NativeProgram& prog);
		FUNCTION3V(ProgramParameteri, NativeProgram& prog, GVar::ParamType type, int i);
		FUNCTION2V(AttachShader, NativeProgram& prog, NativeShader& shdr);
		FUNCTION1V(DeleteShader, NativeShader& shdr);
		FUNCTION1R(LinkProgram, bool, NativeProgram& prog);
		FUNCTION3V(GetProgramiv, NativeProgram& prog, GVar::ProgParamType type, int& out);
		FUNCTION4R(GetActiveUniform, String, NativeProgram& prog, int i, int* size_out=0, int* type_out=0);
		FUNCTION1V(Clear, GVar::BufferType type);
		FUNCTION1V(GenProgramPipeline, NativePipeline& pipe);
		FUNCTION3V(UseProgramStages, NativePipeline& pipe, uint32 shader_type_bmask, NativeProgram& prog);
		FUNCTION1V(DeleteProgramPipeline, NativePipeline& pipe);
		FUNCTION3V(TexParameteri, GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat);
		FUNCTION1R(GenTexture, bool, NativeFrameBuffer& fb);
		FUNCTION1V(GenVertexArray, NativeVertexArray& vao);
		FUNCTION1V(GenVertexBuffer, NativeVertexBuffer& vbo);
		FUNCTION1V(GenElementBuffer, NativeElementBuffer& ebo);
		FUNCTION1V(BindVertexArray, NativeVertexArray& vao);
		FUNCTION1V(BindVertexBuffer, NativeVertexBuffer& vbo);
		FUNCTION1V(BindElementBuffer, NativeElementBuffer& ebo);
		FUNCTION1V(VertexBufferData, const Vector<Vertex>& vtx);
		FUNCTION1V(ElementBufferData, const Vector<uint32>& el);
		FUNCTION0V(SetupVertexStructure);
		FUNCTION0V(UnbindVertexArray);
		FUNCTION0V(UnbindVertexBuffer);
		FUNCTION0V(UnbindElementBuffer);
		FUNCTION0V(ActivateVertexStructure);
		FUNCTION0V(DeactivateVertexStructure);
		FUNCTION1V(DrawVertexElements, int element_limit);
		FUNCTION1V(TexImage2D, Texture& tex);
		FUNCTION1V(DeleteVertexArray, NativeVertexArray& vao);
		FUNCTION1V(DeleteVertexBuffer, NativeVertexBuffer& vbo);
		FUNCTION1V(DeleteElementBuffer, NativeElementBuffer& ebo);
		FUNCTION1V(DeleteTexture, NativeColorBuffer& b);
		
		FUNCTION2V(Uniform1i, int idx, int f);
		FUNCTION2V(Uniform1f, int idx, float f);
		FUNCTION3V(Uniform2f, int idx, float f0, float f1);
		FUNCTION4V(Uniform3f, int idx, float f0, float f1, float f2);
		FUNCTION5V(Uniform4f, int idx, float f0, float f1, float f2, float f3);
		FUNCTION2V(UniformMatrix4fv, int idx, const mat4& mat);
		
		
		FUNCTION0V(ClearBuffers);
		FUNCTION1V(SetSmoothShading, bool b=true);
		FUNCTION1V(SetDepthTest, bool b=true);
		FUNCTION1V(SetDepthOrderLess, bool b=true);
		FUNCTION2V(SetClearValue, RGBA clr, byte depth);
		FUNCTION1V(SetFastPerspectiveCorrection, bool b=true);
		FUNCTION1V(SetTriangleBacksideCulling, bool b=true);
		FUNCTION1V(SetTriangleFrontsideCCW, bool b=true);
		FUNCTION1V(SetViewport, Size sz);
		//FUNCTION0V(ActivateNextFrame);
		FUNCTION1V(SetDebugOutput, bool b=true);
		
		
		FUNCTION1V(BindFramebufferEXT, NativeFrameBuffer& fb);
		FUNCTION2V(BindTextureRO, GVar::TextureType type, const NativeFrameBuffer& tex);
		FUNCTION2V(BindTextureRW, GVar::TextureType type, NativeFrameBuffer& tex);
		FUNCTION1V(UnbindTexture, GVar::TextureType type);
		FUNCTION1V(GenerateMipmap, GVar::TextureType type);
		FUNCTION0V(BindFramebufferDefault);
		FUNCTION0V(RenderScreenRect);
		FUNCTION1V(SetContextDefaultFramebuffer, NativeFrameBuffer& fb);
		FUNCTION0V(BeginRender);
		FUNCTION0V(EndRender);
		*/
	}
	
	NAMESPACE {
		ENUM(RenderTarget) {
			ENUMVAL(COLOR0_EXT, 1 << 0)
		}
		CLASS(VertexShader) {
			
		}
		CLASS(FragmentShader) {
			
		}
		CLASS(DataObject) {
			
		}
		CLASS(DataState) {
			INHERIT(ErrorReporter)
			
		}
		CLASS(InputState) {
			INHERIT(ErrorReporter)
			
		}
		CLASS(Framebuffer) {
			INHERIT(ErrorReporter)
			
		}
		CLASS(Compiler) {
			INHERIT(ErrorReporter)
			
		}
		CLASS(Linker) {
			INHERIT(ErrorReporter)
			
		}
		/*CLASS(ShaderState) {
			
		}*/
		CLASS(ShaderPipeline) {
			
		}
		CLASS(RuntimeState) {
			INHERIT(ErrorReporter)
			
		}
		CLASS(ContextState) {
			
		}
		CLASS(Renderer) {
			
		}
		CLASS(StateDraw) {
			INHERIT(Draw)
			
		}
		CLASS(Buffer) {
			
		}
	}
	
	VENDOR(Cpu) {
		
		
		
	}
	
	VENDOR(Ogl) {
		
		
		
	}
	
}


NAMESPACE_PLAN_END

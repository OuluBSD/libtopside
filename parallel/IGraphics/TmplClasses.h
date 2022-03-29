// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IGraphics_TmplClasses_h_
#define _IGraphics_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Gfx> struct GraphicsVertexShaderT;
template <class Gfx> struct GraphicsFragmentShaderT;
template <class Gfx> struct GraphicsDataObjectT;
template <class Gfx> struct GraphicsDataStateT;
template <class Gfx> struct GraphicsInputStateT;
template <class Gfx> struct GraphicsFramebufferT;
template <class Gfx> struct GraphicsCompilerT;
template <class Gfx> struct GraphicsLinkerT;
template <class Gfx> struct GraphicsShaderPipelineT;
template <class Gfx> struct GraphicsRuntimeStateT;
template <class Gfx> struct GraphicsContextStateT;
template <class Gfx> struct GraphicsRendererT;
template <class Gfx> struct GraphicsStateDrawT;
template <class Gfx> struct GraphicsBufferT;


template <class Gfx>
struct GraphicsVertexShaderT : GfxVertexShader {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsFragmentShaderT : GfxFragmentShader {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsDataObjectT : GfxDataObject {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsDataStateT : GfxDataState {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsInputStateT : GfxInputState {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsFramebufferT : GfxFramebuffer {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsCompilerT : GfxCompiler {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsLinkerT : GfxLinker {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsShaderPipelineT : GfxShaderPipeline {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsRuntimeStateT : GfxRuntimeState {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsContextStateT : GfxContextState {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsRendererT : GfxRenderer {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsStateDrawT : GfxStateDraw {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Gfx>
struct GraphicsBufferT : GfxBuffer {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

using CpuVertexShader = GraphicsVertexShaderT<GfxCpu>;
using CpuFragmentShader = GraphicsFragmentShaderT<GfxCpu>;
using CpuDataObject = GraphicsDataObjectT<GfxCpu>;
using CpuDataState = GraphicsDataStateT<GfxCpu>;
using CpuInputState = GraphicsInputStateT<GfxCpu>;
using CpuFramebuffer = GraphicsFramebufferT<GfxCpu>;
using CpuCompiler = GraphicsCompilerT<GfxCpu>;
using CpuLinker = GraphicsLinkerT<GfxCpu>;
using CpuShaderPipeline = GraphicsShaderPipelineT<GfxCpu>;
using CpuRuntimeState = GraphicsRuntimeStateT<GfxCpu>;
using CpuContextState = GraphicsContextStateT<GfxCpu>;
using CpuRenderer = GraphicsRendererT<GfxCpu>;
using CpuStateDraw = GraphicsStateDrawT<GfxCpu>;
using CpuBuffer = GraphicsBufferT<GfxCpu>;
using OglVertexShader = GraphicsVertexShaderT<GfxOgl>;
using OglFragmentShader = GraphicsFragmentShaderT<GfxOgl>;
using OglDataObject = GraphicsDataObjectT<GfxOgl>;
using OglDataState = GraphicsDataStateT<GfxOgl>;
using OglInputState = GraphicsInputStateT<GfxOgl>;
using OglFramebuffer = GraphicsFramebufferT<GfxOgl>;
using OglCompiler = GraphicsCompilerT<GfxOgl>;
using OglLinker = GraphicsLinkerT<GfxOgl>;
using OglShaderPipeline = GraphicsShaderPipelineT<GfxOgl>;
using OglRuntimeState = GraphicsRuntimeStateT<GfxOgl>;
using OglContextState = GraphicsContextStateT<GfxOgl>;
using OglRenderer = GraphicsRendererT<GfxOgl>;
using OglStateDraw = GraphicsStateDrawT<GfxOgl>;
using OglBuffer = GraphicsBufferT<GfxOgl>;


NAMESPACE_PARALLEL_END



#endif


#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
SoftPipelineT<Gfx>::SoftPipelineT() {
	
}

template <class Gfx>
bool SoftPipelineT<Gfx>::Create() {
	
	inited = true;
	return true;
}

template <class Gfx>
void SoftPipelineT<Gfx>::Clear() {
	
	inited = false;
}

template <class Gfx>
void SoftPipelineT<Gfx>::Use(SoftProgram& prog, uint32 bmask) {
	Stage& s = stages.IsEmpty() ? stages.Add() : stages.Top();
	s.prog = &prog;
	s.bmask = bmask;
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftPipelineT)


NAMESPACE_PARALLEL_END

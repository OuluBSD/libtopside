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
void SoftPipelineT<Gfx>::Begin() {
	for (Stage& s : stages)
		if (s.prog)
			s.prog->Begin();
}

template <class Gfx>
void SoftPipelineT<Gfx>::Use(SoftProgram& prog, uint32 bmask) {
	for (Stage& s : stages) {
		if (s.prog == &prog) {
			s.bmask |= bmask;
			return;
		}
	}
	Stage& s = stages.Add();
	s.prog = &prog;
	s.bmask = bmask;
	ASSERT(prog.pipeline == 0);
	prog.pipeline = this;
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftPipelineT)


NAMESPACE_PARALLEL_END

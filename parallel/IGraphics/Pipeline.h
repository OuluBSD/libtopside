#ifndef _SoftRend_Pipeline_h_
#define _SoftRend_Pipeline_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class SoftPipelineT {
	bool inited = false;
	
public:
	using SoftProgram = SoftProgramT<Gfx>;
	
	struct Stage : Moveable<Stage> {
		SoftProgram* prog = 0;
		uint32 bmask = 0;
	};
	Vector<Stage> stages;
	
	
public:
	typedef SoftPipelineT CLASSNAME;
	SoftPipelineT();
	
	bool Create();
	void Clear();
	void Use(SoftProgram& prog, uint32 bmask);
	
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	
};


NAMESPACE_PARALLEL_END

#endif

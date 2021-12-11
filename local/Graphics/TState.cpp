#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN


template <class Gfx>
DataObjectT<Gfx>::DataObjectT() {
	vao = Null;
	vbo = Null;
	ebo = Null;
}

template <class Gfx>
DataObjectT<Gfx>::~DataObjectT() {
	FreeOgl();
}




template <class Gfx>
DataStateT<Gfx>::DataStateT() {
	
}

template <class Gfx>
typename Gfx::DataObject& DataStateT<Gfx>::AddObject() {
	DataObject* p = new DataObject();
	p->SetState(this);
	objects.Add(p);
	p->id = objects.GetCount() - 1;
	RendVer1(OnRealizeObject, p->id);
	return *p;
}

GFX_EXCPLICIT_INITIALIZE_CLASS(VertexShaderArgsT)
GFX_EXCPLICIT_INITIALIZE_CLASS(FragmentShaderArgsT)
GFX_EXCPLICIT_INITIALIZE_CLASS(DataObjectT)
GFX_EXCPLICIT_INITIALIZE_CLASS(DataStateT)

NAMESPACE_TOPSIDE_END

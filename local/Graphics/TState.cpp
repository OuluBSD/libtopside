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
void DataObjectT<Gfx>::Refresh(Mesh& m) {
	ASSERT(!vao && !vbo && !ebo);

	// Create objects
	Gfx::GenVertexArray(vao);
	Gfx::GenVertexBuffer(vbo);
	Gfx::GenElementBuffer(ebo);

	// Set vertex array object data
	Gfx::BindVertexArray(vao);
	Gfx::BindVertexBuffer(vbo);
	Gfx::VertexBufferData(m.vertices);

	// Set element buffer object data
	Gfx::BindElementBuffer(ebo);
	Gfx::ElementBufferData(m.indices);
	element_count = m.indices.GetCount();

	Gfx::SetupVertexStructure();
	
	Gfx::UnbindVertexArray();
}

template <class Gfx>
void DataObjectT<Gfx>::Paint() {
	ASSERT(element_count > 0)
	if (!element_count)
		return;
	
	// bind vbos for vertex array and index array
	Gfx::BindVertexArray(vao);
	Gfx::GenElementBuffer(ebo);
	Gfx::ActivateVertexStructure();
	
	// draw 6 faces using offset of index array
	Gfx::DrawVertexElements(element_count);
	
	Gfx::DeactivateVertexStructure();
	
	// bind with 0, so, switch back to normal pointer operation
	Gfx::UnbindVertexArray();
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

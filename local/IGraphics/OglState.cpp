#include "IGraphics.h"

#if defined flagSCREEN && defined flagOGL

NAMESPACE_PARALLEL_BEGIN


#if 0

void OglDataObject::FreeOgl() {
	if (vbo) {
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		glDeleteVertexArrays(1, &vao);
		vbo = 0;
		ebo = 0;
		vao = 0;
	}
	
	for (GLint gl_tex : tex.GetValues())
		glDeleteTextures(1, (GLuint*)&gl_tex);
	tex.Clear();
}

void OglDataObject::Refresh(Mesh& o) {
	/*ASSERT_(GetAppFlags().IsOpenGLContextOpen(), "OpenGL context is not open");
	if (!GetAppFlags().IsOpenGLContextOpen())
		return;*/
	
	ASSERT(!vao && !vbo && !ebo);
	
	auto& vertices = o.vertices;
	auto& indices = o.indices;
	
	// Create objects
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	
	// Set vertex array object data
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.GetCount() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
	// Set element buffer object data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.GetCount() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);
	element_count = indices.GetCount();
	
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	
	glBindVertexArray(0);
	
}

void OglDataObject::Paint() {
	ASSERT(vbo && ebo && element_count > 0)
	if (!vbo || !ebo || !element_count)
		return;
	
	// bind vbos for vertex array and index array
	glBindBuffer(GL_ARRAY_BUFFER, vbo);            // for vertex coordinates
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);    // for indices
	
	const int vtx = 0;
	const int nm = 1;
	const int tex = 2;
	glEnableVertexAttribArray(vtx);          // activate vertex position array
	glEnableVertexAttribArray(nm);           // activate vertex normal array
	glEnableVertexAttribArray(tex);          // activate texture coords array
	
	// set vertex arrays with generic API
	const int stride = sizeof(Vertex);
	const void* offset1 = 0; // Vertex::position
	const void* offset2 = (void*)(4*sizeof(float)); // Vertex::normal
	const void* offset3 = (void*)(7*sizeof(float)); // Vertex::tex_coords
	glVertexAttribPointer(vtx, 3, GL_FLOAT, false, stride, offset1);
	glVertexAttribPointer(nm,  3, GL_FLOAT, false, stride, offset2);
	glVertexAttribPointer(tex, 2, GL_FLOAT, false, stride, offset3);
	
	// draw 6 faces using offset of index array
	glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
	
	glDisableVertexAttribArray(vtx);         // deactivate vertex position
	glDisableVertexAttribArray(nm);          // deactivate vertex normal
	glDisableVertexAttribArray(tex);         // deactivate texture coords
	
	// bind with 0, so, switch back to normal pointer operation
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif


NAMESPACE_PARALLEL_END

#endif

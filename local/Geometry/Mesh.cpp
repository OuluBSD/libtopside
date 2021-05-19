#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN



void Mesh::Clear() {
	vertices.Clear();
	indices.Clear();
	material.Clear();
	for(int i = 0; i < TEXTYPE_COUNT; i++)
		tex_id[i] = -1;
	is_colored_only = false;
	is_lines = false;
	
	if (VBO) {
#if HAVE_OPENGL
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
#endif
	}
}

void Mesh::Set(const Vector<Vertex>& Vertices, const Vector<uint32>& indices) {
	this->vertices <<= vertices;
    this->indices <<= indices;
    
    SetupAutomatic();
}

void Mesh::SetupAutomatic() {
	AppFlags& f = GetAppFlags();
	if (f.IsOpenGL()) {
#if HAVE_OPENGL
		SetupOpenGL();
#else
		LOG("error: opengl is not supported in this executable");
#endif
	}
}

#if HAVE_OPENGL
void Mesh::SetupOpenGL() {
	ASSERT(VAO == 0);
	
	// Create objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	// Set vertex array object data
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.GetCount() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
	// Set element buffer object data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.GetCount() * sizeof(unsigned int),
	         &indices[0], GL_STATIC_DRAW);
	
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
#endif

void Mesh::UpdateBoundingBox() {
	int m_num_tri = indices.GetCount() / 3;
    Topside::ivec3 tri_indices = GetTriangleIndices(0);
    m_min = m_max = GetVertCoord(tri_indices[0]);
    m_min = m_max = GetVertCoord(tri_indices[1]);
    m_min = m_max = GetVertCoord(tri_indices[2]);
    for(int i = 1; i < static_cast<int>(m_num_tri); i++) {
        Topside::ivec3 tri_indices = GetTriangleIndices(i);
        Topside::vec3 p0 = GetVertCoord(tri_indices[0]);
        Topside::vec3 p1 = GetVertCoord(tri_indices[1]);
        Topside::vec3 p2 = GetVertCoord(tri_indices[2]);
        m_max = Topside::max(m_max, p0);
        m_min = Topside::min(m_min, p0);
        m_max = Topside::max(m_max, p1);
        m_min = Topside::min(m_min, p1);
        m_max = Topside::max(m_max, p2);
        m_min = Topside::min(m_min, p2);
    }
}

void Mesh::UpdateNormalsAndTangents() {
	int m_num_vertex = vertices.GetCount();
	int m_num_tri = indices.GetCount() / 3;
	
    for(int i = 0; i < static_cast<int>(m_num_vertex); i++) {
        SetVertNormal( i, Topside::vec3(0));
        SetVertTangent(i, Topside::vec3(0));
    }
    // is smooth
    if(false) {
        for(int i = 0; i < static_cast<int>(m_num_tri); i++) {
            Topside::ivec3 tri_indices = GetTriangleIndices(i);
            Topside::vec3 p0 = GetVertCoord(tri_indices[0]);
            Topside::vec3 p1 = GetVertCoord(tri_indices[1]);
            Topside::vec3 p2 = GetVertCoord(tri_indices[2]);
            Topside::vec3 e1 = safe_normalize(p1 - p0);
            Topside::vec3 e2 = safe_normalize(p2 - p0);
            Topside::vec3 n  = safe_normalize(Topside::cross(e1, e2));
            for(int j = 0; j < 3; j++) {
                int vert_index = tri_indices[j];
                SetVertNormal( vert_index, GetVertNormal(vert_index) + n);
                SetVertTangent(vert_index, Topside::vec3(0));
            }
        }
        for(int k = 0; k < static_cast<int>(m_num_vertex); k++) {
            SetVertNormal(k, safe_normalize(GetVertNormal(k)));
        }
        SetCount(m_num_vertex, m_num_tri);
        return;
    }
    for(int i = 0; i < static_cast<int>(m_num_tri); i++) {
        Topside::ivec3 tri_indices = GetTriangleIndices(i);
        Topside::vec3 p0 = GetVertCoord(tri_indices[0]);
        Topside::vec3 p1 = GetVertCoord(tri_indices[1]);
        Topside::vec3 p2 = GetVertCoord(tri_indices[2]);
        Topside::vec3 e1 = safe_normalize(p1 - p0);
        Topside::vec3 e2 = safe_normalize(p2 - p0);
        Topside::vec3 n  = safe_normalize(Topside::cross(e1, e2));
        for(int j = 0; j < 3; j++) {
            int vert_index = tri_indices[j];
            SetVertNormal( vert_index, n);
            SetVertTangent(vert_index, e1);
        }
    }
}

/*void Mesh::CenterAxis(BoundingBox::Align align) {
	UpdateBoundingBox();
    SetAxis(Topside::vec3(Topside::vec4(GetCenter(align), 1)));
}

void Mesh::SetAxis(Topside::vec3 axis)
{
	Topside::vec4 v(axis, 1);
	quat q;
	q[0] = v[0];
	q[1] = v[1];
	q[2] = v[2];
	q.w = v.w;
    Topside::vec3 local_axis = Topside::vec3(Topside::inverse(q));
    TransformVertices(Topside::translate(Topside::mat4(1), -local_axis));
    m_origin = in_parent_system(axis);
    mark_dirty_transform();
}

void Mesh::TransformVertices(Topside::mat4 transform)
{
    Topside::mat4 normal_transform = Topside::transpose(Topside::inverse(transform));
    for(int i = 0; i < static_cast<int>(m_num_vertex); i++) {
        SetVertCoord(i,   Topside::vec3(transform        * Topside::vec4(get_vert_coord(i),   1)));
        SetVertNormal(i,  Topside::vec3(normal_transform * Topside::vec4(get_vert_normal(i),  1)));
        SetVertTangent(i, Topside::vec3(normal_transform * Topside::vec4(get_vert_tangent(i), 1)));
    }
    UpdateBoundingBox();
}*/

void Mesh::Dump(int indent) {
	String in;
	in.Cat('\t', indent);
	LOG(in << "Vertices: " << vertices.GetCount());
	for(int i = 0; i < vertices.GetCount(); i++) {
		Vertex& v = vertices[i];
		LOG(in << "\t" << i << ": pos: " << v.position[0] << ", " << v.position[1] << ", " << v.position[2] << ". normal: " << v.normal[0] << ", " << v.normal[1] << ", " << v.normal[2]);
	}
	LOG(in << "Indices: " << indices.GetCount());
	for(int i = 0; i < indices.GetCount(); i++) {
		LOG(in << "\t" << i << ": " << (int)indices[i]);
	}
}

void Model::Dump() {
	for(int i = 0; i < meshes.GetCount(); i++) {
		LOG("Mesh " << i << ":");
		meshes[i].Dump(1);
	}
	LOG("Textures:");
	for(int i = 0; i < textures.GetCount(); i++) {
		LOG("\t" << i << ": " << (int)textures[i].width << "x" << (int)textures[i].height);
	}
}

NAMESPACE_TOPSIDE_END

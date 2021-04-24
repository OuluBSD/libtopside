#include "Geometry.h"

NAMESPACE_OULU_BEGIN



void Mesh::Clear() {
	vertices.Clear();
	indices.Clear();
	material.Clear();
	for(int i = 0; i < TEXTYPE_COUNT; i++)
		tex_id[i] = -1;
	is_colored_only = false;
	is_lines = false;
	
	if (VBO) {
#ifdef flagOPENGL
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
#ifdef flagOPENGL
		SetupOpenGL();
#else
		LOG("error: opengl is not supported in this executable");
#endif
	}
}

#ifdef flagOPENGL
void Mesh::SetupOpenGL() {
	
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
    Oulu::ivec3 tri_indices = GetTriangleIndices(0);
    m_min = m_max = GetVertCoord(tri_indices[0]);
    m_min = m_max = GetVertCoord(tri_indices[1]);
    m_min = m_max = GetVertCoord(tri_indices[2]);
    for(int i = 1; i < static_cast<int>(m_num_tri); i++) {
        Oulu::ivec3 tri_indices = GetTriangleIndices(i);
        Oulu::vec3 p0 = GetVertCoord(tri_indices[0]);
        Oulu::vec3 p1 = GetVertCoord(tri_indices[1]);
        Oulu::vec3 p2 = GetVertCoord(tri_indices[2]);
        m_max = Oulu::max(m_max, p0);
        m_min = Oulu::min(m_min, p0);
        m_max = Oulu::max(m_max, p1);
        m_min = Oulu::min(m_min, p1);
        m_max = Oulu::max(m_max, p2);
        m_min = Oulu::min(m_min, p2);
    }
}

void Mesh::UpdateNormalsAndTangents() {
	int m_num_vertex = vertices.GetCount();
	int m_num_tri = indices.GetCount() / 3;
	
    for(int i = 0; i < static_cast<int>(m_num_vertex); i++) {
        SetVertNormal( i, Oulu::vec3(0));
        SetVertTangent(i, Oulu::vec3(0));
    }
    // is smooth
    if(false) {
        for(int i = 0; i < static_cast<int>(m_num_tri); i++) {
            Oulu::ivec3 tri_indices = GetTriangleIndices(i);
            Oulu::vec3 p0 = GetVertCoord(tri_indices[0]);
            Oulu::vec3 p1 = GetVertCoord(tri_indices[1]);
            Oulu::vec3 p2 = GetVertCoord(tri_indices[2]);
            Oulu::vec3 e1 = safe_normalize(p1 - p0);
            Oulu::vec3 e2 = safe_normalize(p2 - p0);
            Oulu::vec3 n  = safe_normalize(Oulu::cross(e1, e2));
            for(int j = 0; j < 3; j++) {
                int vert_index = tri_indices[j];
                SetVertNormal( vert_index, GetVertNormal(vert_index) + n);
                SetVertTangent(vert_index, Oulu::vec3(0));
            }
        }
        for(int k = 0; k < static_cast<int>(m_num_vertex); k++) {
            SetVertNormal(k, safe_normalize(GetVertNormal(k)));
        }
        SetCount(m_num_vertex, m_num_tri);
        return;
    }
    for(int i = 0; i < static_cast<int>(m_num_tri); i++) {
        Oulu::ivec3 tri_indices = GetTriangleIndices(i);
        Oulu::vec3 p0 = GetVertCoord(tri_indices[0]);
        Oulu::vec3 p1 = GetVertCoord(tri_indices[1]);
        Oulu::vec3 p2 = GetVertCoord(tri_indices[2]);
        Oulu::vec3 e1 = safe_normalize(p1 - p0);
        Oulu::vec3 e2 = safe_normalize(p2 - p0);
        Oulu::vec3 n  = safe_normalize(Oulu::cross(e1, e2));
        for(int j = 0; j < 3; j++) {
            int vert_index = tri_indices[j];
            SetVertNormal( vert_index, n);
            SetVertTangent(vert_index, e1);
        }
    }
}

/*void Mesh::CenterAxis(BoundingBox::Align align) {
	UpdateBoundingBox();
    SetAxis(Oulu::vec3(Oulu::vec4(GetCenter(align), 1)));
}

void Mesh::SetAxis(Oulu::vec3 axis)
{
	Oulu::vec4 v(axis, 1);
	quat q;
	q[0] = v[0];
	q[1] = v[1];
	q[2] = v[2];
	q.w = v.w;
    Oulu::vec3 local_axis = Oulu::vec3(Oulu::inverse(q));
    TransformVertices(Oulu::translate(Oulu::mat4(1), -local_axis));
    m_origin = in_parent_system(axis);
    mark_dirty_transform();
}

void Mesh::TransformVertices(Oulu::mat4 transform)
{
    Oulu::mat4 normal_transform = Oulu::transpose(Oulu::inverse(transform));
    for(int i = 0; i < static_cast<int>(m_num_vertex); i++) {
        SetVertCoord(i,   Oulu::vec3(transform        * Oulu::vec4(get_vert_coord(i),   1)));
        SetVertNormal(i,  Oulu::vec3(normal_transform * Oulu::vec4(get_vert_normal(i),  1)));
        SetVertTangent(i, Oulu::vec3(normal_transform * Oulu::vec4(get_vert_tangent(i), 1)));
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

NAMESPACE_OULU_END

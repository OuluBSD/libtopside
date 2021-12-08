#include "Geometry.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN



void Mesh::Clear() {
	vertices.Clear();
	indices.Clear();
	material.Clear();
	for(int i = 0; i < TEXTYPE_COUNT; i++)
		tex_id[i] = -1;
	is_colored_only = false;
	is_lines = false;
	
}

void Mesh::Set(GfxDataObject& o, const Vector<Vertex>& Vertices, const Vector<uint32>& indices) {
	this->vertices <<= vertices;
    this->indices <<= indices;
    
    Refresh(o);
}

void Mesh::Refresh(GfxDataObject& o) {
	if (o.IsOpenGL()) {
#if HAVE_OPENGL
		RefreshOgl(o);
#else
		LOG("Mesh::Refresh: error: opengl is not supported in this executable");
#endif
	}
	else if (o.IsSoftware()) {
		RefreshSw(o);
	}
	else {
		TODO
	}
}

void Mesh::UpdateBoundingBox() {
	int m_num_tri = indices.GetCount() / 3;
    TS::ivec3 tri_indices = GetTriangleIndices(0);
    m_min = m_max = GetVertCoord(tri_indices[0]);
    m_min = m_max = GetVertCoord(tri_indices[1]);
    m_min = m_max = GetVertCoord(tri_indices[2]);
    for(int i = 1; i < static_cast<int>(m_num_tri); i++) {
        TS::ivec3 tri_indices = GetTriangleIndices(i);
        TS::vec3 p0 = GetVertCoord(tri_indices[0]);
        TS::vec3 p1 = GetVertCoord(tri_indices[1]);
        TS::vec3 p2 = GetVertCoord(tri_indices[2]);
        m_max = TS::Max(m_max, p0);
        m_min = TS::Min(m_min, p0);
        m_max = TS::Max(m_max, p1);
        m_min = TS::Min(m_min, p1);
        m_max = TS::Max(m_max, p2);
        m_min = TS::Min(m_min, p2);
    }
}

void Mesh::UpdateNormalsAndTangents() {
	int m_num_vertex = vertices.GetCount();
	int m_num_tri = indices.GetCount() / 3;
	
    for(int i = 0; i < static_cast<int>(m_num_vertex); i++) {
        SetVertNormal( i, TS::vec3(0));
        SetVertTangent(i, TS::vec3(0));
    }
    // is smooth
    if(false) {
        for(int i = 0; i < static_cast<int>(m_num_tri); i++) {
            TS::ivec3 tri_indices = GetTriangleIndices(i);
            TS::vec3 p0 = GetVertCoord(tri_indices[0]);
            TS::vec3 p1 = GetVertCoord(tri_indices[1]);
            TS::vec3 p2 = GetVertCoord(tri_indices[2]);
            TS::vec3 e1 = safe_normalize(p1 - p0);
            TS::vec3 e2 = safe_normalize(p2 - p0);
            TS::vec3 n  = safe_normalize(TS::cross(e1, e2));
            for(int j = 0; j < 3; j++) {
                int vert_index = tri_indices[j];
                SetVertNormal( vert_index, GetVertNormal(vert_index) + n);
                SetVertTangent(vert_index, TS::vec3(0));
            }
        }
        for(int k = 0; k < static_cast<int>(m_num_vertex); k++) {
            SetVertNormal(k, safe_normalize(GetVertNormal(k)));
        }
        SetCount(m_num_vertex, m_num_tri);
        return;
    }
    for(int i = 0; i < static_cast<int>(m_num_tri); i++) {
        TS::ivec3 tri_indices = GetTriangleIndices(i);
        TS::vec3 p0 = GetVertCoord(tri_indices[0]);
        TS::vec3 p1 = GetVertCoord(tri_indices[1]);
        TS::vec3 p2 = GetVertCoord(tri_indices[2]);
        TS::vec3 e1 = safe_normalize(p1 - p0);
        TS::vec3 e2 = safe_normalize(p2 - p0);
        TS::vec3 n  = safe_normalize(TS::cross(e1, e2));
        for(int j = 0; j < 3; j++) {
            int vert_index = tri_indices[j];
            SetVertNormal( vert_index, n);
            SetVertTangent(vert_index, e1);
        }
    }
}

/*void Mesh::CenterAxis(BoundingBox::Align align) {
	UpdateBoundingBox();
    SetAxis(TS::vec3(TS::vec4(GetCenter(align), 1)));
}

void Mesh::SetAxis(TS::vec3 axis)
{
	TS::vec4 v(axis, 1);
	quat q;
	q[0] = v[0];
	q[1] = v[1];
	q[2] = v[2];
	q.w = v.w;
    TS::vec3 local_axis = TS::vec3(TS::inverse(q));
    TransformVertices(TS::translate(TS::mat4(1), -local_axis));
    m_origin = in_parent_system(axis);
    mark_dirty_transform();
}

void Mesh::TransformVertices(TS::mat4 transform)
{
    TS::mat4 normal_transform = TS::transpose(TS::inverse(transform));
    for(int i = 0; i < static_cast<int>(m_num_vertex); i++) {
        SetVertCoord(i,   TS::vec3(transform        * TS::vec4(get_vert_coord(i),   1)));
        SetVertNormal(i,  TS::vec3(normal_transform * TS::vec4(get_vert_normal(i),  1)));
        SetVertTangent(i, TS::vec3(normal_transform * TS::vec4(get_vert_tangent(i), 1)));
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

void ModelMesh::Dump() {
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

#endif

#include "Geometry.h"


#define _VEC_LEFT    vec3(1.0f, 0.0f, 0.0f)
#define _VEC_UP      vec3(0.0f, 1.0f, 0.0f)
#define _VEC_FORWARD vec3(0.0f, 0.0f, 1.0f)

NAMESPACE_TOPSIDE_BEGIN


bool mb_disable_textures = false;

Mesh& ModelBuilder::AddPlane(const vec3& pos, const vec2& size, int grid_steps) {
	this->model.Create();
	Model& model = *this->model;
	Mesh& m = model.meshes.Add();
	MeshFactory::CreateGrid(m, grid_steps, grid_steps, size[0], size[1]);
	
	for(Vertex& v : m.vertices) {
		v.position += pos;
	}
	
	model.SetTexture(m, TEXTYPE_DIFFUSE, GetDefaultImage(IMAGEID_GRID), "grid");
	m.disable_textures = mb_disable_textures;
	//m.Refresh();
	return m;
}

Mesh& ModelBuilder::AddBox(const vec3& pos, const vec3& dim, bool centered, bool skybox) {
	this->model.Create();
	Model& model = *this->model;
	Mesh& m = model.meshes.Add();
	
	vec3 off = (centered ? dim * -0.5 : vec3(0,0,0)) + pos;
	
	MeshFactory::CreateBox(m, dim[0], dim[1], dim[2], skybox);
	
	for(Vertex& v : m.vertices) {
		v.position += off;
	}
	
	model.SetTexture(m, TEXTYPE_DIFFUSE, GetDefaultImage(IMAGEID_GRID), "grid");
	m.disable_textures = mb_disable_textures;
	//m.Refresh();
	return m;
}

Mesh& ModelBuilder::AddSphere(const vec3& pos, float radius, int slices, int stacks) {
	this->model.Create();
	Model& model = *this->model;
	Mesh& m = model.meshes.Add();
	MeshFactory::CreateSphere(m, slices, stacks, radius);
	
	for(Vertex& v : m.vertices) {
		v.position += pos;
	}
	
	model.SetTexture(m, TEXTYPE_DIFFUSE, GetDefaultImage(IMAGEID_GRID), "grid");
	m.disable_textures = mb_disable_textures;
	//m.Refresh();
	return m;
}

Mesh& ModelBuilder::AddCylinder(const vec3& pos, float radius, float length, int slices) {
	this->model.Create();
	Model& model = *this->model;
	
	ModelNode& node = model.AddNode("PaintTip");
	
	Mesh& m = model.meshes.Add();
	MeshFactory::CreateCylinder(m, slices, radius, length, &node);
	
	// update node with given position argument
	mat4 trans = Translate(pos);
	node.local_transform *= trans;
	
	// update vertices with with given position argument
	for(Vertex& v : m.vertices) {
		v.position += pos;
	}
	
	model.SetTexture(m, TEXTYPE_DIFFUSE, GetDefaultImage(IMAGEID_GRID), "grid");
	m.disable_textures = mb_disable_textures;
	//m.Refresh();
	return m;
}



vec3 euler_to_offset(vec3  euler,
                     vec3* up_direction = NULL)
{
    if (up_direction) {
        mat4 euler_transform = GetEulerAngleYXZ(euler);
        *up_direction = (euler_transform * MakeVec4(_VEC_UP, 1)).Splice();
        return (euler_transform * MakeVec4(_VEC_FORWARD, 1)).Splice();
    }
    mat4 euler_transform_sans_roll = GetEulerAngleYX(euler);
    return (euler_transform_sans_roll * MakeVec4(_VEC_FORWARD, 1)).Splice();
}



class Mesh;


void MeshFactory::GetBoxCorners(vec3        (&points)[8],
                                       const vec3* origin,
                                       const vec3* dim)
{
    // points
    //
    //     y
    //     4-------7
    //    /|      /|
    //   / |     / |
    //  5-------6  |
    //  |  0----|--3 x
    //  | /     | /
    //  |/      |/
    //  1-------2
    // z

    points[0] = vec3(0, 0, 0);
    points[1] = vec3(0, 0, 1);
    points[2] = vec3(1, 0, 1);
    points[3] = vec3(1, 0, 0);
    points[4] = vec3(0, 1, 0);
    points[5] = vec3(0, 1, 1);
    points[6] = vec3(1, 1, 1);
    points[7] = vec3(1, 1, 0);
    if(!origin && !dim) {
        return;
    }
    vec3 _origin = origin ? *origin : vec3(0,0,0);
    vec3 _dim    = dim    ? *dim    : vec3(1,1,1);
    for(int i = 0; i < 8; i++) {
        vec3 m = points[i] * _dim;
        vec3 n = _origin + m;
        points[i] = n;
    }
}

void MeshFactory::CreateGrid(Mesh& mesh,
                                          int          cols,
                                          int          rows,
                                          float        width,
                                          float        length,
                                          float        tex_width_scale,
                                          float        tex_length_scale,
                                          bool         use_quad) {
	if (!use_quad)
		CreateGridTriangles(mesh, cols, rows, width, length, tex_width_scale, tex_length_scale);
	else
		CreateGridQuad(mesh, cols, rows, width, length, tex_width_scale, tex_length_scale);
}

void MeshFactory::CreateGridQuad(Mesh& mesh,
                                          int          cols,
                                          int          rows,
                                          float        width,
                                          float        length,
                                          float        tex_width_scale,
                                          float        tex_length_scale) {
    int       num_vertex = (rows + 1) * (cols + 1);
    int       num_quad    = rows * cols * 2;
    mesh.SetCountQuads(num_vertex, num_quad);
	
    // ==============================
    // init mesh vertex/normal coords
    // ==============================

    int vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            mesh.SetVertCoord( vert_index, vec3(
                    width * (static_cast<float>(col) / cols),
                    0,
                    length * (1 - static_cast<float>(row) / rows)));
            mesh.SetVertNormal( vert_index, vec3(0, 1, 0));
            mesh.SetVertTangent(vert_index, vec3(1, 0, 0));
            vert_index++;
        }
    }
	
    // ========================
    // init mesh texture coords
    // ========================
	
    int tex_vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            mesh.SetTexCoord(tex_vert_index++,
                vec2(
                    static_cast<float>(col) / cols / tex_width_scale,
                    1 - static_cast<float>(row) / rows / tex_length_scale));
        }
    }

    // ==========================
    // init mesh triangle indices
    // ==========================

    int quad_index = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            int lower_left  = row * (cols + 1) + col;
            int lower_right = lower_left + 1;
            int upper_left  = (row + 1) * (cols + 1) + col;
            int upper_right = upper_left + 1;
            mesh.SetQuadIndices(quad_index++, ivec4(lower_left, lower_right, upper_right, upper_left));
        }
    }

    mesh.UpdateBoundingBox();
}

void MeshFactory::CreateGridTriangles(Mesh& mesh,
                                          int          cols,
                                          int          rows,
                                          float        width,
                                          float        length,
                                          float        tex_width_scale,
                                          float        tex_length_scale)
{
    int       num_vertex = (rows + 1) * (cols + 1);
    int       num_tri    = rows * cols * 2;
    mesh.SetCountTriangles(num_vertex, num_tri);

    // ==============================
    // init mesh vertex/normal coords
    // ==============================

    int vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            mesh.SetVertCoord( vert_index, vec3(
                    width * (static_cast<float>(col) / cols),
                    0,
                    length * (1 - static_cast<float>(row) / rows)));
            mesh.SetVertNormal( vert_index, vec3(0, 1, 0));
            mesh.SetVertTangent(vert_index, vec3(1, 0, 0));
            vert_index++;
        }
    }

    // ========================
    // init mesh texture coords
    // ========================
	
	// tex coord moved to vertex
    int tex_vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            mesh.SetTexCoord(tex_vert_index++, vec2(
                    static_cast<float>(col) / cols / tex_width_scale,
                    1 - static_cast<float>(row) / rows / tex_length_scale));
        }
    }

    // ==========================
    // init mesh triangle indices
    // ==========================

    int tri_index = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            int lower_left  = row * (cols + 1) + col;
            int lower_right = lower_left + 1;
            int upper_left  = (row + 1) * (cols + 1) + col;
            int upper_right = upper_left + 1;
            mesh.SetTriangleIndices(tri_index++, ivec3(lower_left, lower_right, upper_right));
            mesh.SetTriangleIndices(tri_index++, ivec3(upper_right, upper_left, lower_left));
        }
    }

    mesh.UpdateBoundingBox();

    ASSERT(vert_index == num_vertex);
    ASSERT(tri_index  == num_tri);
}

void MeshFactory::CreateSphere(Mesh& mesh,
                                            int          slices,
                                            int          stacks,
                                            float        radius)
{
    int       cols = slices;
    int       rows = stacks;
    CreateGrid(mesh, cols, rows);

    // ==============================
    // init mesh vertex/normal coords
    // ==============================

    int vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            vec3 normal = euler_to_offset(vec3(
                    0,
                    -(static_cast<float>(row) / rows * M_PI - M_PI_2), // pitch
                    static_cast<float>(col) / cols * M_2PI));       // yaw
            vec3 offset = normal * radius;
            mesh.SetVertCoord(  vert_index, offset);
            mesh.SetVertNormal( vert_index, safe_normalize(offset));
            mesh.SetVertTangent(vert_index, euler_to_offset(vec3(
                    0,
                    0,                                            // pitch
                    static_cast<float>(col) / cols * M_2PI + M_PI_2))); // yaw
            vert_index++;
        }
    }

    mesh.UpdateBoundingBox();
}

void MeshFactory::CreateHemisphere(Mesh& mesh,
                                                int          slices,
                                                int          stacks,
                                                float        radius)
{
    int       cols = slices;
    int       rows = stacks * 0.5 + 2;
    CreateGrid(mesh, cols, rows);

    // ==============================
    // init mesh vertex/normal coords
    // ==============================

    int vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            switch(row) {
                case 0: // bottom
                    mesh.SetVertCoord( vert_index, vec3(0,  0, 0));
                    mesh.SetVertNormal(vert_index, vec3(0, -1, 0));
                    break;
                default:
                    {
                        vec3 offset = euler_to_offset(vec3(
                                0,
                                (row == 1) ? 0 : -(static_cast<float>(row - 2) / (rows - 2) * M_PI_2), // pitch
                                static_cast<float>(col) / cols * M_2PI))                             // yaw
                                *radius;
                        mesh.SetVertCoord( vert_index, offset);
                        mesh.SetVertNormal(vert_index, (row == 1) ?
                                vec3(0, -1, 0) : safe_normalize(offset));
                    }
                    break;
            }
            mesh.SetVertTangent(vert_index, euler_to_offset(vec3(
                    0,
                    0,                                            // pitch
                    static_cast<float>(col) / cols * M_2PI + M_PI_2))); // yaw
            vert_index++;
        }
    }

    mesh.UpdateBoundingBox();
}

void MeshFactory::CreateCylinder(Mesh& mesh,
                                              int          slices,
                                              float        radius,
                                              float        height,
                                              ModelNode*	tip)
{
    int       cols = slices;
    int       rows = 5;
    CreateGrid(mesh, cols, rows);

    // ==============================
    // init mesh vertex/normal coords
    // ==============================
	
	if (tip) {
		vec3 top_center(0, height, 0); // see case 5, "top"
		tip->local_transform = Translate(top_center);
		tip->modify_count++;
	}
	
    int vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            switch(row) {
                case 0: // bottom
                    mesh.SetVertCoord( vert_index, vec3(0,  0, 0));
                    mesh.SetVertNormal(vert_index, vec3(0, -1, 0));
                    break;
                case 1: // bottom rim
                case 2: // bottom side rim
                    {
                        vec3 offset = euler_to_offset(vec3(
                                0,
                                0,                                     // pitch
                                static_cast<float>(col) / cols * M_2PI)) // yaw
                                *radius;
                        mesh.SetVertCoord( vert_index, vec3(offset[0], 0, offset[2]));
                        mesh.SetVertNormal(vert_index, (row == 1) ?
                                vec3(0, -1, 0) : safe_normalize(offset));
                    }
                    break;
                case 3: // top side rim
                case 4: // top rim
                    {
                        vec3 offset = euler_to_offset(vec3(
                                0,
                                0,                                     // pitch
                                static_cast<float>(col) / cols * M_2PI)) // yaw
                                *radius;
                        mesh.SetVertCoord( vert_index, vec3(offset[0], height, offset[2]));
                        mesh.SetVertNormal(vert_index, (row == 4) ?
                                vec3(0, 1, 0) : safe_normalize(offset));
                    }
                    break;
                case 5: // top
                    mesh.SetVertCoord( vert_index, vec3(0, height, 0));
                    mesh.SetVertNormal(vert_index, vec3(0, 1, 0));
                    break;
            }
            mesh.SetVertTangent(vert_index, euler_to_offset(vec3(
                    0,
                    0,                                            // pitch
                    static_cast<float>(col) / cols * M_2PI + M_PI_2))); // yaw
            
            if (tip)
                mesh.SetNodeIndex(vert_index, tip->index);
            
            vert_index++;
        }
    }

    mesh.UpdateBoundingBox();
}

void MeshFactory::CreateCone(Mesh& mesh,
                                          int          slices,
                                          float        radius,
                                          float        height)
{
    int       cols = slices;
    int       rows = 3;
    CreateGrid(mesh, cols, rows);

    // ==============================
    // init mesh vertex/normal coords
    // ==============================

    float rim_y_offset = radius * sin(M_PI_2 - atan(height / radius));
    int vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            switch(row) {
                case 0: // bottom
                    mesh.SetVertCoord( vert_index, vec3(0,  0, 0));
                    mesh.SetVertNormal(vert_index, vec3(0, -1, 0));
                    break;
                case 1: // bottom rim
                case 2: // side rim
                    {
                        vec3 offset = euler_to_offset(vec3(
                                0,
                                0,                                     // pitch
                                static_cast<float>(col) / cols * M_2PI)) // yaw
                                *radius;
                        mesh.SetVertCoord( vert_index, offset);
                        mesh.SetVertNormal(vert_index, (row == 1) ?
                                vec3(0, -1, 0) : safe_normalize(offset + vec3(0, rim_y_offset, 0)));
                    }
                    break;
                case 3: // tip
                    {
                        vec3 offset = euler_to_offset(vec3(
                                0,
                                0,                                     // pitch
                                static_cast<float>(col) / cols * M_2PI)) // yaw
                                *radius;
                        mesh.SetVertCoord( vert_index, vec3(0, height, 0));
                        mesh.SetVertNormal(vert_index, safe_normalize(offset + vec3(0, rim_y_offset, 0)));
                    }
                    break;
            }
            mesh.SetVertTangent(vert_index, euler_to_offset(vec3(
                    0,
                    0,                                            // pitch
                    static_cast<float>(col) / cols * M_2PI + M_PI_2))); // yaw
            vert_index++;
        }
    }

    mesh.UpdateBoundingBox();
}

void MeshFactory::CreateTorus(Mesh& mesh,
                                           int          slices,
                                           int          stacks,
                                           float        radius_major,
                                           float        radius_minor)
{
    int       cols = slices;
    int       rows = stacks;
    CreateGrid(mesh, cols, rows);

    // ==============================
    // init mesh vertex/normal coords
    // ==============================

    int vert_index = 0;
    for(int row = 0; row <= rows; row++) {
        for(int col = 0; col <= cols; col++) {
            vec3 normal_major = euler_to_offset(vec3(
                    0,
                    0,                                      // pitch
                    static_cast<float>(col) / cols * M_2PI)); // yaw
            vec3 normal_minor = euler_to_offset(vec3(
                    0,
                    -(static_cast<float>(row) / rows * M_2PI - M_PI), // pitch
                    static_cast<float>(col) / cols * M_2PI));        // yaw
            mesh.SetVertCoord(  vert_index, normal_major * radius_major + normal_minor * radius_minor);
            mesh.SetVertNormal( vert_index, normal_minor);
            mesh.SetVertTangent(vert_index, euler_to_offset(vec3(
                    0,
                    0,                                            // pitch
                    static_cast<float>(col) / cols * M_2PI + M_PI_2))); // yaw
            vert_index++;
        }
    }

    mesh.UpdateBoundingBox();
}

void MeshFactory::CreateBox(Mesh& mesh,
                            float        width,
                            float        height,
                            float        length,
                            bool skybox)
{
    mesh.SetCountTriangles(24, 12);

    // ==============================
    // init mesh vertex/normal coords
    // ==============================

    vec3 points[8];

    // points
    //
    //     y
    //     4-------7
    //    /|      /|
    //   / |     / |
    //  5-------6  |
    //  |  0----|--3 x
    //  | /     | /
    //  |/      |/
    //  1-------2
    // z

    vec3 dim(width, height, length);
    GetBoxCorners(points, NULL, &dim);

    int tri_indices[6][4];
    vec3 tri_normals[6];
    vec3 tri_tangents[6];

    // right
    //
    //     y
    //     3-------*
    //    /|      /|
    //   / |     / |
    //  2-------*  |
    //  |  0----|--* x
    //  | /     | /
    //  |/      |/
    //  1-------*
    // z

    tri_indices[0][0] = 0;
    tri_indices[0][1] = 1;
    tri_indices[0][2] = 5;
    tri_indices[0][3] = 4;
    tri_normals[0]  = vec3(-1, 0, 0);
    tri_tangents[0] = vec3(0, 0, 1);

    // front
    //
    //     y
    //     *-------*
    //    /|      /|
    //   / |     / |
    //  3-------2  |
    //  |  *----|--* x
    //  | /     | /
    //  |/      |/
    //  0-------1
    // z

    tri_indices[1][0] = 1;
    tri_indices[1][1] = 2;
    tri_indices[1][2] = 6;
    tri_indices[1][3] = 5;
    tri_normals[1]  = vec3(0, 0, 1);
    tri_tangents[1] = vec3(1, 0, 0);

    // left
    //
    //     y
    //     *-------2
    //    /|      /|
    //   / |     / |
    //  *-------3  |
    //  |  *----|--1 x
    //  | /     | /
    //  |/      |/
    //  *-------0
    // z

    tri_indices[2][0] = 2;
    tri_indices[2][1] = 3;
    tri_indices[2][2] = 7;
    tri_indices[2][3] = 6;
    tri_normals[2]  = vec3(1, 0, 0);
    tri_tangents[2] = vec3(0, 0, -1);

    // back
    //
    //     y
    //     2-------3
    //    /|      /|
    //   / |     / |
    //  *-------*  |
    //  |  1----|--0 x
    //  | /     | /
    //  |/      |/
    //  *-------*
    // z

    tri_indices[3][0] = 3;
    tri_indices[3][1] = 0;
    tri_indices[3][2] = 4;
    tri_indices[3][3] = 7;
    tri_normals[3]  = vec3(0, 0, -1);
    tri_tangents[3] = vec3(-1, 0, 0);

    // top
    //
    //     y
    //     1-------0
    //    /|      /|
    //   / |     / |
    //  2-------3  |
    //  |  *----|--* x
    //  | /     | /
    //  |/      |/
    //  *-------*
    // z

    tri_indices[4][0] = 7;
    tri_indices[4][1] = 4;
    tri_indices[4][2] = 5;
    tri_indices[4][3] = 6;
    tri_normals[4]  = vec3(0, 1, 0);
    tri_tangents[4] = vec3(-1, 0, 0);

    // bottom
    //
    //     y
    //     *-------*
    //    /|      /|
    //   / |     / |
    //  *-------*  |
    //  |  0----|--1 x
    //  | /     | /
    //  |/      |/
    //  3-------2
    // z

    tri_indices[5][0] = 0;
    tri_indices[5][1] = 3;
    tri_indices[5][2] = 2;
    tri_indices[5][3] = 1;
    tri_normals[5]  = vec3(0, -1, 0);
    tri_tangents[5] = vec3(1, 0, 0);

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            int vert_index = i * 4 + j;
            int idx = tri_indices[i][j];
            vec3 pt = points[idx];
            mesh.SetVertCoord(  vert_index, pt);
            mesh.SetVertNormal( vert_index, tri_normals[i]);
            mesh.SetVertTangent(vert_index, tri_tangents[i]);
        }
    }

    // ========================
    // init mesh texture coords
    // ========================

    // right
	
	// tex coord moved to vertex
    mesh.SetTexCoord(0, vec2(0, 0));
    mesh.SetTexCoord(1, vec2(1, 0));
    mesh.SetTexCoord(2, vec2(1, 1));
    mesh.SetTexCoord(3, vec2(0, 1));

    for(int i = 4; i < 24; i++) {
        mesh.SetTexCoord(i, mesh.GetTexCoord(i % 4));
    }

    // ==========================
    // init mesh triangle indices
    // ==========================

    // right
    mesh.SetTriangleIndices(0, ivec3(0, 1, 2));
    mesh.SetTriangleIndices(1, ivec3(2, 3, 0));

    // front
    mesh.SetTriangleIndices(2, ivec3(4, 5, 6));
    mesh.SetTriangleIndices(3, ivec3(6, 7, 4));

    // left
    mesh.SetTriangleIndices(4, ivec3(8,  9, 10));
    mesh.SetTriangleIndices(5, ivec3(10, 11, 8));

    // back
    mesh.SetTriangleIndices(6, ivec3(12, 13, 14));
    mesh.SetTriangleIndices(7, ivec3(14, 15, 12));

    // top
    mesh.SetTriangleIndices(8, ivec3(16, 17, 18));
    mesh.SetTriangleIndices(9, ivec3(18, 19, 16));

    // bottom
    mesh.SetTriangleIndices(10, ivec3(20, 21, 22));
    mesh.SetTriangleIndices(11, ivec3(22, 23, 20));
	
	if (skybox) {
		for(int i = 0; i < 12; i++) {
			int a = i * 3 + 1;
			int b = i * 3 + 2;
			int tmp = mesh.indices[a];
			mesh.indices[a] = mesh.indices[b];
			mesh.indices[b] = tmp;
		}
		for (Vertex& vtx : mesh.vertices)
			vtx.normal = vtx.normal * vec3(-1);
	}
	
    mesh.UpdateBoundingBox();
}

void MeshFactory::CreateTetrahedron(Mesh& mesh,
                                                 float        width,
                                                 float        height,
                                                 float        length)
{
    mesh.SetCountTriangles(12, 4);

    // triangle opposite to origin
    mesh.SetVertCoord(0, vec3(1, 0, 0));
    mesh.SetVertCoord(1, vec3(0, 0, 1));
    mesh.SetVertCoord(2, vec3(0, 1, 0));

    // triangle starting at x
    mesh.SetVertCoord(3, vec3(1, 0, 0));
    mesh.SetVertCoord(4, vec3(0, 1, 0));
    mesh.SetVertCoord(5, vec3(1, 1, 1));

    // triangle starting at y
    mesh.SetVertCoord(6, vec3(0, 1, 0));
    mesh.SetVertCoord(7, vec3(0, 0, 1));
    mesh.SetVertCoord(8, vec3(1, 1, 1));

    // triangle starting at z
    mesh.SetVertCoord(9,  vec3(0, 0, 1));
    mesh.SetVertCoord(10, vec3(1, 0, 0));
    mesh.SetVertCoord(11, vec3(1, 1, 1));

    mesh.SetTriangleIndices(0, ivec3(0, 1,  2));
    mesh.SetTriangleIndices(1, ivec3(3, 4,  5));
    mesh.SetTriangleIndices(2, ivec3(6, 7,  8));
    mesh.SetTriangleIndices(3, ivec3(9, 10, 11));

    mesh.UpdateNormalsAndTangents();
    mesh.UpdateBoundingBox();
}

/*void MeshFactory::CreateGeosphere(Mesh& mesh,
                                               float        radius,
                                               int          tessellation_iters)
{
    CreateSphere(mesh, 4, 2, radius);
    mesh.CenterAxis();
    for(int i = 0; i < tessellation_iters; i++) {
        mesh_tessellate(mesh, TESSELLATION_TYPE_EDGE_CENTER, true);
        size_t num_vertex = mesh.get_num_vertex();
        for(int j = 0; j < static_cast<int>(num_vertex); j++) {
            mesh.SetVertCoord(j, safe_normalize(mesh.get_vert_coord(j)) * radius);
        }
        mesh.CenterAxis();
    }
}*/

void MeshFactory::CreateDiamondBrilliantCut(Mesh& mesh,
                                                           float        radius,
                                                           float        table_radius,
                                                           float        height,
                                                           float        crown_height_to_total_height_ratio,
                                                           float        upper_girdle_height_to_crown_height_ratio,
                                                           float        lower_girdle_depth_to_pavilion_depth_ratio,
                                                           float        girdle_thick_part_thickness,
                                                           float        girdle_thin_part_thickness)
{
    // table:         8      triangles
    // star:          8      triangles
    // kite:          8 * 2  triangles
    // upper-girdle:  16     triangles
    // girdle:        16 * 2 triangles
    // lower-girdle:  16     triangles
    // pavilion main: 8 * 2  triangles
    // ===============================
    // total (faces):    16 * 7 = 112
    // total (vertices): 112 * 3 = 336

    int       num_vertex = 336;
    int       num_tri    = 112;
    mesh.SetCountTriangles(num_vertex, num_tri);

    float crown_height   = height * crown_height_to_total_height_ratio;
    float pavilion_depth = height - crown_height;

    float upper_girdle_inner_rim_y      = pavilion_depth + crown_height * upper_girdle_height_to_crown_height_ratio;
    float upper_girdle_inner_rim_radius = radius - (radius - table_radius) * upper_girdle_height_to_crown_height_ratio;

    float girdle_thick_part_top_y    = pavilion_depth + girdle_thick_part_thickness * 0.5;
    float girdle_thick_part_bottom_y = pavilion_depth - girdle_thick_part_thickness * 0.5;
    float girdle_thin_part_top_y     = pavilion_depth + girdle_thin_part_thickness * 0.5;
    float girdle_thin_part_bottom_y  = pavilion_depth - girdle_thin_part_thickness * 0.5;

    float lower_girdle_inner_rim_y      = pavilion_depth * (1 - lower_girdle_depth_to_pavilion_depth_ratio);
    float lower_girdle_inner_rim_radius = radius * lower_girdle_depth_to_pavilion_depth_ratio;

    upper_girdle_inner_rim_radius /= cos(M_PI * 0.125);
    lower_girdle_inner_rim_radius /= cos(M_PI * 0.125);

    int vert_index = 0;
    int tri_index  = 0;

    // table: 8 triangles
    for(int i = 0; i < 8; i++) {
        vec3 p1 = vec3(0, height, 0);
        vec3 p2 = euler_to_offset(vec3(
                0,
                0,                                // pitch
                static_cast<float>(i) / 8 * M_2PI)) // yaw
                        * table_radius
                        + vec3(0, height, 0);
        vec3 p3 = euler_to_offset(vec3(
                0,
                0,                                    // pitch
                static_cast<float>(i + 1) / 8 * M_2PI)) // yaw
                        * table_radius
                        + vec3(0, height, 0);
        mesh.SetVertCoord( vert_index + 0, p1);
        mesh.SetVertCoord( vert_index + 1, p2);
        mesh.SetVertCoord( vert_index + 2, p3);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;
    }

    // star: 8 triangles
    for(int i = 0; i < 8; i++) {
        vec3 p1 = euler_to_offset(vec3(
                0,
                0,                                // pitch
                static_cast<float>(i) / 8 * M_2PI)) // yaw
                        * table_radius
                        + vec3(0, height, 0);
        vec3 p2 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * upper_girdle_inner_rim_radius
                        + vec3(0, upper_girdle_inner_rim_y, 0);
        vec3 p3 = euler_to_offset(vec3(
                0,
                0,                                    // pitch
                static_cast<float>(i + 1) / 8 * M_2PI)) // yaw
                        * table_radius
                        + vec3(0, height, 0);
        mesh.SetVertCoord( vert_index + 0, p1);
        mesh.SetVertCoord( vert_index + 1, p2);
        mesh.SetVertCoord( vert_index + 2, p3);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;
    }

    // kite: 8 * 2 triangles
    for(int i = 0; i < 8; i++) {
        // half kite 1
        vec3 p1 = euler_to_offset(vec3(
                0,
                0,                                // pitch
                static_cast<float>(i) / 8 * M_2PI)) // yaw
                        * table_radius
                        + vec3(0, height, 0);
        vec3 p2 = euler_to_offset(vec3(
                0,
                0,                                // pitch
                static_cast<float>(i) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_top_y, 0);
        vec3 p3 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * upper_girdle_inner_rim_radius
                        + vec3(0, upper_girdle_inner_rim_y, 0);
        mesh.SetVertCoord( vert_index + 0, p1);
        mesh.SetVertCoord( vert_index + 1, p2);
        mesh.SetVertCoord( vert_index + 2, p3);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;

        // half kite 2
        vec3 p4 = euler_to_offset(vec3(
                0,
                0,                                    // pitch
                static_cast<float>(i + 1) / 8 * M_2PI)) // yaw
                        * table_radius
                        + vec3(0, height, 0);
        vec3 p5 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * upper_girdle_inner_rim_radius
                        + vec3(0, upper_girdle_inner_rim_y, 0);
        vec3 p6 = euler_to_offset(vec3(
                0,
                0,                                    // pitch
                static_cast<float>(i + 1) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_top_y, 0);
        mesh.SetVertCoord( vert_index + 0, p4);
        mesh.SetVertCoord( vert_index + 1, p5);
        mesh.SetVertCoord( vert_index + 2, p6);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;
    }

    // upper-girdle: 16 triangles
    for(int i = 0; i < 8; i++) {
        // half upper-girdle 1
        vec3 p1 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * upper_girdle_inner_rim_radius
                        + vec3(0, upper_girdle_inner_rim_y, 0);
        vec3 p2 = euler_to_offset(vec3(
                0,
                0,                                // pitch
                static_cast<float>(i) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_top_y, 0);
        vec3 p3 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thin_part_top_y, 0);
        mesh.SetVertCoord( vert_index + 0, p1);
        mesh.SetVertCoord( vert_index + 1, p2);
        mesh.SetVertCoord( vert_index + 2, p3);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;

        // half upper-girdle 2
        vec3 p4 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * upper_girdle_inner_rim_radius
                        + vec3(0, upper_girdle_inner_rim_y, 0);
        vec3 p5 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thin_part_top_y, 0);
        vec3 p6 = euler_to_offset(vec3(
                0,
                0,                                    // pitch
                static_cast<float>(i + 1) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_top_y, 0);
        mesh.SetVertCoord( vert_index + 0, p4);
        mesh.SetVertCoord( vert_index + 1, p5);
        mesh.SetVertCoord( vert_index + 2, p6);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;
    }

    // girdle: 16 * 2 triangles
    for(int i = 0; i < 16; i++) {
        float left_top_y     = (i % 2)       ? girdle_thin_part_top_y    : girdle_thick_part_top_y;
        float left_bottom_y  = (i % 2)       ? girdle_thin_part_bottom_y : girdle_thick_part_bottom_y;
        float right_top_y    = ((i + 1) % 2) ? girdle_thin_part_top_y    : girdle_thick_part_top_y;
        float right_bottom_y = ((i + 1) % 2) ? girdle_thin_part_bottom_y : girdle_thick_part_bottom_y;

        // top half
        vec3 p1 = euler_to_offset(vec3(
                0,
                0,                                     // pitch
                static_cast<float>(i + 1) / 16 * M_2PI)) // yaw
                        * radius
                        + vec3(0, right_top_y, 0);
        vec3 p2 = euler_to_offset(vec3(
                0,
                0,                                 // pitch
                static_cast<float>(i) / 16 * M_2PI)) // yaw
                        * radius
                        + vec3(0, left_top_y, 0);
        vec3 p3 = euler_to_offset(vec3(
                0,
                0,                                 // pitch
                static_cast<float>(i) / 16 * M_2PI)) // yaw
                        * radius
                        + vec3(0, left_bottom_y, 0);
        mesh.SetVertCoord( vert_index + 0, p1);
        mesh.SetVertCoord( vert_index + 1, p2);
        mesh.SetVertCoord( vert_index + 2, p3);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;

        // bottom half
        vec3 p4 = euler_to_offset(vec3(
                0,
                0,                                 // pitch
                static_cast<float>(i) / 16 * M_2PI)) // yaw
                        * radius
                        + vec3(0, left_bottom_y, 0);
        vec3 p5 = euler_to_offset(vec3(
                0,
                0,                                     // pitch
                static_cast<float>(i + 1) / 16 * M_2PI)) // yaw
                        * radius
                        + vec3(0, right_bottom_y, 0);
        vec3 p6 = euler_to_offset(vec3(
                0,
                0,                                     // pitch
                static_cast<float>(i + 1) / 16 * M_2PI)) // yaw
                        * radius
                        + vec3(0, right_top_y, 0);
        mesh.SetVertCoord( vert_index + 0, p4);
        mesh.SetVertCoord( vert_index + 1, p5);
        mesh.SetVertCoord( vert_index + 2, p6);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;
    }

    // lower-girdle: 16 triangles
    for(int i = 0; i < 8; i++) {
        // half lower-girdle 1
        vec3 p1 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * lower_girdle_inner_rim_radius
                        + vec3(0, lower_girdle_inner_rim_y, 0);
        vec3 p2 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thin_part_bottom_y, 0);
        vec3 p3 = euler_to_offset(vec3(
                0,
                0,                                // pitch
                static_cast<float>(i) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_bottom_y, 0);
        mesh.SetVertCoord( vert_index + 0, p1);
        mesh.SetVertCoord( vert_index + 1, p2);
        mesh.SetVertCoord( vert_index + 2, p3);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;

        // half lower-girdle 2
        vec3 p4 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * lower_girdle_inner_rim_radius
                        + vec3(0, lower_girdle_inner_rim_y, 0);
        vec3 p5 = euler_to_offset(vec3(
                0,
                0,                                    // pitch
                static_cast<float>(i + 1) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_bottom_y, 0);
        vec3 p6 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thin_part_bottom_y, 0);
        mesh.SetVertCoord( vert_index + 0, p4);
        mesh.SetVertCoord( vert_index + 1, p5);
        mesh.SetVertCoord( vert_index + 2, p6);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;
    }

    // pavilion main: 8 * 2 triangles
    for(int i = 0; i < 8; i++) {
        // half pavilion main 1
        vec3 p1 = vec3(0);
        vec3 p2 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * lower_girdle_inner_rim_radius
                        + vec3(0, lower_girdle_inner_rim_y, 0);
        vec3 p3 = euler_to_offset(vec3(
                0,
                0,                                // pitch
                static_cast<float>(i) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_bottom_y, 0);
        mesh.SetVertCoord( vert_index + 0, p1);
        mesh.SetVertCoord( vert_index + 1, p2);
        mesh.SetVertCoord( vert_index + 2, p3);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;

        // half pavilion main 2
        vec3 p4 = vec3(0);
        vec3 p5 = euler_to_offset(vec3(
                0,
                0,                                    // pitch
                static_cast<float>(i + 1) / 8 * M_2PI)) // yaw
                        * radius
                        + vec3(0, girdle_thick_part_bottom_y, 0);
        vec3 p6 = euler_to_offset(vec3(
                0,
                0,                                      // pitch
                static_cast<float>(i + 0.5) / 8 * M_2PI)) // yaw
                        * lower_girdle_inner_rim_radius
                        + vec3(0, lower_girdle_inner_rim_y, 0);
        mesh.SetVertCoord( vert_index + 0, p4);
        mesh.SetVertCoord( vert_index + 1, p5);
        mesh.SetVertCoord( vert_index + 2, p6);
        mesh.SetTriangleIndices(tri_index++, ivec3(vert_index + 0, vert_index + 1, vert_index + 2));
        vert_index += 3;
    }

    mesh.UpdateNormalsAndTangents();
    mesh.UpdateBoundingBox();

    ASSERT(vert_index == num_vertex);
    ASSERT(tri_index  == num_tri);
}


NAMESPACE_TOPSIDE_END

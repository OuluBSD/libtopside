#ifndef _Geometry_ModelBuilder_h_
#define _Geometry_ModelBuilder_h_

NAMESPACE_TOPSIDE_BEGIN


#define DEFAULT_SLICES 16
#define DEFAULT_STACKS 16

#define VEC_LEFT    vec3(1.0f, 0.0f, 0.0f)
#define VEC_UP      vec3(0.0f, 1.0f, 0.0f)
#define VEC_FORWARD vec3(0.0f, 0.0f, 1.0f)

enum euler_index_t {
    EULER_INDEX_UNDEF = -1,
    EULER_INDEX_ROLL,
    EULER_INDEX_PITCH,
    EULER_INDEX_YAW
};



class MeshFactory
{
public:
    static void GetBoxCorners(vec3        (&points)[8],
                              const vec3* origin = NULL,
                              const vec3* dim    = NULL);
    static void CreateGrid(Mesh& mesh,
                                   int          cols             = 1,
                                   int          rows             = 1,
                                   float        width            = 1,
                                   float        length           = 1,
                                   float        tex_width_scale  = 1,
                                   float        tex_length_scale = 1);
    static void CreateSphere(Mesh& mesh,
                                     int          slices = DEFAULT_SLICES,
                                     int          stacks = DEFAULT_STACKS,
                                     float        radius = 1);
    static void CreateHemisphere(Mesh& mesh,
                                         int          slices = DEFAULT_SLICES,
                                         int          stacks = DEFAULT_STACKS,
                                         float        radius = 1);
    static void CreateCylinder(Mesh& mesh,
                                       int          slices = DEFAULT_SLICES,
                                       float        radius = 1,
                                       float        height = 1);
    static void CreateCone(Mesh& mesh,
                                   int          slices = DEFAULT_SLICES,
                                   float        radius = 1,
                                   float        height = 1);
    static void CreateTorus(Mesh& mesh,
                                    int          slices       = DEFAULT_SLICES,
                                    int          stacks       = DEFAULT_STACKS,
                                    float        radius_major = 1,
                                    float        radius_minor = 0.5);
    static void CreateBox(Mesh& mesh,
                                  float        width  = 1,
                                  float        height = 1,
                                  float        length = 1);
    static void CreateTetrahedron(Mesh& mesh,
                                          float        width  = 1,
                                          float        height = 1,
                                          float        length = 1);
    static void CreateGeosphere(Mesh& mesh,
                                        float        radius             = 1,
                                        int          tessellation_iters = 3);
    static void CreateDiamondBrilliantCut(Mesh& mesh,
                                                    float        radius                                     = 0.5,
                                                    float        table_radius                               = 0.25,
                                                    float        height                                     = 1,
                                                    float        crown_height_to_total_height_ratio         = 0.25,
                                                    float        upper_girdle_height_to_crown_height_ratio  = 0.75,
                                                    float        lower_girdle_depth_to_pavilion_depth_ratio = 0.5,
                                                    float        girdle_thick_part_thickness                = 0.05,
                                                    float        girdle_thin_part_thickness                 = 0.0125);
    static void CreateViewportQuad(Mesh& mesh)
    {
        return CreateGrid(mesh, 1, 1);
    }
};


class ModelBuilder {
	One<ModelMesh> model;
	
public:
	
	Mesh& AddPlane(const vec3& pos, const vec2& size);
	Mesh& AddBox(const vec3& pos, const vec3& dim, bool centered=false);
	Mesh& AddSphere(const vec3& pos, float radius, int slices=16, int stacks=16);
	Mesh& AddCylinder(const vec3& pos, float radius, float length, int slices=16);
	
	
	operator const ModelMesh&() const {return *model;}
	const ModelMesh& AsModel() const {return *model;}
	
	ModelMesh* Detach() {if (model) return model.Detach(); else return 0;}
	
};


NAMESPACE_TOPSIDE_END

#endif

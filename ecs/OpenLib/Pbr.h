#ifndef _OpenLib_Pbr_h_
#define _OpenLib_Pbr_h_

NAMESPACE_OULU_BEGIN
namespace Pbr {

using NodeIndex_t = uint16; // This type must align with the type used in the Pbr shaders.

constexpr Pbr::NodeIndex_t RootNodeIndex = 0;


struct Vertex : Moveable<Vertex>
{
    vec3	position;
    vec3	normal;
    vec4	tangent;
    vec2	tex_coord0;
    uint16	model_transform_index; // Index into the node transforms

    static const char* vertex_desc[5];
    
};

struct PrimitiveBuilder
{
    Vector<Pbr::Vertex>		vertices;
    Vector<uint32>			indices;

    PrimitiveBuilder& AddSphere(float diameter, uint32 tessellation, Pbr::NodeIndex_t trans_idx = Pbr::RootNodeIndex);
    PrimitiveBuilder& AddCube(float side_length, Pbr::NodeIndex_t trans_idx = Pbr::RootNodeIndex);
    
    PrimitiveBuilder() {}
    PrimitiveBuilder(PrimitiveBuilder&& b) : vertices(std::move(b.vertices)), indices(std::move(b.indices)) {}
    
};


struct Resources {
	
	
	
};


struct Model {
	
	
};

}
NAMESPACE_OULU_END

#endif

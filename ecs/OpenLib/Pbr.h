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


struct Material {
	struct ConstantBufferData {
		vec4 base_clr_factor;
		
	};
	
	
	TrackChanges<ConstantBufferData> parameters;
	
};


struct Node {
	
	
	mat4 GetTransform() const;
	
};

struct Resources {
	
	
	
};


struct Primitive {
	
	
	Material& GetMaterial();
	const Material& GetMaterial() const;
	
};

struct Model {
	
	
    void Clone(const Pbr::Resources& pbr_res, Model& dst) const;
	
	Optional<NodeIndex_t> FindFirstNode(char const* name, Optional<NodeIndex_t> const& parentNodeIndex = {}) const;
	mat4 GetNodeWorldTransform(NodeIndex_t nodeIndex) const;
    NodeIndex_t GetNodeCount() const;// { return (NodeIndex_t)m_nodes.size(); }
    Node& GetNode(NodeIndex_t nodeIndex);// { return m_nodes[nodeIndex]; }
    const Node& GetNode(NodeIndex_t nodeIndex) const;// { return m_nodes[nodeIndex]; }
    
    int GetPrimitiveCount() const;
    Primitive& GetPrimitive(int i);
    
};

}
NAMESPACE_OULU_END

#endif

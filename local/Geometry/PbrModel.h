#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr {


// Node for creating a hierarchy of transforms. These transforms are referenced by vertices in the model's primitives.
struct Node : Moveable<Node>
{
    using Collection = Vector<Node>;
	
	Node();
	
    void Set(const mat4& local_transform, String name, NodeIndex index, NodeIndex parent_node_index)
    {
        this->name = name;
        this->index = index;
        this->parent_node_index = parent_node_index;
        modify_count = 0;
        SetTransform(local_transform);
    }

    // Set the local transform for this node.
    void SetTransform(const mat4& transform)
    {
        StoreMatrix(&local_transform, transform);
        ++modify_count;
    }

    // Get the local transform for this node.
    const mat4& GetTransform() const
    {
        return local_transform;
    }

    String			name;
    NodeIndex		index;
    NodeIndex		parent_node_index;

private:
    friend struct Model;
    
    AtomicInt		modify_count;
    mat4			local_transform;
    
    
};

// A model is a collection of primitives (which reference a material) and transforms referenced by the primitives' vertices.

struct Model
{
	/*using Resources = Resources;
	using Primitive = Primitive;
	using ShaderResources& = typename Gfx::ShaderResources&;
	using GfxContext& = typename Gfx::GfxContext&;
	using NativeBufferRef = typename Gfx::NativeBufferRef;*/
	
    Model(bool create_root_node = true);

    // Add a node to the model.
    Node& AddNode(const mat4& transform, NodeIndex parent_index, String name);

    // Add a primitive to the model.
    //void AddPrimitive(const Primitive& primitive);
    Primitive& AddPrimitive();
    Primitive& AddPrimitive(Primitive* p);

    // Render the model.
    void Render(const Resources& pbr_res, GfxContext& context) const;

    // Remove all primitives.
    void Clear();

    // Create a clone of this model.
    Shared<Model> Clone(Resources const& pbr_res) const;

    NodeIndex GetNodeCount() const { return (NodeIndex)nodes.GetCount(); }
    Node& GetNode(NodeIndex node_idx) { return nodes[node_idx]; }
    const Node& GetNode(NodeIndex node_idx) const { return nodes[node_idx]; }

    // Find the first node which matches a given name.
    Optional<NodeIndex> FindFirstNode(char const* name, Optional<NodeIndex> const& parent_node_index = {}) const;

    // Compute the world transform for a given node.
    mat4 GetNodeWorldTransform(NodeIndex node_idx) const;

    uint32 GetPrimitiveCount() const { return (uint32)primitives.GetCount(); }
    Primitive& GetPrimitive(uint32 index) { return primitives[index]; }
    const Primitive& GetPrimitive(uint32 index) const { return primitives[index]; }

    String								name;

private:
    // Updated the transforms used to render the model. This needs to be called any time a node transform is changed.
    void UpdateTransforms(Resources const& pbr_res, GfxContext& context) const;

private:
    // A model is made up of one or more Primitives. Each Primitive has a unique material.
    // Ideally primitives with the same material should be merged to reduce draw calls.
    Array<Primitive>					primitives;
	
    // A model contains one or more nodes. Each vertex of a primitive references a node to have the
    // node's transform applied.
    Node::Collection					nodes;
	
    // Temporary buffer holds the world transforms, computed from the node's local transforms.
    mutable Vector<mat4>				model_transforms;
    mutable DataBuffer					model_transforms_structured_buffer;
    mutable ShaderResources		model_transforms_resource_view;
	
    mutable uint32						total_modify_count{ 0 };
    
};

}

NAMESPACE_TOPSIDE_END


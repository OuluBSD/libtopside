#pragma once


NAMESPACE_TOPSIDE_BEGIN


namespace Pbr {


// Node for creating a hierarchy of transforms. These transforms are referenced by vertices in the model's primitives.
struct Node
{
    using Collection = Vector<Node>;

    Node(const mat4& local_transform, String name, NodeIndex_t index, NodeIndex_t parent_node_index)
        : name(name), index(index), parent_node_index(parent_node_index)
    {
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
    mat4 GetTransform() const
    {
        return DirectX::XMLoadFloat4x4(&local_transform);
    }

    const String name;
    const NodeIndex_t index;
    const NodeIndex_t parent_node_index;

private:
    friend struct Model;
    AtomicInt modify_count;
    mat4 local_transform;
};

// A model is a collection of primitives (which reference a material) and transforms referenced by the primitives' vertices.
struct Model
{
    Model(bool create_root_node = true);

    // Add a node to the model.
    Node& AddNode(const mat4& transform, NodeIndex_t parent_index, String name);

    // Add a primitive to the model.
    void AddPrimitive(Primitive primitive);

    // Render the model.
    void Render(Pbr::Resources const& pbr_res, ID3D11DeviceContext3* context) const;

    // Remove all primitives.
    void Clear();

    // Create a clone of this model.
    Shared<Model> Clone(Pbr::Resources const& pbr_res) const;

    NodeIndex_t GetNodeCount() const { return (NodeIndex_t)nodes.GetCount(); }
    Node& GetNode(NodeIndex_t nodeIndex) { return nodes[nodeIndex]; }
    const Node& GetNode(NodeIndex_t nodeIndex) const { return nodes[nodeIndex]; }

    // Find the first node which matches a given name.
    std::optional<NodeIndex_t> FindFirstNode(char const* name, std::optional<NodeIndex_t> const& parent_node_index = {}) const;

    // Compute the world transform for a given node.
    mat4 GetNodeWorldTransform(NodeIndex_t nodeIndex) const;

    uint32 GetPrimitiveCount() const { return (uint32)primitives.GetCount(); }
    Primitive& GetPrimitive(uint32 index) { return primitives[index]; }
    const Primitive& GetPrimitive(uint32 index) const { return primitives[index]; }

    String name;

private:
    // Updated the transforms used to render the model. This needs to be called any time a node transform is changed.
    void UpdateTransforms(Pbr::Resources const& pbr_res, ID3D11DeviceContext3* context) const;

private:
    // A model is made up of one or more Primitives. Each Primitive has a unique material.
    // Ideally primitives with the same material should be merged to reduce draw calls.
    Primitive::Collection primitives;

    // A model contains one or more nodes. Each vertex of a primitive references a node to have the
    // node's transform applied.
    Node::Collection nodes;

    // Temporary buffer holds the world transforms, computed from the node's local transforms.
    mutable Vector<mat4> model_transforms;
    mutable ComPtr<ID3D11Buffer> model_transforms_structured_buffer;
    mutable ComPtr<ID3D11ShaderResourceView> model_transforms_resource_view;

    mutable uint32 total_modify_count{ 0 };
};

}

NAMESPACE_TOPSIDE_END


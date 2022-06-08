#if 0
#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


#define TRIANGLE_VERTEX_COUNT 3 // #define so it can be used in lambdas without capture

constexpr Pbr::NodeIndex root_parent_node_index = -1;


namespace Pbr {




Node::Node() {
	modify_count = 0;
}

Model::Model(bool create_root_node /*= true*/)
{
    if (create_root_node)
		CreateRootNode();
}

void Model::CreateRootNode() {
	ASSERT(nodes.IsEmpty());
	AddNode(identity<mat4>(), root_parent_node_index, "root");
}

void Model::Render(Resources const& pbr_res/*, GfxContext& context*/) const
{
	TODO
	/*
    UpdateTransforms(pbr_res, context);

    ShaderResources vs_shader_resources[] = { model_transforms_resource_view.Get() };
    context->VSSetShaderResources(Pbr::ShaderSlots::Transforms, _countof(vs_shader_resources), vs_shader_resources);

    for (const Pbr::Mesh& primitive : primitives)
    {
        if (primitive.GetMaterial()->hidden) continue;

        primitive.GetMaterial()->Bind(context);
        primitive.Render(context);
    }

    // Expect the caller to reset other state, but the geometry shader is cleared specially.
    context->GSSetShader(nullptr, nullptr, 0);
    */
}


Node& Model::AddNode(const mat4& transform, Pbr::NodeIndex parent_index, String name)
{
    auto new_node_idx = (Pbr::NodeIndex)nodes.GetCount();
    if (new_node_idx != root_node_idx && parent_index == root_parent_node_index)
    {
        throw new Exc("Only the first node can be the root");
    }

    nodes.Add().Set(transform, name, new_node_idx, parent_index);
    
    model_transforms_structured_buffer.Clear(); // Structured buffer will need to be recreated.
    return nodes.Top();
}


void Model::Clear()
{
    primitives.Clear();
}


void Model::Copy(const Resources& pbr_res, Model& dst) const
{
    for (const Node& node : nodes) {
        dst.AddNode(node.GetTransform(), node.parent_node_index, node.name);
    }

    for (const Mesh& primitive : primitives) {
        primitive.Copy(pbr_res, dst.AddMesh());
    }
}


Optional<NodeIndex> Model::FindFirstNode(char const* name, Optional<NodeIndex> const& parent_node_index) const
{
    // Children are guaranteed to come after their parents, so start looking after the parent index if one is provided.
    const NodeIndex start_index = parent_node_index ? parent_node_index.value() + 1 : Pbr::root_node_idx;
    for (const Pbr::Node& node : nodes)
    {
        if ((!parent_node_index || node.parent_node_index == parent_node_index.value()) &&
            node.name == name) {
            return node.index;
        }
    }

    return {};
}


mat4 Model::GetNodeWorldTransform(NodeIndex node_idx) const
{
    const Pbr::Node& node = GetNode(node_idx);

    // Compute the transform recursively.
    const mat4 parent_transform =
		node.index == Pbr::root_node_idx ?
			identity<mat4>() :
			GetNodeWorldTransform(node.parent_node_index);
	
    return MultiplyMatrix(node.GetTransform(), parent_transform);
}


/*void Model::AddMesh(const Pbr::Mesh& primitive)
{
    primitives.Add(std::move(primitive));
}*/
Pbr::Mesh& Model::AddMesh()
{
    Pbr::Mesh& prim = primitives.Add();
    //prim.res = &pbr_res;
    //prim.GetMaterial().res = &pbr_res;
    return prim;
}

Mesh& Model::AddMesh(Mesh* p)
{
    Pbr::Mesh& prim = primitives.Add(p);
    //prim.res = &pbr_res;
    //prim.GetMaterial().res = &pbr_res;
    return prim;
}

void Model::UpdateTransforms(Resources const& pbr_res, GfxContext& context) const
{
	TODO
	
    /*const uint32 newtotal_modify_count = std::accumulate(
        nodes.begin(),
        nodes.end(),
        0,
        [](uint32 sum_change_count, const Node& node) { return sum_change_count + node.modify_count; });

    // If none of the node transforms have changed, no need to recompute/update the model transform structured buffer.
    if (newtotal_modify_count != total_modify_count || model_transforms_structured_buffer == nullptr)
    {
        if (model_transforms_structured_buffer == nullptr) // The structured buffer is reset when a Node is added.
        {
            model_transforms.SetCount(nodes.GetCount());

            // Create/recreate the structured buffer and SRV which holds the node transforms.
            // Use Usage=D3D11_USAGE_DYNAMIC and CPUAccessFlags=D3D11_CPU_ACCESS_WRITE with Map/Unmap instead?
            D3D11_BUFFER_DESC desc{};
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            desc.StructureByteStride = sizeof(decltype(model_transforms)::value_type);
            desc.ByteWidth = (uint32)(model_transforms.GetCount() * desc.StructureByteStride);
            Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateBuffer(&desc, nullptr, &model_transforms_structured_buffer));

            D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{};
            srv_desc.view_dimension = D3D11_SRV_DIMENSION_BUFFER;
            srv_desc.Buffer.NumElements = (uint32)model_transforms.GetCount();
            srv_desc.Buffer.ElementWidth = (uint32)model_transforms.GetCount();
            Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateShaderResourceView(model_transforms_structured_buffer.Get(), &srv_desc, &model_transforms_resource_view));
        }

        // Nodes are guaranteed to come after their parents, so each node transform can be multiplied by its parent transform in a single pass.
        ASSERT(nodes.GetCount() == model_transforms.GetCount());
        for (const auto& node : nodes)
        {
            ASSERT(node.parent_node_index == root_parent_node_index || node.parent_node_index < node.Index);
            const mat4 parent_transform = (node.parent_node_index == root_parent_node_index) ? identity<mat4>() : XMLoadFloat4x4(&model_transforms[node.parent_node_index]);
            StoreMatrix(&model_transforms[node.Index], MultiplyMatrix(parent_transform, MatrixTranspose(node.GetTransform())));
        }

        // Update node transform structured buffer.
        context->UpdateSubresource(model_transforms_structured_buffer.Get(), 0, nullptr, this->model_transforms.data(), 0, 0);
        total_modify_count = newtotal_modify_count;
    }*/
}

}

NAMESPACE_TOPSIDE_END


#endif

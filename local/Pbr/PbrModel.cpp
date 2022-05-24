#include "Pbr.h"


NAMESPACE_TOPSIDE_BEGIN


#define TRIANGLE_VERTEX_COUNT 3 // #define so it can be used in lambdas without capture

constexpr Pbr::NodeIndex_t Rootparent_node_index = -1;


namespace Pbr {

Model::Model(bool create_root_node /*= true*/)
{
    if (create_root_node)
    {
        AddNode(identity<mat4>(), Rootparent_node_index, "root");
    }
}

void Model::Render(Pbr::Resources const& pbr_res, ID3D11DeviceContext3* context) const
{
    UpdateTransforms(pbr_res, context);

    ID3D11ShaderResourceView* vsShaderResources[] = { model_transforms_resource_view.Get() };
    context->VSSetShaderResources(Pbr::ShaderSlots::Transforms, _countof(vsShaderResources), vsShaderResources);

    for (const Pbr::Primitive& primitive : primitives)
    {
        if (primitive.GetMaterial()->hidden) continue;

        primitive.GetMaterial()->Bind(context);
        primitive.Render(context);
    }

    // Expect the caller to reset other state, but the geometry shader is cleared specially.
    context->GSSetShader(nullptr, nullptr, 0);
}

Node& Model::AddNode(const mat4& transform, Pbr::NodeIndex_t parent_index, String name)
{
    auto newNodeIndex = (Pbr::NodeIndex_t)nodes.size();
    if (newNodeIndex != RootNodeIndex && parent_index == Rootparent_node_index)
    {
        throw new std::exception("Only the first node can be the root");
    }

    nodes.emplace_back(transform, std::move(name), newNodeIndex, parent_index);
    model_transforms_structured_buffer = nullptr; // Structured buffer will need to be recreated.
    return nodes.back();
}

void Model::Clear()
{
    primitives.clear();
}

Shared<Model> Model::Clone(Pbr::Resources const& pbr_res) const
{
    auto clone = std::make_shared<Model>(false /* create_root_node */);

    for (const Node& node : nodes)
    {
        clone->AddNode(node.GetTransform(), node.parent_node_index, node.Name);
    }

    for (const Primitive& primitive : primitives)
    {
        clone->AddPrimitive(primitive.Clone(pbr_res));
    }

    return clone;
}

std::optional<NodeIndex_t> Model::FindFirstNode(char const* name, std::optional<NodeIndex_t> const& parent_node_index) const
{
    // Children are guaranteed to come after their parents, so start looking after the parent index if one is provided.
    const NodeIndex_t startIndex = parent_node_index ? parent_node_index.value() + 1 : Pbr::RootNodeIndex;
    for (const Pbr::Node& node : nodes)
    {
        if ((!parent_node_index || node.parent_node_index == parent_node_index.value()) &&
            node.Name == name)
        {
            return node.Index;
        }
    }

    return {};
}

mat4 Model::GetNodeWorldTransform(NodeIndex_t nodeIndex) const
{
    const Pbr::Node& node = GetNode(nodeIndex);

    // Compute the transform recursively.
    const mat4 parentTransform = node.Index == Pbr::RootNodeIndex ? identity<mat4>() : GetNodeWorldTransform(node.parent_node_index);
    return MultiplyMatrix(node.GetTransform(), parentTransform);
}

void Model::AddPrimitive(Pbr::Primitive primitive)
{
    primitives.push_back(std::move(primitive));
}

void Model::UpdateTransforms(Pbr::Resources const& pbr_res, ID3D11DeviceContext3* context) const
{
    const uint32 newtotal_modify_count = std::accumulate(
        nodes.begin(),
        nodes.end(),
        0,
        [](uint32 sumChangeCount, const Node& node) { return sumChangeCount + node.modify_count; });

    // If none of the node transforms have changed, no need to recompute/update the model transform structured buffer.
    if (newtotal_modify_count != total_modify_count || model_transforms_structured_buffer == nullptr)
    {
        if (model_transforms_structured_buffer == nullptr) // The structured buffer is reset when a Node is added.
        {
            model_transforms.resize(nodes.size());

            // Create/recreate the structured buffer and SRV which holds the node transforms.
            // Use Usage=D3D11_USAGE_DYNAMIC and CPUAccessFlags=D3D11_CPU_ACCESS_WRITE with Map/Unmap instead?
            D3D11_BUFFER_DESC desc{};
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            desc.StructureByteStride = sizeof(decltype(model_transforms)::value_type);
            desc.ByteWidth = (uint32)(model_transforms.size() * desc.StructureByteStride);
            Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateBuffer(&desc, nullptr, &model_transforms_structured_buffer));

            D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc{};
            srv_desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
            srv_desc.Buffer.NumElements = (uint32)model_transforms.size();
            srv_desc.Buffer.ElementWidth = (uint32)model_transforms.size();
            Internal::ThrowIfFailed(pbr_res.GetDevice()->CreateShaderResourceView(model_transforms_structured_buffer.Get(), &srv_desc, &model_transforms_resource_view));
        }

        // Nodes are guaranteed to come after their parents, so each node transform can be multiplied by its parent transform in a single pass.
        assert(nodes.size() == model_transforms.size());
        for (const auto& node : nodes)
        {
            assert(node.parent_node_index == Rootparent_node_index || node.parent_node_index < node.Index);
            const mat4 parentTransform = (node.parent_node_index == Rootparent_node_index) ? identity<mat4>() : XMLoadFloat4x4(&model_transforms[node.parent_node_index]);
            StoreMatrix(&model_transforms[node.Index], MultiplyMatrix(parentTransform, XMMatrixTranspose(node.GetTransform())));
        }

        // Update node transform structured buffer.
        context->UpdateSubresource(model_transforms_structured_buffer.Get(), 0, nullptr, this->model_transforms.data(), 0, 0);
        total_modify_count = newtotal_modify_count;
    }
}

}

NAMESPACE_TOPSIDE_END


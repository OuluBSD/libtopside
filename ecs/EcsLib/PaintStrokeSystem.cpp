#include "EcsLib.h"


NAMESPACE_OULU_BEGIN


PaintStrokeSystem::PaintStrokeSystem(
    Machine& core,
    Shared<Pbr::Resources> pbr_res) :
    System(core),
    pbr_res(std::move(pbr_res))
{}

void PaintStrokeSystem::Update(double)
{
    for (auto& comp_set : GetMachine().Get<EntityStore>()->GetComponents<PaintStrokeComponent, PbrRenderable>())
    {
        auto[paintStroke, pbr] = comp_set;

        if (paintStroke->stroke_changed)
        {
            Shared<Pbr::Material> strokeMaterial = Pbr::Material::CreateFlat(
                *pbr_res,
                *pbr->Color /* base color */,
                0.95f /* roughness */);

            // Load the primitive into D3D buffers with associated materia.
            Pbr::Primitive strokePrimitive(*pbr_res, paintStroke->GetPrimitiveData(), std::move(strokeMaterial));

            // Add the primitive into the model.
            if (auto& model = pbr->Model)
            {
                model->Clear();
                model->AddPrimitive(std::move(strokePrimitive));
            }

            paintStroke->stroke_changed = false;
        }
    }
}

void PaintStrokeComponent::AddPoint(const mat4& transformation, float width)
{
    const float halfWidth = width / 2.0f;

    PaintStrokeComponent::Square square;

    square.tl = transform(vec3{ -halfWidth, 0.0f, +halfWidth }, transformation);
    square.tr = transform(vec3{ +halfWidth, 0.0f, +halfWidth }, transformation);
    square.bt = transform(vec3{ +halfWidth, 0.0f, -halfWidth }, transformation);
    square.bl = transform(vec3{ -halfWidth, 0.0f, -halfWidth }, transformation);

    squares.Add(std::move(square));

    stroke_changed = true;
}

Pbr::PrimitiveBuilder PaintStrokeComponent::GetPrimitiveData()
{
    Pbr::PrimitiveBuilder primitiveBuilder;

    if (squares.GetCount() > 0)
    {
        // Vertices
        Vector<Pbr::Vertex> vertices;
        vertices.reserve(squares.GetCount() * 4);
        const size_t expectedVerticesCapacity = vertices.capacity();

        constexpr XMFLOAT3 Normal{ 0.0f, 0.0f, 1.0f };
        constexpr XMFLOAT4 Tangent{ 1.0f, 0.0f, 0.0f, 1.0f };
        constexpr XMFLOAT2 TexCoord{ 0.0f, 0.0f };

        for (auto& square : squares)
        {
            vertices.Add({ AsRef<XMFLOAT3>(square.tl), Normal, Tangent, TexCoord, Pbr::RootNodeIndex });
            vertices.Add({ AsRef<XMFLOAT3>(square.tr), Normal, Tangent, TexCoord, Pbr::RootNodeIndex });
            vertices.Add({ AsRef<XMFLOAT3>(square.br), Normal, Tangent, TexCoord, Pbr::RootNodeIndex });
            vertices.Add({ AsRef<XMFLOAT3>(square.bl), Normal, Tangent, TexCoord, Pbr::RootNodeIndex });
        }

        constexpr size_t numIndicesPerFace = 6u;
        constexpr size_t numBackFrontFaces = 2u;
        const size_t numSideFaces = 4u * (squares.GetCount() - 1);

        // Indices
        Vector<uint32> indices;
        indices.reserve(numIndicesPerFace * (numBackFrontFaces + numSideFaces));

        const size_t expectedIndicesCapacity = indices.capacity();

        auto addSquare = [&indices](uint32 topLeft, uint32 topRight, uint32 bottomRight, uint32 bottomLeft)
        {
            indices.Add(topLeft); indices.Add(topRight); indices.Add(bottomRight);
            indices.Add(topLeft); indices.Add(bottomRight); indices.Add(bottomLeft);
        };

        // Back face
        addSquare(1, 0, 3, 2);

        // Front face
        const uint32 frontStart = static_cast<uint32>(4 * (squares.GetCount() - 1));
        addSquare(frontStart, frontStart + 1, frontStart + 2, frontStart + 3);

        // Side faces
        const uint32 sidesCount = static_cast<uint32>(squares.GetCount() - 1);
        for (uint32 sideIndex = 0; sideIndex < sidesCount; sideIndex++)
        {
            const uint32 start = sideIndex * 4u;

            // +0 = back / top / left
            // +1 = back / top / right
            // +2 = back / bottom / right
            // +3 = back / bottom / left
            // +4 = front / top / left
            // +5 = front / top / right
            // +6 = front / bottom / right
            // +7 = front / bottom / left

            addSquare(start + 0, start + 1, start + 5, start + 4); // Top
            addSquare(start + 5, start + 1, start + 2, start + 6); // Right
            addSquare(start + 0, start + 4, start + 7, start + 3); // Left
            addSquare(start + 7, start + 6, start + 2, start + 3); // Bottom
        }

        // Make sure we only allocate memory once
        fail_fast_if(expectedVerticesCapacity != vertices.GetCount());
        fail_fast_if(expectedIndicesCapacity != indices.GetCount());

        primitiveBuilder.Vertices = std::move(vertices);
        primitiveBuilder.Indices = std::move(indices);
    }

    return primitiveBuilder;
}


NAMESPACE_OULU_END

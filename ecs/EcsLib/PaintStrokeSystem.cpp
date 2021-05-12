#include "EcsLib.h"


NAMESPACE_OULU_BEGIN



void PaintStrokeSystem::Update(double)
{
	TODO
	#if 0
    for (auto& comp_set : GetMachine().Get<EntityStore>()->GetComponents<PaintStrokeComponent, PbrRenderable>())
    {
        auto[paint_stroke, pbr] = comp_set;

        if (paint_stroke->stroke_changed)
        {
            Shared<Pbr::Material> stroke_material = Pbr::Material::CreateFlat(
                *pbr_res,
                *pbr->Color /* base color */,
                0.95f /* roughness */);

            // Load the primitive into D3D buffers with associated materia.
            Pbr::Primitive stroke_primitive(*pbr_res, paint_stroke->GetPrimitiveData(), std::move(stroke_material));

            // Add the primitive into the model.
            if (auto& model = pbr->Model)
            {
                model->Clear();
                model->AddPrimitive(stroke_primitive);
            }

            paint_stroke->stroke_changed = false;
        }
    }
    #endif
}

void PaintStrokeComponent::AddPoint(const mat4& transformation, float width)
{
    const float half_width = width / 2.0f;

    Square square;

    square.tl = transform(vec3{ -half_width, 0.0f, +half_width }, transformation);
    square.tr = transform(vec3{ +half_width, 0.0f, +half_width }, transformation);
    square.br = transform(vec3{ +half_width, 0.0f, -half_width }, transformation);
    square.bl = transform(vec3{ -half_width, 0.0f, -half_width }, transformation);

    squares.Add(square);

    stroke_changed = true;
}

Pbr::PrimitiveBuilder PaintStrokeComponent::GetPrimitiveData()
{
    Pbr::PrimitiveBuilder primitive_builder;

    if (squares.GetCount() > 0)
    {
		Vector<Pbr::Vertex>& vertices	= primitive_builder.vertices;
        Vector<uint32>& indices			= primitive_builder.indices;
		
        // Vertices
        const size_t expected_vertices_capacity = squares.GetCount() * 4;
        vertices.Reserve(expected_vertices_capacity);
        
        vec3 normal { 0.0f, 0.0f, 1.0f };
        vec4 tangent{ 1.0f, 0.0f, 0.0f, 1.0f };
        vec2 tex_coord{ 0.0f, 0.0f };

        for (auto& square : squares)
        {
            vertices.Add(Pbr::Vertex{ {}, square.tl, normal, tangent, tex_coord, Pbr::RootNodeIndex });
            vertices.Add(Pbr::Vertex{ {}, square.tr, normal, tangent, tex_coord, Pbr::RootNodeIndex });
            vertices.Add(Pbr::Vertex{ {}, square.br, normal, tangent, tex_coord, Pbr::RootNodeIndex });
            vertices.Add(Pbr::Vertex{ {}, square.bl, normal, tangent, tex_coord, Pbr::RootNodeIndex });
        }

        const size_t num_indices_per_face = 6u;
        const size_t num_back_front_faces = 2u;
        const size_t num_side_faces = 4u * (squares.GetCount() - 1);

        // Indices
        const size_t expected_indices_capacity = num_indices_per_face * (num_back_front_faces + num_side_faces);
		indices.Reserve(expected_indices_capacity);
        
        auto add_square = [&indices](uint32 top_left, uint32 top_right, uint32 bottom_right, uint32 bottom_left)
        {
            indices.Add(top_left); indices.Add(top_right); indices.Add(bottom_right);
            indices.Add(top_left); indices.Add(bottom_right); indices.Add(bottom_left);
        };

        // Back face
        add_square(1, 0, 3, 2);

        // Front face
        const uint32 front_start = static_cast<uint32>(4 * (squares.GetCount() - 1));
        add_square(front_start, front_start + 1, front_start + 2, front_start + 3);

        // Side faces
        const uint32 sides_count = static_cast<uint32>(squares.GetCount() - 1);
        for (uint32 side_index = 0; side_index < sides_count; side_index++)
        {
            const uint32 start = side_index * 4u;

            // +0 = back / top / left
            // +1 = back / top / right
            // +2 = back / bottom / right
            // +3 = back / bottom / left
            // +4 = front / top / left
            // +5 = front / top / right
            // +6 = front / bottom / right
            // +7 = front / bottom / left

            add_square(start + 0, start + 1, start + 5, start + 4); // Top
            add_square(start + 5, start + 1, start + 2, start + 6); // Right
            add_square(start + 0, start + 4, start + 7, start + 3); // Left
            add_square(start + 7, start + 6, start + 2, start + 3); // Bottom
        }

        // Make sure we only allocate memory once
        ASSERT(expected_vertices_capacity == vertices.GetCount());
        ASSERT(expected_indices_capacity == indices.GetCount());
    }

    return primitive_builder;
}


NAMESPACE_OULU_END

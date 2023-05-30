#include "EcsLocal.h"


NAMESPACE_ECS_BEGIN





void PaintStrokeComponent::Etherize(Ether& e) {
	e % squares
	  % stroke_changed;
}

void PaintStrokeComponent::Initialize(){
	Engine& e = GetEngine();
	Ref<PaintStrokeSystemBase> sys = e.Get<PaintStrokeSystemBase>();
	sys->Attach(this);
}

void PaintStrokeComponent::Uninitialize() {
	Engine& e = GetEngine();
	Ref<PaintStrokeSystemBase> sys = e.Get<PaintStrokeSystemBase>();
	sys->Detach(this);
}




void PaintStrokeSystemBase::Attach(PaintStrokeComponent* comp) {
	comps.Add(comp);
}

void PaintStrokeSystemBase::Detach(PaintStrokeComponent* comp) {
	VectorRemoveKey(comps, comp);
}

bool PaintStrokeSystemBase::Initialize() {
	
	return true;
}

void PaintStrokeSystemBase::Update(double) {
	for (PaintStrokeComponent* paint_stroke : comps) {
		if (paint_stroke->stroke_changed) {
			ModelComponentRef c = paint_stroke->GetEntity()->Get<ModelComponent>();
			Ref<Model> m = c->GetModel();
			
			if (m) {
				auto& squares = paint_stroke->squares;
				
				// Add the primitive into the model.
				Mesh& stroke_mesh = m->GetMeshCount() == 0 ? m->AddMesh() : m->GetMesh(0);
				vec3 normal { 0.0f, 0.0f, 1.0f };
				vec3 tangent{ 1.0f, 0.0f, 0.0f };
				vec2 tex_coord{ 0.0f, 0.0f };
				
				int square_begin = stroke_mesh.vertices.GetCount() / 4;
				int vert_count = squares.GetCount() * 4;
				stroke_mesh.vertices.SetCount(vert_count);
				for(int i = square_begin; i < squares.GetCount(); i++) {
					const Square& sq = squares[i];
					int vtx_begin = i * 4;
					
					Vertex& tl = stroke_mesh.vertices[vtx_begin + 0];
					Vertex& tr = stroke_mesh.vertices[vtx_begin + 1];
					Vertex& br = stroke_mesh.vertices[vtx_begin + 2];
					Vertex& bl = stroke_mesh.vertices[vtx_begin + 3];
					tl.Set(sq.tl, normal, tangent, tex_coord);
					tr.Set(sq.tr, normal, tangent, tex_coord);
					br.Set(sq.br, normal, tangent, tex_coord);
					bl.Set(sq.bl, normal, tangent, tex_coord);
				}
				
				auto& indices = stroke_mesh.indices;
				auto AddSquare = [&indices](uint32 top_left, uint32 top_right, uint32 bottom_right, uint32 bottom_left) {
					indices.Add(top_left); indices.Add(top_right); indices.Add(bottom_right);
					indices.Add(top_left); indices.Add(bottom_right); indices.Add(bottom_left);
				};
				
				int num_indices_per_face = 6;
				int num_back_front_faces = 2;
				int num_side_faces = 4 * (squares.GetCount() - 1);
				int expected_indices_capacity = num_indices_per_face * (num_back_front_faces + num_side_faces);
				indices.Reserve(expected_indices_capacity);
				
				// Back face
				AddSquare(1, 0, 3, 2);
				
				// Front face
				int front_start = 4 * (squares.GetCount() - 1);
				AddSquare(front_start, front_start + 1, front_start + 2, front_start + 3);
				
				// Side faces
				int sides_count = squares.GetCount() - 1;
				
				for (int i = square_begin; i < sides_count; i++) {
					int start = i * 4;
					// +0 = back / top / left
					// +1 = back / top / right
					// +2 = back / bottom / right
					// +3 = back / bottom / left
					// +4 = front / top / left
					// +5 = front / top / right
					// +6 = front / bottom / right
					// +7 = front / bottom / left
					AddSquare(start + 0, start + 1, start + 5, start + 4); // Top
					AddSquare(start + 5, start + 1, start + 2, start + 6); // Right
					AddSquare(start + 0, start + 4, start + 7, start + 3); // Left
					AddSquare(start + 7, start + 6, start + 2, start + 3); // Bottom
				}
				
				Material& stroke_material = m->AddMaterial();
				stroke_mesh.SetMaterial(stroke_material);
				
				stroke_material.SetFlat(
					c->color, // base color
					0.95f // roughness
				);
				
				c->SetModelChanged();
			}
			
			paint_stroke->stroke_changed = false;
		}
	}
}










void PaintStrokeComponent::AddPoint(const mat4& transformation, float width) {
	const float half_width = width / 2.0f;
	Square square;
	square.tl = VectorTransform(vec3{ -half_width, 0.0f, +half_width }, transformation);
	square.tr = VectorTransform(vec3{ +half_width, 0.0f, +half_width }, transformation);
	square.br = VectorTransform(vec3{ +half_width, 0.0f, -half_width }, transformation);
	square.bl = VectorTransform(vec3{ -half_width, 0.0f, -half_width }, transformation);
	squares.Add(square);
	stroke_changed = true;
}

#if 0
Pbr::PrimitiveBuilder PaintStrokeComponent::GetPrimitiveData() {
	Pbr::PrimitiveBuilder primitive_builder;
	
	if (squares.GetCount() > 0) {
		Vector<Pbr::Vertex>& vertices	= primitive_builder.vertices;
		Vector<uint32>& indices			= primitive_builder.indices;
		// Vertices
		vec3 normal { 0.0f, 0.0f, 1.0f };
		vec4 tangent{ 1.0f, 0.0f, 0.0f, 1.0f };
		vec2 tex_coord{ 0.0f, 0.0f };
		
		#if 0
		const size_t expected_vertices_capacity = squares.GetCount() * 4;
		vertices.Reserve(expected_vertices_capacity);
		for (auto& square : squares) {
			vertices.Add(Pbr::Vertex{ square.tl, normal, tangent, tex_coord, Pbr::RootNodeIndex });
			vertices.Add(Pbr::Vertex{ square.tr, normal, tangent, tex_coord, Pbr::RootNodeIndex });
			vertices.Add(Pbr::Vertex{ square.br, normal, tangent, tex_coord, Pbr::RootNodeIndex });
			vertices.Add(Pbr::Vertex{ square.bl, normal, tangent, tex_coord, Pbr::RootNodeIndex });
		}
		
		const size_t num_indices_per_face = 6u;
		const size_t num_back_front_faces = 2u;
		const size_t num_side_faces = 4u * (squares.GetCount() - 1);
		
		// Indices
		const size_t expected_indices_capacity = num_indices_per_face * (num_back_front_faces + num_side_faces);
		indices.Reserve(expected_indices_capacity);
		auto add_square = [&indices](uint32 top_left, uint32 top_right, uint32 bottom_right, uint32 bottom_left) {
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
		
		for (uint32 side_index = 0; side_index < sides_count; side_index++) {
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
		
		#else
		const size_t expected_vertices_capacity = squares.GetCount() * 2;
		vertices.Reserve(expected_vertices_capacity);
		for (auto& square : squares) {
			vertices.Add(Pbr::Vertex{ square.tl, normal, tangent, tex_coord, Pbr::RootNodeIndex });
			vertices.Add(Pbr::Vertex{ square.br, normal, tangent, tex_coord, Pbr::RootNodeIndex });
		}
		
		const size_t num_indices_per_face = 6u;
		const size_t num_back_front_faces = 2u;
		const size_t num_side_faces = 4u * (squares.GetCount() - 1);
		// Indices
		const size_t expected_indices_capacity = num_indices_per_face * (num_back_front_faces + num_side_faces);
		indices.Reserve(expected_indices_capacity);
		auto add_square = [&indices](uint32 top_left, uint32 top_right, uint32 bottom_right, uint32 bottom_left) {
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
		
		for (uint32 side_index = 0; side_index < sides_count; side_index++) {
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
		
		
		#endif
		
	}
	
	return primitive_builder;
}

#endif

NAMESPACE_ECS_END


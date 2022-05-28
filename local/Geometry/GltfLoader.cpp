#include "Geometry.h"
#include <ports/tiny_gltf/tiny_gltf.h>


NAMESPACE_TOPSIDE_BEGIN


// Maps a glTF material to a PrimitiveBuilder. This optimization combines all primitives which use
// the same material into a single primitive for reduced draw calls. Each primitive's vertex specifies
// which node it corresponds to any appropriate node transformation be happen in the shader.
using PrimitiveMap = ArrayMap<int, Pbr::Primitive>;


// Create a DirectX texture view from a tinygltf Image.
void LoadImage(Pbr::Texture& tex, const tinygltf::Image& image, bool sRGB)
{
    // First convert the image to RGBA if it isn't already.
    Vector<byte> tmp_buffer;
    const byte* rgba_buf = GltfHelper::ReadImageAsRGBA(image, &tmp_buffer);
    if (rgba_buf != nullptr) {
	    int channels = sRGB ? 4 : 3;
	    tex.Set(rgba_buf, image.width * image.height * 4, image.width, image.height, channels);
    }
}

#if 0
// Create a DirectX sampler state from a tinygltf Sampler.
SamplerState& CreateSampler(NativeDeviceRef device, const tinygltf::Model& gltf_model, const tinygltf::Sampler& sampler)
{
	TODO
	
    /*D3D11_SAMPLER_DESC sampler_desc{};
    // Not supported: Mipmap filters (NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR)
    sampler_desc.Filter =
        (sampler.mag_filter == TINYGLTF_TEXTURE_FILTER_NEAREST && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_NEAREST) ? D3D11_FILTER_MIN_MAG_MIP_POINT :
        (sampler.mag_filter == TINYGLTF_TEXTURE_FILTER_NEAREST && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_LINEAR) ? D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR :
        (sampler.mag_filter == TINYGLTF_TEXTURE_FILTER_LINEAR  && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_NEAREST) ? D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR :
        (sampler.mag_filter == TINYGLTF_TEXTURE_FILTER_LINEAR  && sampler.minFilter == TINYGLTF_TEXTURE_FILTER_LINEAR) ? D3D11_FILTER_MIN_MAG_MIP_LINEAR : D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampler_desc.AddressU =
        sampler.wrap_s == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ? D3D11_TEXTURE_ADDRESS_CLAMP :
        sampler.wrap_s == TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV =
        sampler.wrap_t == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE ? D3D11_TEXTURE_ADDRESS_CLAMP :
        sampler.wrap_t == TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT ? D3D11_TEXTURE_ADDRESS_MIRROR : D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.addr_w = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.max_anistropy = 1;
    sampler_desc.comparison_func = D3D11_COMPARISON_ALWAYS;
    sampler_desc.min_lod = 0;
    sampler_desc.max_lod = D3D11_FLOAT32_MAX;

    SamplerState& sampler_state;
    Pbr::Internal::ThrowIfFailed(device->CreateSamplerState(&sampler_desc, &sampler_state));
    return sampler_state;*/
}
#endif

// Load a glTF node from the tinygltf object model. This will process the node's mesh (if specified) and then recursively load the child nodes too.
void LoadNode(Pbr::NodeIndex parent_node_index, const tinygltf::Model& gltf_model, int nodeId, PrimitiveMap& prim_builder_map, Pbr::Model& model)
{
    const tinygltf::Node& gltf_node = gltf_model.nodes.at(nodeId);

    // Read the local transform for this node and add it into the Pbr Model.
    const mat4 node_local_transform = GltfHelper::ReadNodeLocalTransform(gltf_node);
    const Pbr::NodeIndex transform_idx = model.AddNode(node_local_transform, parent_node_index, gltf_node.name.c_str()).index;

    if (gltf_node.mesh != -1) // Load the node's optional mesh when specified.
    {
        // A glTF mesh is composed of primitives.
        const tinygltf::Mesh& gltf_mesh = gltf_model.meshes.at(gltf_node.mesh);
        for (const tinygltf::Primitive& gltf_primitive : gltf_mesh.primitives)
        {
            // Read the primitive data from the glTF buffers.
            const GltfHelper::Primitive primitive = GltfHelper::ReadPrimitive(gltf_model, gltf_primitive);

            // Insert or append the primitive into the PBR primitive builder. Primitives which use the same
            // material are appended to reduce the number of draw calls.
            Pbr::Primitive& prim_builder = prim_builder_map.GetAdd(gltf_primitive.material);

            // Use the starting offset for vertices and indices since multiple glTF primitives can
            // be put into the same primitive builder.
            const uint32 start_vertex = (uint32)prim_builder.vertices.GetCount();
            const uint32 start_index = (uint32)prim_builder.indices.GetCount();

            // Convert the GltfHelper vertices into the PBR vertex format.
            prim_builder.vertices.SetCount(start_vertex + primitive.vertices.GetCount());
            for (size_t i = 0; i < primitive.vertices.GetCount(); i++)
            {
                const GltfHelper::Vertex& vertex = primitive.vertices[i];
                Pbr::Vertex pbr_vtx;
                pbr_vtx.position = vertex.position;
                pbr_vtx.normal = vertex.normal;
                pbr_vtx.tangent = vertex.tangent;
                pbr_vtx.tex_coord = vertex.tex_coord;
                pbr_vtx.mdl_transform_idx = transform_idx;

                prim_builder.vertices[i + start_vertex] = pbr_vtx;
            }

            // Insert indicies with reverse winding order.
            prim_builder.indices.SetCount(start_index + primitive.indices.GetCount());
            for (size_t i = 0; i < primitive.indices.GetCount(); i += 3)
            {
                prim_builder.indices[start_index + i + 0] = start_vertex + primitive.indices[i + 0];
                prim_builder.indices[start_index + i + 1] = start_vertex + primitive.indices[i + 2];
                prim_builder.indices[start_index + i + 2] = start_vertex + primitive.indices[i + 1];
            }
        }
    }

    // Recursively load all children.
    for (const int child_node_id : gltf_node.children) {
        LoadNode(transform_idx, gltf_model, child_node_id, prim_builder_map, model);
    }
}


namespace Gltf
{


bool FromGltfObject(
	Pbr::Model& model,
    Pbr::Resources& pbr_res,
    const tinygltf::Model& gltf_model,
    const mat4& root_gltf_transform)
{
	/*using namespace Pbr;
	using ShaderResources& = typename Gfx::ShaderResources;
	using SamplerState& = typename Gfx::SamplerState;
	using Material = Pbr::Material;
	using Primitive = Pbr::Primitive;*/
	
	
    // Read and transform mesh/node data. Primitives with the same material are merged to reduce draw calls.
    PrimitiveMap prim_builder_map;
    {
        const int def_scene_id = (gltf_model.defaultScene == -1) ? 0 : gltf_model.defaultScene;
        const tinygltf::Scene& def_scene = gltf_model.scenes.at(def_scene_id);

        // The Pbr::Model will already have a root node, which is often used to dynamically move the object. This node
        // is the root of the glTF model and can be used to create a persistent transform. This is useful if the model
        // is not positioned or scaled correctly.
        const Pbr::NodeIndex gltf_root_node_idx = model.AddNode(root_gltf_transform, Pbr::root_node_idx, "gltf_root").index;

        // Process the root scene nodes. The children will be processed recursively.
        for (const int root_node_id : def_scene.nodes) {
            LoadNode(gltf_root_node_idx, gltf_model, root_node_id, prim_builder_map, model);
        }
    }
	
    // Load the materials referenced by the primitives
    VectorMap<int, Pbr::Material*> material_map;
    {
        // Create D3D cache for reuse of texture views and samplers when possible.
        using ImageKey = Tuple<const tinygltf::Image*, bool>; // Item1 is a pointer to the image, Item2 is sRGB.
        VectorMap<ImageKey, Pbr::Texture*> image_map;
        
        
        // prim_builder_map is grouped by material. Loop through the referenced materials and load their resources. This will only
        // load materials which are used by the active scene.
        for(int i = 0; i < prim_builder_map.GetCount(); i++) {
			const int material_idx = prim_builder_map.GetKey(i);
			Pbr::Primitive& prim = prim_builder_map[i];
			
            Pbr::Material*& pbr_material = material_map.GetAdd(material_idx, (Pbr::Material*)0);
            if (pbr_material)
                continue;
            
            pbr_material = &pbr_res.AddMaterial();
            
            if (material_idx == -1) // No material was referenced. Make up a material for it.
            {
                // Default material is a grey material, 50% roughness, non-metallic.
                pbr_material->SetFlat(Colors::Gray, 0.5f);
            }
            else
            {
                const tinygltf::Material& gltf_material = gltf_model.materials.at(material_idx);
                const GltfHelper::Material material = GltfHelper::ReadMaterial(gltf_model, gltf_material);
                
                // Read a tinygltf texture and sampler into the Pbr Material.
                auto load_tex = [&](Pbr::ShaderSlots::PSMaterial slot, const GltfHelper::Material::Texture& texture, bool sRGB, const vec4& def_rgba)
                {
                    // Find or load the image referenced by the texture.
                    const ImageKey image_key = MakeTuple(texture.image, sRGB);
                    int tex_i = image_map.Find(image_key);
                    if (tex_i < 0) // If not cached, load the image and store it in the texture cache.
                    {
                        tex_i = image_map.GetCount();
                        Pbr::Texture*& tex_view = image_map.Add(image_key);
                        
                        // TODO: Generate mipmaps if sampler's minification filter (minFilter) uses mipmapping.
                        // TODO: If texture is not power-of-two and (sampler has wrapping=repeat/mirrored_repeat OR minFilter uses mipmapping), resize to power-of-two.
                        if (texture.image)
                            LoadImage(*tex_view, *texture.image, sRGB);
                        else
                            tex_view->SetSolidColorTexture(def_rgba);
                    }
					Pbr::Texture*& tex_view = image_map[tex_i];
					
                    pbr_material->SetTexture(slot, *tex_view);
                };

                pbr_material->name = gltf_material.name.c_str();

                pbr_material->parameters.Set([&](Pbr::Material::ConstantBufferData& data) {
                    data.base_clr_factor = material.base_color_factor;
                    data.metallic_factor = material.metallic_factor;
                    data.roughness_factor = material.roughness_factor;
                    data.emissive_factor = material.emissive_factor;
                    data.occlusion_strength = material.occlusion_strength;
                    data.normal_scale = material.normal_scale;
                });

                load_tex(Pbr::ShaderSlots::BaseColor, material.base_color_texture,	false /* sRGB */, vec4{ 1, 1, 1, 1 });
                load_tex(Pbr::ShaderSlots::MetallicRoughness, material.metallic_roughness_texture, false /* sRGB */, vec4{ 1, 1, 1, 1 });
                load_tex(Pbr::ShaderSlots::Emissive, material.emissive_texture, true /* sRGB */, vec4{ 1, 1, 1, 1 });
                load_tex(Pbr::ShaderSlots::Normal, material.normal_texture, false /* sRGB */, vec4{ 0.5f, 0.5f, 1, 1 });
                load_tex(Pbr::ShaderSlots::Occlusion, material.occlusion_texture, false /* sRGB */, vec4{ 1, 1, 1, 1 });

                // Not supported: alphaMode ("OPAQUE", "MASK", "BLEND")
                // Not supported: alphaCutoff (default: 0.5)
                // Not supported: doubleSided
            }
        }
    }
	
    // Convert the primitive builders into primitives with their respective material and add it into the Pbr Model.
    while (prim_builder_map.GetCount()) {
		int a = prim_builder_map.GetKey(0);
        Pbr::Primitive* prim = prim_builder_map.Detach(0);
        Pbr::Material* material = material_map[a];
        prim->SetMaterial(material);
        model.AddPrimitive(prim);
        //prim->Set(pbr_res, prim_builder, *material);
    }
    
    return true;
}


bool FromGltfBinary(
	Pbr::Model& model,
    Pbr::Resources& pbr_res,
    const char* buffer,
    uint32 buffer_bytes,
    const mat4& root_transform)
{
    // Parse the GLB buffer data into a tinygltf model object.
    tinygltf::Model gltf_model;
    std::string error_msg, warn_msg;
    tinygltf::TinyGLTF loader;
    if (!loader.LoadBinaryFromMemory(&gltf_model, &error_msg, &warn_msg, (const unsigned char*)buffer, buffer_bytes, "."))
    {
        LOG("FromGltfBinary: error: failed to load gltf model (" +
			IntStr(buffer_bytes) +
			" bytes). Error: " +
			String(error_msg.c_str()));
		ASSERT(0);
        return false;
    }

    return FromGltfObject(model, pbr_res, gltf_model, root_transform);
}

}

NAMESPACE_TOPSIDE_END


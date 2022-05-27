#include "IHolograph.h"


NAMESPACE_PARALLEL_BEGIN


#define TRIANGLE_VERTEX_COUNT 3 // #define so it can be used in lambdas without capture


// The glTF 2 specification recommends using the MikkTSpace algorithm to generate
// tangents when none are available. This function takes a GltfHelper Primitive which has
// no tangents and uses the MikkTSpace algorithm to generate the tangents. This can
// be computationally expensive.
void ComputeTriangleTangents(GltfHelper::Primitive& primitive) {
	
	// Set up the callbacks so that MikkTSpace can read the Primitive data.
	SMikkTSpaceInterface mikk_iface {};
	
	mikk_iface.m_getNumFaces = [](const SMikkTSpaceContext* ctx) {
		auto primitive = static_cast<const GltfHelper::Primitive*>(ctx->m_pUserData);
		ASSERT((primitive->indices.GetCount() % TRIANGLE_VERTEX_COUNT) == 0); // Only triangles are supported.
		return (int)(primitive->indices.GetCount() / TRIANGLE_VERTEX_COUNT);
	};
	mikk_iface.m_getNumVerticesOfFace = [](const SMikkTSpaceContext* ctx, int i_face) {
		return TRIANGLE_VERTEX_COUNT;
	};
	mikk_iface.m_getPosition = [](const SMikkTSpaceContext* ctx, float pos_out[], const int i_face, const int i_vert) {
		auto primitive = static_cast<const GltfHelper::Primitive*>(ctx->m_pUserData);
		const auto vtx_idx = primitive->indices[(i_face * TRIANGLE_VERTEX_COUNT) + i_vert];
		memcpy(pos_out, &primitive->vertices[vtx_idx].position, sizeof(float) * 3);
	};
	mikk_iface.m_getNormal = [](const SMikkTSpaceContext* ctx, float norm_out[], const int i_face, const int i_vert) {
		auto primitive = static_cast<const GltfHelper::Primitive*>(ctx->m_pUserData);
		const auto vtx_idx = primitive->indices[(i_face * TRIANGLE_VERTEX_COUNT) + i_vert];
		memcpy(norm_out, &primitive->vertices[vtx_idx].normal, sizeof(float) * 3);
	};
	mikk_iface.m_getTexCoord = [](const SMikkTSpaceContext* ctx, float texc_out[], const int i_face, const int i_vert) {
		auto primitive = static_cast<const GltfHelper::Primitive*>(ctx->m_pUserData);
		const auto vtx_idx = primitive->indices[(i_face * TRIANGLE_VERTEX_COUNT) + i_vert];
		memcpy(texc_out, &primitive->vertices[vtx_idx].tex_coord, sizeof(float) * 2);
	};
	mikk_iface.m_setTSpaceBasic = [](const SMikkTSpaceContext* ctx, const float tangent_out[], const float f_sign, const int i_face, const int i_vert) {
		auto primitive = static_cast<GltfHelper::Primitive*>(ctx->m_pUserData);
		const auto vtx_idx = primitive->indices[(i_face * TRIANGLE_VERTEX_COUNT) + i_vert];
		primitive->vertices[vtx_idx].tangent[0] = tangent_out[0];
		primitive->vertices[vtx_idx].tangent[1] = tangent_out[1];
		primitive->vertices[vtx_idx].tangent[2] = tangent_out[2];
		primitive->vertices[vtx_idx].tangent[3] = f_sign;
	};
	
	// Run the MikkTSpace algorithm.
	SMikkTSpaceContext mikk_ctx {};
	mikk_ctx.m_pUserData = &primitive;
	mikk_ctx.m_pInterface = &mikk_iface;
	if (genTangSpaceDefault(&mikk_ctx) == 0) {
		throw Exc("Failed to generate tangents");
	}
}

// Generates normals for the trianges in the GltfHelper Primitive object.
void ComputeTriangleNormals(GltfHelper::Primitive& primitive) {
	ASSERT((primitive.indices.GetCount() % TRIANGLE_VERTEX_COUNT) == 0); // Only triangles are supported.
	
	// Loop through each triangle
	for (uint32 i = 0; i < primitive.indices.GetCount(); i += TRIANGLE_VERTEX_COUNT) {
		// References to the three vertices of the triangle.
		GltfHelper::Vertex& v0 = primitive.vertices[primitive.indices[i]];
		GltfHelper::Vertex& v1 = primitive.vertices[primitive.indices[i + 1]];
		GltfHelper::Vertex& v2 = primitive.vertices[primitive.indices[i + 2]];
		
		// Compute normal. Normalization happens later.
		const vec3 pos0 = v0.position;
		const vec3 d0 = v2.position - pos0;
		const vec3 d1 = v1.position - pos0;
		const vec3 normal = cross(d0, d1);
		
		// Add the normal to the three vertices of the triangle. Normals are added
		// so that reused vertices will get the average normal (done later).
		// Note that the normals are not normalized at this point, so larger triangles
		// will have more weight than small triangles which share a vertex. This
		// appears to give better results.
		v0.normal = v0.normal + normal;
		v1.normal = v1.normal + normal;
		v2.normal = v2.normal + normal;
	}
	
	// Since the same vertex may have been used by multiple triangles, and the cross product normals
	// aren't normalized yet, normalize the computed normals.
	for (GltfHelper::Vertex& vertex : primitive.vertices) {
		vertex.normal = vertex.normal.GetNormalized();
	}
}

// Some data, like texCoords, can be represented 32bit float or normalized unsigned short or byte.
// ReadNormalizedFloat provides overloads for all three types.
template <typename T> float ReadNormalizedFloat(const byte* ptr);
template<> float ReadNormalizedFloat<float>(const byte* ptr) {
	return *reinterpret_cast<const float*>(ptr);
}

template<> float ReadNormalizedFloat<unsigned short>(const byte* ptr) {
	return *reinterpret_cast<const unsigned short*>(ptr) / (float)std::numeric_limits<unsigned short>::max();
}

template<> float ReadNormalizedFloat<unsigned char>(const byte* ptr) {
	return *reinterpret_cast<const unsigned char*>(ptr) / (float)std::numeric_limits<unsigned char>::max();
}

// Convert array of 16 doubles to an XMMATRIX.
mat4 Double4x4ToXMMatrix(mat4 def_mat, const Vector<double>& dbl_data) {
	if (dbl_data.GetCount() != 16) {
		return def_mat;
	}
	
	return mat4{(float)dbl_data[0],  (float)dbl_data[1],  (float)dbl_data[2],  (float)dbl_data[3],
			    (float)dbl_data[4],  (float)dbl_data[5],  (float)dbl_data[6],  (float)dbl_data[7],
			    (float)dbl_data[8],  (float)dbl_data[9], (float)dbl_data[10], (float)dbl_data[11],
			   (float)dbl_data[12], (float)dbl_data[13], (float)dbl_data[14], (float)dbl_data[15]};
}

// Convert array of three doubles to an XMVECTOR.
vec3 Double3ToVector(vec3 def_vec, const Vector<double>& dbl_data) {
	if (dbl_data.GetCount() != 3) {
		return def_vec;
	}
	
	return vec3((float)dbl_data[0], (float)dbl_data[1], (float)dbl_data[2]);
}

// Convert array of four doubles to an XMVECTOR.
vec4 Double4ToXMVector(vec4 def_vec, const Vector<double>& dbl_data) {
	if (dbl_data.GetCount() != 4) {
		return def_vec;
	}
	
	return vec4((float)dbl_data[0], (float)dbl_data[1], (float)dbl_data[2], (float)dbl_data[3]);
}

// Validate that an accessor does not go out of bounds of the buffer view that it references and that the buffer view does not exceed
// the bounds of the buffer that it references.
void ValidateAccessor(const tinygltf::Accessor& accessor, const tinygltf::BufferView& buf_view, const tinygltf::Buffer& buffer, size_t byteStride, size_t elementSize) {
	// Make sure the accessor does not go out of range of the buffer view.
	if (accessor.byteOffset + (accessor.count - 1) * byteStride + elementSize > buf_view.byteLength) {
		throw Exc("Accessor goes out of range of bufferview.");
	}
	
	// Make sure the buffer view does not go out of range of the buffer.
	if (buf_view.byteOffset + buf_view.byteLength > buffer.data.size()) {
		throw Exc("BufferView goes out of range of buffer.");
	}
}

// Reads the tangent data (VEC4) from a glTF primitive into a GltfHelper Primitive.
void ReadTangentToVertexField(const tinygltf::Accessor& accessor, const tinygltf::BufferView& buf_view, const tinygltf::Buffer& buffer, GltfHelper::Primitive& primitive) {
	if (accessor.type != TINYGLTF_TYPE_VEC4) {
		throw Exc("Accessor for primitive attribute has incorrect type (VEC4 expected).");
	}
	
	if (accessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
		throw Exc("Accessor for primitive attribute has incorrect component type (FLOAT expected).");
	}
	
	// If stride is not specified, it is tightly packed.
	constexpr size_t packed_size = sizeof(vec4);
	const size_t stride = buf_view.byteStride == 0 ? packed_size : buf_view.byteStride;
	ValidateAccessor(accessor, buf_view, buffer, stride, packed_size);
	
	// Resize the vertices vector, if necessary, to include room for the attribute data.
	// If there are multiple attributes for a primitive, the first one will resize, and the subsequent will not need to.
	primitive.vertices.SetCount(accessor.count);
	
	// Copy the attribute value over from the glTF buffer into the appropriate vertex field.
	const unsigned char* buf_ptr = buffer.data.data() + buf_view.byteOffset + accessor.byteOffset;
	for (size_t i = 0; i < accessor.count; i++, buf_ptr += stride) {
		primitive.vertices[i].tangent = *reinterpret_cast<const vec4*>(buf_ptr);
	}
}

// Reads the TexCoord data (VEC2) from a glTF primitive into a GltfHelper Primitive.
// This function uses a template type to express the VEC2 component type (byte, ushort, or float).
template <typename TComponentType, vec2 GltfHelper::Vertex::*field>
void ReadTexCoordToVertexField(const tinygltf::Accessor& accessor, const tinygltf::BufferView& buf_view, const tinygltf::Buffer& buffer, GltfHelper::Primitive& primitive) {
	// If stride is not specified, it is tightly packed.
	constexpr size_t packed_size = sizeof(TComponentType) * 2;
	const size_t stride = buf_view.byteStride == 0 ? packed_size : buf_view.byteStride;
	ValidateAccessor(accessor, buf_view, buffer, stride, packed_size);
	
	// Resize the vertices vector, if necessary, to include room for the attribute data.
	// If there are multiple attributes for a primitive, the first one will resize, and the subsequent will not need to.
	primitive.vertices.SetCount(accessor.count);
	
	// Copy the attribute value over from the glTF buffer into the appropriate vertex field.
	const unsigned char* buf_ptr = buffer.data.data() + buf_view.byteOffset + accessor.byteOffset;
	for (size_t i = 0; i < accessor.count; i++, buf_ptr += stride) {
		(primitive.vertices[i].*field)[0] = ReadNormalizedFloat<TComponentType>(buf_ptr);
		(primitive.vertices[i].*field)[1] = ReadNormalizedFloat<TComponentType>(buf_ptr + sizeof(TComponentType));
	}
}

// Reads the TexCoord data (VEC2) from a glTF primitive into a GltfHelper Primitive.
template <vec2 GltfHelper::Vertex::*field>
void ReadTexCoordToVertexField(const tinygltf::Accessor& accessor, const tinygltf::BufferView& buf_view, const tinygltf::Buffer& buffer, GltfHelper::Primitive& primitive) {
	if (accessor.type != TINYGLTF_TYPE_VEC2) {
		throw Exc("Accessor for primitive TexCoord must have VEC2 type.");
	}
	
	if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) {
		ReadTexCoordToVertexField<float, field>(accessor, buf_view, buffer, primitive);
	}
	else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
		if (!accessor.normalized) {
			throw Exc("Accessor for TEXTCOORD_n unsigned byte must be normalized.");
		}
		ReadTexCoordToVertexField<byte, field>(accessor, buf_view, buffer, primitive);
	}
	else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
		if (!accessor.normalized) {
			throw Exc("Accessor for TEXTCOORD_n unsigned short must be normalized.");
		}
		ReadTexCoordToVertexField<unsigned short, field>(accessor, buf_view, buffer, primitive);
	}
	else {
		throw Exc("Accessor for TEXTCOORD_n uses unsupported component type.");
	}
}

// Reads VEC3 attribute data (like POSITION and NORMAL) from a glTF primitive into a GltfHelper Primitive. The specific Vertex field is specified as a template parameter.
template <vec3 GltfHelper::Vertex::*field>
void ReadVec3ToVertexField(const tinygltf::Accessor& accessor, const tinygltf::BufferView& buf_view, const tinygltf::Buffer& buffer, GltfHelper::Primitive& primitive) {
	if (accessor.type != TINYGLTF_TYPE_VEC3) {
		throw Exc("Accessor for primitive attribute has incorrect type (VEC3 expected).");
	}
	
	if (accessor.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT) {
		throw Exc("Accessor for primitive attribute has incorrect component type (FLOAT expected).");
	}
	
	// If stride is not specified, it is tightly packed.
	constexpr size_t packed_size = sizeof(vec3);
	const size_t stride = buf_view.byteStride == 0 ? packed_size : buf_view.byteStride;
	ValidateAccessor(accessor, buf_view, buffer, stride, packed_size);
	
	// Resize the vertices vector, if necessary, to include room for the attribute data.
	// If there are multiple attributes for a primitive, the first one will resize, and the subsequent will not need to.
	primitive.vertices.SetCount(accessor.count);
	
	// Copy the attribute value over from the glTF buffer into the appropriate vertex field.
	const unsigned char* buf_ptr = buffer.data.data() + buf_view.byteOffset + accessor.byteOffset;
	for (size_t i = 0; i < accessor.count; i++, buf_ptr += stride) {
		(primitive.vertices[i].*field) = *reinterpret_cast<const vec3*>(buf_ptr);
	}
}

// Load a primitive's (vertex) attributes. Vertex attributes can be positions, normals, tangents, texture coordinates, colors, and more.
void LoadAttributeAccessor(const tinygltf::Model& gltf_model, const std::string& attr_name, int accessor_id, GltfHelper::Primitive& primitive) {
	const auto& accessor = gltf_model.accessors.at(accessor_id);
	
	if (accessor.bufferView == -1) {
		throw Exc("Accessor for primitive attribute specifies no bufferview.");
	}
	
	// WARNING: This version of the tinygltf loader does not support sparse accessors, so neither does this renderer.
	
	const tinygltf::BufferView& buf_view = gltf_model.bufferViews.at(accessor.bufferView);
	if (buf_view.target != TINYGLTF_TARGET_ARRAY_BUFFER && buf_view.target != 0) { // Allow 0 (not specified) even though spec doesn't seem to allow this (BoomBox GLB fails)
		throw Exc("Accessor for primitive attribute uses bufferview with invalid 'target' type.");
	}
	
	const tinygltf::Buffer& buffer = gltf_model.buffers.at(buf_view.buffer);
	
	if (attr_name == "POSITION") {
		ReadVec3ToVertexField<&GltfHelper::Vertex::position>(accessor, buf_view, buffer, primitive);
	}
	else if (attr_name == "NORMAL") {
		ReadVec3ToVertexField<&GltfHelper::Vertex::normal>(accessor, buf_view, buffer, primitive);
	}
	else if (attr_name == "TANGENT") {
		ReadTangentToVertexField(accessor, buf_view, buffer, primitive);
	}
	else if (attr_name == "TEXCOORD_0") {
		ReadTexCoordToVertexField<&GltfHelper::Vertex::tex_coord>(accessor, buf_view, buffer, primitive);
	}
	else {
		return; // Ignore unsupported vertex accessors like COLOR_0.
	}
}

// Reads index data from a glTF primitive into a GltfHelper Primitive. glTF indices may be 8bit, 16bit or 32bit integers.
// This will coalesce indices from the source type(s) into a 32bit integer.
template <typename TSrcIndex>
void ReadIndices(const tinygltf::Accessor& accessor, const tinygltf::BufferView& buf_view, const tinygltf::Buffer& buffer, GltfHelper::Primitive& primitive) {
	if (buf_view.target != TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER && buf_view.target != 0) { // Allow 0 (not specified) even though spec doesn't seem to allow this (BoomBox GLB fails)
		throw Exc("Accessor for indices uses bufferview with invalid 'target' type.");
	}
	
	constexpr size_t ComponentSizeBytes = sizeof(TSrcIndex);
	if (buf_view.byteStride != 0 && buf_view.byteStride != ComponentSizeBytes) { // Index buffer must be packed per glTF spec.
		throw Exc("Accessor for indices uses bufferview with invalid 'byteStride'.");
	}
	
	ValidateAccessor(accessor, buf_view, buffer, ComponentSizeBytes, ComponentSizeBytes);
	
	if ((accessor.count % 3) != 0) { // Since only triangles are supported, enforce that the number of indices is divisible by 3.
		throw Exc("Unexpected number of indices for triangle primitive");
	}
	
	const TSrcIndex* indexBuffer = reinterpret_cast<const TSrcIndex*>(buffer.data.data() + buf_view.byteOffset + accessor.byteOffset);
	for (uint32 i = 0; i < accessor.count; i++) {
		primitive.indices.push_back(*(indexBuffer + i));
	}
}

// Reads index data from a glTF primitive into a GltfHelper Primitive.
void LoadIndexAccessor(const tinygltf::Model& gltf_model, const tinygltf::Accessor& accessor, GltfHelper::Primitive& primitive) {
	if (accessor.type != TINYGLTF_TYPE_SCALAR) {
		throw Exc("Accessor for indices specifies invalid 'type'.");
	}
	
	if (accessor.bufferView == -1) {
		throw Exc("Index accessor without buf_view is currently not supported.");
	}
	
	const tinygltf::BufferView& buf_view = gltf_model.bufferViews.at(accessor.bufferView);
	const tinygltf::Buffer& buffer = gltf_model.buffers.at(buf_view.buffer);
	
	if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
		ReadIndices<unsigned char>(accessor, buf_view, buffer, primitive);
	}
	else
		if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
			ReadIndices<unsigned short>(accessor, buf_view, buffer, primitive);
		}
		else
			if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
				ReadIndices<unsigned int>(accessor, buf_view, buffer, primitive);
			}
			else {
				throw Exc("Accessor for indices specifies invalid 'componentType'.");
			}
}


namespace GltfHelper {

mat4 ReadNodeLocalTransform(const tinygltf::Node& gltf_node) {
	TODO
	/*
	// A node may specify either a 4x4 matrix or TRS (Translation-Rotation-Scale) values, but not both.
	if (gltf_node.matrix.GetCount() == 16) {
		return Double4x4ToXMMatrix(identity<mat4>(), gltf_node.matrix);
	}
	else {
		// No matrix is present, so construct a matrix from the TRS values (each one is optional).
		return XMMatrixTransformation(
				   g_XMZero, // Scaling origin
				   identity<quat>(),
				   Double3ToVector(g_XMOne, gltf_node.scale), // Scale
				   g_XMZero, // Rotating origin
				   Double4ToVector(identity<quat>(), gltf_node.rotation), // Rotation
				   Double3ToVector(g_XMZero, gltf_node.translation)); // Translation
	}
	*/
}

Primitive ReadPrimitive(const tinygltf::Model& gltf_model, const tinygltf::Primitive& gltf_primitive) {
	if (gltf_primitive.mode != TINYGLTF_MODE_TRIANGLES) {
		throw Exc("Unsupported primitive mode. Only TINYGLTF_MODE_TRIANGLES is supported.");
	}
	
	Primitive primitive;
	
	// glTF vertex data is stored in an attribute dictionary. Loop through each attribute and insert it into the GltfHelper primitive.
	for (const auto& attribute : gltf_primitive.attributes) {
		LoadAttributeAccessor(gltf_model, attribute.first /* attribute name */, attribute.second /* accessor index */, primitive);
	}
	
	if (gltf_primitive.indices != -1) {
		// If indices are specified for the glTF primitive, read them into the GltfHelper Primitive.
		LoadIndexAccessor(gltf_model, gltf_model.accessors.at(gltf_primitive.indices), primitive);
	}
	else {
		// When indices is not defined, the primitives should be rendered without indices using drawArrays()
		// This is the equivalent to having an index in sequence for each vertex.
		const uint32 vertexCount = (uint32)primitive.vertices.GetCount();
		if ((vertexCount % 3) != 0) {
			throw Exc("Non-indexed triangle-based primitive must have number of vertices divisible by 3.");
		}
		
		primitive.indices.Reserve(primitive.indices.GetCount() + vertexCount);
		for (uint32 i = 0; i < vertexCount; i ++) {
			primitive.indices.push_back(i);
		}
	}
	
	// If normals are missing, compute flat normals. Normals must be computed before tangents.
	if (gltf_primitive.attributes.find("NORMAL") == std::end(gltf_primitive.attributes)) {
		ComputeTriangleNormals(primitive);
	}
	
	// If tangents are missing, compute tangents.
	if (gltf_primitive.attributes.find("TANGENT") == std::end(gltf_primitive.attributes)) {
		ComputeTriangleTangents(primitive);
	}
	
	return primitive;
}

Material ReadMaterial(const tinygltf::Model& gltf_model, const tinygltf::Material& gltf_material) {
	// Read an optional VEC4 parameter if available, otherwise use the default.
	auto read_param_factor_as_vec4 = [](const tinygltf::ParameterMap & parameters, const char* name, const vec4& def) {
		auto c = parameters.find(name);
		return (c != parameters.end() && c->second.number_array.size() == 4) ?
				vec4((float)c->second.number_array[0], (float)c->second.number_array[1], (float)c->second.number_array[2], (float)c->second.number_array[3]) :
				def;
	};
	
	// Read an optional VEC3 parameter if available, otherwise use the default.
	auto read_param_factor_as_vec3 = [](const tinygltf::ParameterMap & parameters, const char* name, const vec3& def) {
		auto c = parameters.find(name);
		return (c != parameters.end() && c->second.number_array.size() == 3) ?
				vec3((float)c->second.number_array[0], (float)c->second.number_array[1], (float)c->second.number_array[2]) :
				def;
	};
	
	// Read an optional scalar parameter if available, otherwise use the default.
	auto read_param_factor_as_scalar = [](const tinygltf::ParameterMap & parameters, const char* name, double def) {
		auto c = parameters.find(name);
		return (c != parameters.end() && c->second.number_array.size() == 1) ? c->second.number_array[0] : def;
	};
	
	// Read a specific texture from a tinygltf material parameter map.
	auto LoadTextureFromParameter = [&](const tinygltf::ParameterMap & param_map, const char* tex_name) {
		Material::Texture texture {};
		
		const auto& textureIt = param_map.find(tex_name);
		if (textureIt != std::end(param_map)) {
			const int textureIndex = (int)textureIt->second.json_double_value.at("index");
			const tinygltf::Texture& gltfTexture = gltf_model.textures.at(textureIndex);
			if (gltfTexture.source != -1) {
				texture.image = &gltf_model.images.at(gltfTexture.source);
			}
			
			if (gltfTexture.sampler != -1) {
				texture.sampler = &gltf_model.samplers.at(gltfTexture.sampler);
			}
		}
		
		return texture;
	};
	
	// Read a scalar value from a tinygltf material parameter map.
	auto LoadScalarFromParameter = [&](const tinygltf::ParameterMap & param_map, const char* name, const char* scalar_field, double def_val) {
		const auto& textureIt = param_map.find(name);
		if (textureIt != std::end(param_map)) {
			const auto& json_dbl_values = textureIt->second.json_double_value;
			const auto& json_dbl_it = json_dbl_values.find(scalar_field);
			if (json_dbl_it != std::end(json_dbl_values)) {
				return json_dbl_it->second;
			}
		}
		
		return def_val;
	};
	
	// Read all of the optional material fields from the tinygltf object model and store them in a GltfHelper Material object
	// coalesced with proper defaults when needed.
	Material material;
	
	material.base_color_texture = LoadTextureFromParameter(gltf_material.values, "baseColorTexture");
	material.base_color_factor = read_param_factor_as_vec4(gltf_material.values, "baseColorFactor", vec4(1, 1, 1, 1));
	
	material.metallic_roughness_texture = LoadTextureFromParameter(gltf_material.values, "metallicRoughnessTexture");
	material.metallic_factor = (float)read_param_factor_as_scalar(gltf_material.values, "metallicFactor", 1);
	material.roughness_factor = (float)read_param_factor_as_scalar(gltf_material.values, "roughnessFactor", 1);
	
	material.emissive_texture = LoadTextureFromParameter(gltf_material.additionalValues, "emissiveTexture");
	material.emissive_factor = read_param_factor_as_vec3(gltf_material.additionalValues, "emissiveFactor", vec3(0, 0, 0));
	
	material.normal_texture = LoadTextureFromParameter(gltf_material.additionalValues, "normalTexture");
	material.normal_scale = (float)LoadScalarFromParameter(gltf_material.additionalValues, "normalTexture", "scale", 1.0);
	
	material.occlusion_texture = LoadTextureFromParameter(gltf_material.additionalValues, "occlusionTexture");
	material.occlusion_strength = (float)LoadScalarFromParameter(gltf_material.additionalValues, "occlusionTexture", "strength", 1.0);
	
	return material;
}

const byte* ReadImageAsRGBA(const tinygltf::Image& image, Vector<byte>* temp_buffer) {
	// The image vector (image.image) will be populated if the image was successfully loaded by glTF.
	if (image.width > 0 && image.height > 0) {
		if (image.width * image.height * image.component != image.image.size()) {
			throw Exc("Invalid image buffer size");
		}
		
		// Not supported: STBI_grey (DXGI_FORMAT_R8_UNORM?) and STBI_grey_alpha.
		if (image.component == 3) {
			// Convert RGB to RGBA.
			temp_buffer->SetCount(image.width * image.height * 4);
			for (int y = 0; y < image.height; ++y) {
				const unsigned char* src = image.image.data() + y * image.width * 3;
				unsigned char* dest = temp_buffer->Begin() + y * image.width * 4;
				for (int x = image.width - 1; x >= 0; --x, src += 3, dest += 4) {
					dest[0] = src[0];
					dest[1] = src[1];
					dest[2] = src[2];
					dest[3] = 255;
				}
			}
			
			return temp_buffer->Begin();
		}
		else if (image.component == 4) {
			// Already RGBA, no conversion needed
			return image.image.data();
		}
	}
	
	return nullptr;
}


}


NAMESPACE_PARALLEL_END

#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


void MaterialParameters::Clear() {
	diffuse = vec3(0.5f, 0.5f, 0.5f);
	ambient.Clear();
	specular.Clear();
	shininess = 0;
	
	base_clr_factor = vec4{ 1, 1, 1, 1 };
	metallic_factor = 1;
	roughness_factor = 1;
	emissive_factor = vec3{ 1, 1, 1 };
	normal_scale = 1;
	occlusion_strength = 1;
	
}

void MaterialParameters::Etherize(Ether& e) {
	e % diffuse
	  % ambient
	  % specular
	  % shininess
	
	  % base_clr_factor
	  % metallic_factor
	  % roughness_factor
	  % emissive_factor
	  % normal_scale
	  % occlusion_strength;
}



Material::Material() {
	Clear();
}

void Material::Etherize(Ether& e) {
	e % id
	  % *params;
	if (e.IsStoring()) ++params;
	
	if (e.IsLoading()) {
		e.Get(tex_id, sizeof(tex_id));
		e.Get(tex_filter, sizeof(tex_filter));
	}
	else if (e.IsStoring()) {
		e.Put(tex_id, sizeof(tex_id));
		e.Put(tex_filter, sizeof(tex_filter));
	}
}

void Material::Clear() {
	params.Set([&](MaterialParameters& data) {
		data.Clear();
	});
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		tex_id[i] = -1;
		tex_filter[i] = GVar::DEFAULT_FILTER;
	}
}

Material& Material::SetDiffuse(const Color& clr) {
	RGBA r = clr;
	params->diffuse = vec3(
		r.r / 255.0,
		r.g / 255.0,
		r.b / 255.0);
	return *this;
}

Material& Material::SetDiffuse(const vec3& clr) {
	params->diffuse = clr;
	return *this;
}

Material& Material::SetDiffuse(const vec4& clr) {
	params->diffuse = clr.Splice();
	//params->transparency = clr[3];
	return *this;
}

void Material::SetFlat(const vec4& base_color_factor, float roughness_factor /* = 1.0f */, float metallic_factor /* = 0.0f */, const vec4& emissive_factor /* = XMFLOAT3(0, 0, 0) */)
{
    params.Set([&](MaterialParameters& data) {
        StoreVec4(&data.base_clr_factor, base_color_factor);
        StoreVec3(&data.emissive_factor, emissive_factor);
        data.metallic_factor = metallic_factor;
        data.roughness_factor = roughness_factor;
    });
	
	vec4 diffuse = params->diffuse.Embed() * params->base_clr_factor;
	vec4 shininess(params->metallic_factor);
	vec4 ambient(params->roughness_factor);
	vec4 normals(0.5f, 0.5f, 1, 1);
	vec4 emissive(params->emissive_factor.Embed());
	
    SetTexture(TEXTYPE_DIFFUSE,			CreateSolidColorTexture(diffuse),	"gen_diffuse");
    SetTexture(TEXTYPE_SHININESS,		CreateSolidColorTexture(shininess),	"gen_shininess");
    SetTexture(TEXTYPE_AMBIENT,			CreateSolidColorTexture(ambient),	"gen_ambient"); // No occlusion.
    SetTexture(TEXTYPE_NORMALS,			CreateSolidColorTexture(normals),	"gen_normals"); // Flat normal.
    SetTexture(TEXTYPE_EMISSIVE,		CreateSolidColorTexture(emissive),	"gen_emissive");
	
}

void Material::SetTexture(TexType slot, const Image& img, String path) {
	ASSERT(slot >= TEXTYPE_NONE && slot < TEXTYPE_COUNT);
	tex_id[slot] = owner->AddTexture(img, path);
}

Image Material::CreateSolidColorTexture(vec4 clr) {
	for(int i = 0; i < 4; i++) {ASSERT(clr[i] >= 0 && clr[i] <= 1);}
	ImageBuffer ib(1,1);
	RGBA* dst = ib.Begin();
	dst->r = (byte)(clr[0] * 255.0);
	dst->g = (byte)(clr[1] * 255.0);
	dst->b = (byte)(clr[2] * 255.0);
	dst->a = (byte)(clr[3] * 255.0);
	return ib;
}

void Material::SetDefault() {
	params.Set([&](MaterialParameters& data) {
		data.Clear();
		data.ambient = vec3(1.0, 1.0, 0.0);
		data.diffuse = vec3(1.0, 0.0, 1.0);
		data.specular = vec3(0.0, 1.0, 1.0);
		data.shininess = 0.5;
	});
}

Material DefaultMaterial() {
	Material m;
	m.SetDefault();
	return m;
}




NAMESPACE_TOPSIDE_END

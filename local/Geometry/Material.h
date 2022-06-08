#ifndef _Geometry_Material_h_
#define _Geometry_Material_h_

NAMESPACE_TOPSIDE_BEGIN


class Model;

struct MaterialParameters {
    vec3 ambient = {0,0,0};
    vec3 diffuse = {0,0,0};
    vec3 specular = {0,0,0};
    float shininess = 0;
    
    // Pbr
	vec4 base_clr_factor{ 1, 1, 1, 1 };
	float metallic_factor{ 1 };
	float roughness_factor{ 1 };
	vec3 emissive_factor{ 1, 1, 1 };
	float normal_scale{ 1 };
	float occlusion_strength{ 1 };
	
	
	void Clear();
	
};

struct Material {
	typedef enum {
	    BaseColor = 0,
	    MetallicRoughness,
	    Normal,
	    Occlusion,
	    Emissive,
	    
	    TypeCount
	} TexType;
	
	Model* owner = 0;
	int index = -1;
	
	TrackChanges<MaterialParameters> params;
	
    FixedArray<Image, TypeCount> textures;
	
    // Create a flat (no texture) material.
    void SetFlat(
        const vec4&			base_color_factor,
        float				roughness_factor = 1.0f,
        float				metallic_factor = 0.0f,
        const vec4&			emissive_factor = vec4{0,0,0,1});
    void SetTexture(TexType slot, const Image& img);
    void SetDefault();

    void Clear();
    
    
    static Image CreateSolidColorTexture(vec4 clr);
    
};

Material DefaultMaterial();


NAMESPACE_TOPSIDE_END

#endif

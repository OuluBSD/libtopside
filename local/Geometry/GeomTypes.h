#ifndef _ManyCore_GeomTypes_h_
#define _ManyCore_GeomTypes_h_

NAMESPACE_OULU_BEGIN


struct Vertex : Moveable<Vertex> {
    vec3 position;
    float pos_project;
    vec3 normal;
    vec2 tex_coords;
    
    void Set(vec3 pos, vec3 norm);
    void Set(vec3 pos, vec3 norm, vec3 tan, vec2 tex);
    void Set(float x, float y, float z);
    void Set(float x, float y, float z, float tex_x, float tex_y);
};

struct Texture : Moveable<Texture> {
	Vector<byte>	data;
	uint8			stride;
	uint16			pitch;
	uint16			width, height;
	byte			compression;
	int				tex_id = -1;
	
	enum {
		COMP_NONE,
	};
	
	Texture() {}
	Texture(const Texture& src) {*this = src;}
	~Texture() {ClearAccel();}
	
	void Clear();
	void Set(Image i);
	void Create(Size sz, byte channels);
	void Zero() {if (data.GetCount()) memset(data.Begin(), 0, data.GetCount());}
	
	void MakeAccel();
	void ClearAccel();
	
	bool IsEmpty() {return data.IsEmpty();}
	operator bool() const {return !data.IsEmpty();}
	byte* GetIter(int x, int y) {return data.Begin() + y * pitch + x * stride;}
	int GetWidth() const {return width;}
	int GetHeight() const {return height;}
	
	void operator=(const Texture& src) {
		Clear();
		stride = src.stride;
		pitch = src.pitch;
		width = src.width;
		height = src.height;
		compression = src.compression;
		if (src.data.GetCount()) {
			int size = width * height * stride;
			data.SetCount(size);
			memcpy(data.Begin(), src.data.Begin(), size);
		}
	}
};

typedef Texture FrameBuffer;


struct DepthValue : Moveable<DepthValue> {
	float depth;
	int triangle_i;
};

struct DepthBuffer : Moveable<DepthBuffer> {
	Vector<DepthValue> data;
	uint16 width, height;
	
	void Clear();
	void Create(Size sz);
	void Reset();
	bool IsEmpty() {return data.IsEmpty();}
};




struct Material {
    vec3 ambient = {0,0,0};
    vec3 diffuse = {0,0,0};
    vec3 specular = {0,0,0};
    float shininess = 0;
    
    void Clear() {ambient.Clear(); diffuse.Clear(); specular.Clear(); shininess = 0;}
    void SetDefault();
    
};

Material DefaultMaterial();


class BoundingBox {
public:
    enum Align {
        ALIGN_CENTER,
        ALIGN_X_MIN,
        ALIGN_X_MAX,
        ALIGN_Y_MIN,
        ALIGN_Y_MAX,
        ALIGN_Z_MIN,
        ALIGN_Z_MAX
    };

    BoundingBox();
    BoundingBox(vec3 min, vec3 max);
    
    void SetMinMax(vec3 min, vec3 max);
    void GetMinMax(vec3& min, vec3& max) const;
    vec3 GetDimensions() const;
    vec3 GetCenter(Align align = ALIGN_CENTER) const;
    bool Contains(vec3 pos) const;
    vec3 GetLimit(vec3 pos) const;
    vec3 GetWrap(vec3 pos) const;
    
protected:
    vec3 m_min;
    vec3 m_max;
};


enum TexType {
    TEXTYPE_NONE = 0x0,
    TEXTYPE_DIFFUSE = 0x1,
    TEXTYPE_SPECULAR = 0x2,
    TEXTYPE_AMBIENT = 0x3,
    TEXTYPE_EMISSIVE = 0x4,
    TEXTYPE_HEIGHT = 0x5,
    TEXTYPE_NORMALS = 0x6,
    TEXTYPE_SHININESS = 0x7,
    TEXTYPE_OPACITY = 0x8,
    TEXTYPE_DISPLACEMENT = 0x9,
    TEXTYPE_LIGHTMAP = 0xA,
    TEXTYPE_REFLECTION = 0xB,
    TEXTYPE_UNKNOWN = 0xC,
    
    TEXTYPE_COUNT
};


NAMESPACE_OULU_END

#endif

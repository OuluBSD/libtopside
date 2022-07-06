#ifndef _ManyCore_GeomTypes_h_
#define _ManyCore_GeomTypes_h_

NAMESPACE_TOPSIDE_BEGIN


typedef int NodeIndex;


struct Vertex : Moveable<Vertex> {
    vec4			position;
    vec3			normal;
    vec2			tex_coord;
    vec4			tangent;
    NodeIndex		mdl_transform_idx;
    
    void SetPosTex(vec3 pos, vec2 tex);
    void Set(vec3 pos, vec3 norm);
    void Set(vec3 pos, vec3 norm, vec3 tan, vec2 tex);
    void Set(float x, float y, float z);
    void Set(float x, float y, float z, float tex_x, float tex_y);
    
};


struct DepthImage {
	struct Info : Moveable<Info> {
		uint32 triangle_i;
		vec3 bc_screen;
		uint16 src_id;
	};
	
	
	Size sz;
	int pitch = 0;
	int channels = 0;
	int size = 0;
	
public:
	Vector<Info> info;
	Vector<float> data;
	
public:
	typedef DepthImage CLASSNAME;
	DepthImage() : sz(0,0) {}
	~DepthImage() {Clear();}
	
	void operator=(const Nuller&) {Clear();}
	
	bool Create() {return true;} // for IGraphics compatibility
	void Set(Size sz, int channels);
	void Clear();
	void Zero(float zero_depth);
	
	int GetPitch() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetChannels() const;
	int GetSize() const;
	float* GetIter(int x, int y);
	const float* GetIter(int x, int y) const;
	
	float* Begin();
	float* End();
	float* Detach();
	
	bool IsEmpty() {return data.IsEmpty();}
	operator bool() const {return !data.IsEmpty();}
	
};

typedef const DepthImage ConstDepthImage;


/*
struct Texture : Moveable<Texture> {
	Vector<byte>	data;
	uint8			stride;
	uint16			pitch;
	uint16			width, height;
	byte			compression;
	//int				tex_id = -1;
	
	enum {
		COMP_NONE,
	};
	
	Texture() {}
	Texture(const Texture& src) {*this = src;}
	//~Texture() {ClearAccel();}
	
	void Clear();
	void Set(Image i);
	void Create(Size sz, byte channels);
	void Zero() {if (data.GetCount()) memset(data.Begin(), 0, data.GetCount());}
	
	//void MakeAccel();
	//void ClearAccel();
	
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

typedef Texture FrameBuffer;*/


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


typedef enum {
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
} TexType;

namespace GVar {

typedef enum : uint32 {
	COLOR0_EXT		= 1 << 0,
	COLOR1_EXT		= 1 << 1,
	COLOR2_EXT		= 1 << 2,
	COLOR3_EXT		= 1 << 3,
} RenderTarget;

}

/*
Texture channel ranges:
	0 - 12:	TexType
	13 - 16: shadertoy compat channels
*/
static const int TEXTYPE_OFFSET = 0;
static const int COMPAT_COUNT = 4;
static const int BUFFERSTAGE_COUNT = 5;
static const int COMPAT_OFFSET = TEXTYPE_COUNT;
static const int BUFFERSTAGE_OFFSET = TEXTYPE_COUNT + COMPAT_COUNT;
static const int CHANNEL_COUNT = TEXTYPE_COUNT + COMPAT_COUNT + BUFFERSTAGE_COUNT;
static const int CHANNEL_NONE = 0;

/*static const int CHANNEL_ICHANNEL0 = TEXTYPE_COUNT + 0;
static const int CHANNEL_ICHANNEL1 = TEXTYPE_COUNT + 1;
static const int CHANNEL_ICHANNEL2 = TEXTYPE_COUNT + 2;
static const int CHANNEL_ICHANNEL3 = TEXTYPE_COUNT + 3;*/



struct Ray {
	vec3 origin;
	vec3 direction;

	inline Ray() : direction(0.0f, 0.0f, 1.0f) {}
	inline Ray(const vec3& o, const vec3& d) : origin(o), direction(d) {direction.Normalize();}
	inline void NormalizeDirection() {direction.Normalize();}
};

struct Sphere {
	vec3 position;
	float radius;

	inline Sphere() : radius(1.0f) {}
	inline Sphere(const vec3& p, float r) : position(p), radius(r) {}
};

struct AABB {
	vec3 position;
	vec3 size; // half size

	inline AABB() : size(1, 1, 1) {}
	inline AABB(const vec3& p, const vec3& s) : position(p), size(s) {}
	
	String ToString() const {return position.ToString() + ", " + size.ToString();}
};

struct OBB : Moveable<OBB> {
	vec3 position;
	vec3 size; // half size
	mat3 orientation;

	inline OBB() : size(1, 1, 1) {}
	inline OBB(const vec3& p, const vec3& s) : position(p), size(s) { }
	inline OBB(const vec3& p, const vec3& s, const mat3& o) : position(p), size(s), orientation(o) {}
	
};

struct Plane : Moveable<Plane> {
	vec3 normal;
	float distance;

	inline Plane() : normal(1, 0, 0) {}
	inline Plane(const vec3& n, float d) : normal(n), distance(d) {}
};

struct RaycastResult : Moveable<RaycastResult> {
	vec3 point;
	vec3 normal;
	float t;
	bool hit;
};


NAMESPACE_TOPSIDE_END

#endif

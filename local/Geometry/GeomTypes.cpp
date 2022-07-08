#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


void Vertex::SetPosTex(vec3 pos, vec2 tex) {
    position = pos.Embed();
    tex_coord = tex;
    normal = zero<vec3>();
}

void Vertex::Set(vec3 pos, vec3 norm) {
    position = pos.Embed();
    normal = norm;
    tex_coord.Clear();
}

void Vertex::Set(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = 1.0;
    normal = zero<vec3>();
    tex_coord.Clear();
}

void Vertex::Set(vec3 pos, vec3 norm, vec3 tan, vec2 tex) {
    position = pos.Embed();
    normal = norm;
    tangent = tan.Embed();
    tex_coord = tex;
}

void Vertex::Set(float x, float y, float z, float tex_x, float tex_y) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    position[3] = 1.0;
    tex_coord[0] = tex_x;
    tex_coord[1] = tex_y;
    normal = zero<vec3>();
}






/*void Texture::Clear() {
	data.SetCount(0);
	stride = 0;
	pitch = 0;
	width = 0, height = 0;
	compression = 0;
	//ClearAccel();
}

void Texture::Create(Size sz, byte channels) {
	Clear();
	
	stride = channels;
	width = sz.cx;
	height = sz.cy;
	compression = COMP_NONE;
	pitch = width * stride;
	data.SetCount(width * height * stride);
	Zero();
}

void Texture::Set(Image i) {
	Clear();
	
	#ifdef LIBTOPSIDE
	Image::ImageDataRef* data = i.GetData();
	if (data) {
		auto& sysimg = data->img;
		stride = sysimg.GetStride();
		width = sysimg.GetWidth();
		height = sysimg.GetHeight();
		compression = COMP_NONE;
		pitch = width * stride;
		this->data.SetCount(width * height * stride);
		const byte* src = sysimg.GetData();
		byte* dst = this->data.Begin();
		for(int y = 0; y < height; y++) {
			memcpy(dst, src, pitch);
			dst += pitch;
			src += sysimg.GetPitch();
		}
	}
	#else
	if (!i.IsEmpty()) {
		stride = 4;
		width = i.GetWidth();
		height = i.GetHeight();
		compression = COMP_NONE;
		pitch = width * stride;
		this->data.SetCount(width * height * stride);
		const RGBA* src = i.Begin();
		RGBA* dst = (RGBA*)this->data.Begin();
		memcpy(dst, src, this->data.GetCount());
	}
	#endif
}*/

/*void Texture::MakeAccel() {
	if (tex_id < 0 && width > 0 && height > 0 && pitch > 0 && stride > 0 && data.GetCount()) {
		if (compression == COMP_NONE) {
#if HAVE_OPENGL
			GLuint* texture = (GLuint*)&tex_id;
			glGenTextures(1, texture);
			glBindTexture(GL_TEXTURE_2D, *texture);
		
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			int channels = pitch / width;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
				channels == 4 ? GL_BGRA : GL_BGR,
				GL_UNSIGNED_BYTE, data.Begin());
			glGenerateMipmap(GL_TEXTURE_2D);
#endif
		}
		else Panic("TODO");
	}
}*/

/*void Texture::ClearAccel() {
	if (tex_id >= 0) {
#if HAVE_OPENGL
		glDeleteTextures(1, (GLuint*)&tex_id);
		tex_id = -1;
#endif
	}
}*/



void DepthImage::Set(Size sz, int channels) {
	Clear();
	this->sz = sz;
	this->channels = channels;
	pitch = sz.cx * channels;
	size = pitch * sz.cy;
	ASSERT(channels >= 1 && channels <= 4);
	
	data.SetCount(size);
	info.SetCount(size);
}

void DepthImage::Zero(float zero_depth) {
	memset((Info*)info.Begin(), 0, size * sizeof(Info));
	for (float& f : data)
		f = zero_depth;
}

void DepthImage::Clear() {
	if (size) {
		data.SetCount(0);
		sz = Size(0, 0);
		pitch = 0;
		channels = 0;
		size = 0;
	}
}

int DepthImage::GetPitch() const {
	return pitch;
}

int DepthImage::GetWidth() const {
	return sz.cx;
}

int DepthImage::GetHeight() const {
	return sz.cy;
}

int DepthImage::GetChannels() const {
	return channels;
}

int DepthImage::GetSize() const {
	return size;
}

float* DepthImage::GetIter(int x, int y) {
	ASSERT(x >= 0 && y >= 0 && x < sz.cx && y < sz.cy);
	ASSERT(sz.cx && sz.cy && !data.IsEmpty() && pitch && channels);
	return (float*)data.Begin() + y * pitch + x * channels;
}

const float* DepthImage::GetIter(int x, int y) const {
	ASSERT(x >= 0 && y >= 0 && x < sz.cx && y < sz.cy);
	ASSERT(sz.cx && sz.cy && !data.IsEmpty() && pitch && channels);
	return (const float*)data.Begin() + y * pitch + x * channels;
}

float* DepthImage::Begin() {
	return data.Begin();
}

float* DepthImage::End() {
	if (data.IsEmpty())
		return 0;
	return data.Begin() + sz.cy * pitch;
}

float* DepthImage::Detach() {
	float* f = data.Begin();
	data.Clear();
	sz = Size(0, 0);
	pitch = 0;
	channels = 0;
	size = 0;
	return f;
}











void DepthBuffer::Clear() {
	data.SetCount(0);
	width = 0, height = 0;
}

void DepthBuffer::Create(Size sz) {
	width = sz.cx;
	height = sz.cy;
	data.SetCount(width * height);
	Reset();
}

void DepthBuffer::Reset() {
	if (data.GetCount()) {
		for(DepthValue& v : data) {
			v.triangle_i = -1;
			v.depth = -FLT_MAX;
		}
	}
}








bool Sphere::Contains(const AABB& p) const {
	for(int i = 0; i < 8; i++) {
		bool x_inv = i & 1;
		bool y_inv = i & 2;
		bool z_inv = i & 4;
		vec3 corner = p.position + vec3(
			x_inv ? +p.size[0] : -p.size[0],
			y_inv ? +p.size[1] : -p.size[1],
			z_inv ? +p.size[2] : -p.size[2]);
		if (!Contains(corner))
			return false;
	}
	return true;
}

bool Sphere::Contains(const vec3& p) const {
	return ContainsPoint(*this, p);
}

bool Sphere::Intersects(const AABB& o) const {
	return SphereAABB(*this, o);
}

bool Sphere::Intersects(const OBB& o) const {
	return SphereOBB(*this, o);
}




bool AABB::Contains(const vec3& p) const {
	return ContainsPoint(*this, p);
}

bool AABB::Intersects(const Sphere& o) const {
	return SphereAABB(o, *this);
}

bool AABB::Contains(const Frustum& p) const {
	vec3 corners[8];
	p.GetCorners(corners);
	for(int i = 0; i < 8; i++)
		if (!Contains(corners[i]))
			return false;
	return true;
}




bool OBB::Contains(const vec3& p) const {
	return ContainsPoint(*this, p);
}

bool OBB::Intersects(const Sphere& o) const {
	return SphereOBB(o, *this);
}




NAMESPACE_TOPSIDE_END

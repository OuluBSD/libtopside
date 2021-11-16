#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


void Vertex::Set(vec3 pos, vec3 norm) {
    position = pos;
    normal = norm;
    pos_project = 1.0;
    tex_coords.Clear();
}

void Vertex::Set(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    pos_project = 1.0;
    normal = zero<vec3>();
    tex_coords.Clear();
}

void Vertex::Set(vec3 pos, vec3 norm, vec3 tan, vec2 tex) {
    position = pos;
    normal = norm;
    pos_project = 1.0;
    tex_coords = tex;
}

void Vertex::Set(float x, float y, float z, float tex_x, float tex_y) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    pos_project = 1.0;
    tex_coords[0] = tex_x;
    tex_coords[1] = tex_y;
    normal = zero<vec3>();
}






void Texture::Clear() {
	data.SetCount(0);
	stride = 0;
	pitch = 0;
	width = 0, height = 0;
	compression = 0;
	ClearAccel();
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
}

void Texture::MakeAccel() {
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
}

void Texture::ClearAccel() {
	if (tex_id >= 0) {
#if HAVE_OPENGL
		glDeleteTextures(1, (GLuint*)&tex_id);
		tex_id = -1;
#endif
	}
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



void Material::SetDefault() {
	ambient = vec3(1.0, 1.0, 0.0);
	diffuse = vec3(1.0, 0.0, 1.0);
	specular = vec3(0.0, 1.0, 1.0);
	shininess = 0.5;
}

Material DefaultMaterial() {
	Material m;
	m.SetDefault();
	return m;
}






NAMESPACE_TOPSIDE_END

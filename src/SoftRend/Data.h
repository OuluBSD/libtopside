#ifndef _SoftRend_Data_h_
#define _SoftRend_Data_h_

NAMESPACE_TOPSIDE_BEGIN

struct SoftInited {
	bool inited = false;
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
	void Clear() {inited = 0;}
	void Create() {inited = 1;}
	
	SoftInited() {}
	SoftInited(const Nuller&) {}
	SoftInited(int) {}
};

struct SoftVertexBuffer : SoftInited {
	using SoftInited::SoftInited;
	Vector<Vertex> vertices;
	
	SoftVertexBuffer(int i = 0) {}
};

struct SoftElementBuffer : SoftInited {
	using SoftInited::SoftInited;
	Vector<uint32> indices;
	
	SoftElementBuffer(int i = 0) {}
};

struct SoftVertexArray : SoftInited {
	using SoftInited::SoftInited;
	SoftVertexBuffer* vbo = 0;
	SoftElementBuffer* ebo = 0;
	
	SoftVertexArray(int i = 0) {}
};


NAMESPACE_TOPSIDE_END

#endif

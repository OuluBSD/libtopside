#ifndef _ManyCore_Octree_h_
#define _ManyCore_Octree_h_

NAMESPACE_TOPSIDE_BEGIN


class OctreeNode;
class Octree;


struct OctreeObject : RTTIBase {
	OctreeNode* owner;
	vec3 rel_pos;
	
	
	RTTI_DECL0(OctreeObject);
	OctreeObject();
	virtual ~OctreeObject() {}
	
	void SetPosition(const vec3& pos);
	
	vec3 GetPosition() const;
	
};

struct OctreeDescriptorPoint : OctreeObject {
	RTTI_DECL1(OctreeDescriptorPoint, OctreeObject);
	
	PositionOrientationAverage av;
	union {
		byte b[DESCRIPTOR_BYTES];
		uint32 u[DESCRIPTOR_UINTS];
		uint64 u64[DESCRIPTOR_UINT64];
	};
	
};

class OctreeNode {
	
protected:
	friend class Octree;
	friend class OctreeObject;
	
	typedef byte BitVec;
	
	Octree* otree = NULL;
	OctreeNode* parent = NULL;
	OctreeNode* branch[8] = {0,0,0,0, 0,0,0,0};
	BitVec flags = 0;
	int8 level = 0;
	vec3 position = vec3(0,0,0);
	
public:
	LinkedList<One<OctreeObject>> objs;
	
	typedef RecyclerPool<OctreeNode> Rec;
	static inline Rec& GetRecyclerPool() {MAKE_STATIC(Rec, r); return r;}
	
public:
	
	enum {
		BR_LBI, // left, bottom, inner (-x, -y, -z) // note: "inner" might be forward in -z coord sys
		BR_RBI,
		BR_LTI,
		BR_RTI,
		BR_LBO,
		BR_RBO,
		BR_LTO,
		BR_RTO, // right, top, outer (+z, +y, +z)
	};
	
	enum {
		FLAG_DEBUGDRAW		= 1 << 0,
		
	};
	
	~OctreeNode() {Clear();}
		
	void Clear();
	
	//bool IsSeen() const;
	bool Contains(const vec3& pos) const;
	vec3 GetPosition() const;
	vec3 GetSize() const;
	float GetStep() const;
	AABB GetAABB() const;
	OctreeNode* At(int i) {ASSERT(i >= 0 && i < 8); return branch[i];}
	const OctreeNode* At(int i) const {ASSERT(i >= 0 && i < 8); return branch[i];}
	Octree& GetOctree() const;
	void Attach(OctreeObject* o);
	void Detach(OctreeObject* o);
	
	OctreeNode& SetDebugDraw(bool b=true) {Set(FLAG_DEBUGDRAW, b); return *this;}
	void Set(BitVec mask, bool value) {if (value) SetMaskTrue(mask); else SetMaskFalse(mask);}
	void SetMaskTrue(BitVec mask) {flags |= mask;}
	void SetMaskFalse(BitVec mask) {flags &= ~mask;}
	
	
	template <class T> T& Add() {
		T* o = new T();
		o->owner = this;
		objs.Add() = o;
		return *o;
	}
	
};

struct Frustum;
class Octree;

struct OctreeIterator {
	static const int MAX_LEVELS = 128;
	int pos[MAX_LEVELS] = {9};
	OctreeNode* addr[MAX_LEVELS];
	Octree* otree;
	int level = 0;
	
	bool Next();
	operator bool() const;
	OctreeNode& operator*();
	OctreeNode* operator->();
	bool operator==(const OctreeIterator& it) const {
		if (it.level != level || it.otree != otree)
			return false;
		for(int i = 0; i <= level; i++)
			if (pos[i] != it.pos[i])
				return false;
		return true;
	}
};

template <class T>
struct OctreeObjectIterator : OctreeIterator {
	T o;
	
	bool Next() {
		while (OctreeIterator::Next()) {
			ASSERT(pos[level] == 0);
			const OctreeNode* a = addr[level];
			AABB aabb = a->GetAABB();
			
			if (o.Intersects(aabb)) {
				//LOG("OctreeObjectIterator: match: " << aabb.ToString());
				return true;
			}
			else
				pos[level] = 8;
		}
		
		return false;
	}

	void operator++() {Next();}
	void operator++(int) {Next();}
	bool operator==(const OctreeObjectIterator& it) const {
		return OctreeIterator::operator==(it) && o == it.o;
	}
	
};

template <class T>
struct OctreeObjectCollection {
	using Iterator = OctreeObjectIterator<T>;
	
	Iterator iter;
	
	
	Iterator begin() const {return iter;}
	Iterator end() const {return Iterator();}
	Iterator begin() {return iter;}
	Iterator end() {return Iterator();}
	
};

typedef OctreeObjectIterator<Sphere> OctreeSphereIterator;
typedef OctreeObjectCollection<Sphere> OctreeSphereCollection;
typedef OctreeObjectIterator<Frustum> OctreeFrustumIterator;


class Octree {
	OctreeNode root;
	int min_scale_level = 0, max_scale_level = 0;
	int scale_count = 0;
	
	struct Level : Moveable<Level> {
		float step;
		int steps;
	};
	Vector<Level> levels;
	float max_len = 0;
	float max_off = 0;
	
public:
	typedef Octree CLASSNAME;
	Octree();
	
	void Initialize(int min_scale_level, int max_scale_level);
	
	int GetScaleLevel(float len) const;
	OctreeNode* GetAddNode(vec3 pos, int scale_level);
	OctreeNode& GetRoot() {return root;}
	const OctreeNode& GetRoot() const {return root;}
	uint64 GetSeekBits(vec3 pos, int level) const;
	OctreeFrustumIterator GetFrustumIterator(const Frustum& f);
	OctreeSphereIterator GetSphereIterator(const vec3& center, float radius);
	OctreeSphereCollection GetSphereCollection(const vec3& center, float radius);
	
	template <class T> OctreeObjectIterator<T> GetIterator(const T& o) {
		OctreeObjectIterator<T> it;
		it.otree = this;
		it.o = o;
		it.level = 0;
		it.pos[0] = -1;
		it.addr[0] = &root;
		it.Next();
		return it;
	}
	
	template <class T> OctreeObjectCollection<T> GetCollection(const T& o) {
		OctreeObjectCollection<T> c;
		c.iter = GetIterator(o);
		return c;
	}
	
	
	
	int LimitLevel(int scale_level) const;
	bool Contains(vec3 pos);
	
};


NAMESPACE_TOPSIDE_END


#endif

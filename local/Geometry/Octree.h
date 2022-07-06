#ifndef _ManyCore_Octree_h_
#define _ManyCore_Octree_h_

NAMESPACE_TOPSIDE_BEGIN


class OctreeNode;


struct OctreeObject : RTTIBase {
	OctreeNode* owner;
	vec3 rel_pos;
	
	
	RTTI_DECL0(OctreeObject);
	OctreeObject();
	
	void SetPosition(const vec3& pos);
	
	vec3 GetPosition() const;
	
};

class OctreeNode {
	
protected:
	friend class Octree;
	
	typedef byte BitVec;
	
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

struct OctreeFrustumIterator {
	static const int MAX_LEVELS = 128;
	
	const Frustum* frustum;
	int pos[MAX_LEVELS];
	const OctreeNode* addr[MAX_LEVELS];
	const Octree* otree;
	int level;
	
	
	void Next();
	operator bool() const;
	const OctreeNode& operator*() const;
	void operator++(int);
	
};

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
	OctreeFrustumIterator GetFrustumIterator(const Frustum& f) const;
	
	int LimitLevel(int scale_level) const;
	bool Contains(vec3 pos);
	
};


NAMESPACE_TOPSIDE_END


#endif

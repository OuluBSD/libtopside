#ifndef _ManyCore_Octree_h_
#define _ManyCore_Octree_h_

NAMESPACE_OULU_BEGIN


class OctreeNode;


class OctreeNodePool {
	Vector<OctreeNode*> recycle;
	SpinLock lock;
	
public:
	OctreeNodePool();
	OctreeNode* New();
	void Delete(OctreeNode* n);
	
};

class OctreeNode {
	
protected:
	friend class Octree;
	
	typedef byte BitVec;
	
	OctreeNode* down = NULL;
	OctreeNode* branch[8] = {0,0,0,0, 0,0,0,0};
	BitVec flags = 0;
	int8 level = 0;
	
	
	static OctreeNodePool& Pool() {return Single<OctreeNodePool>();}
	
public:
	
	enum {
		BR_LBI, // left, bottom, inner
		BR_RBI,
		BR_LTI,
		BR_RTI,
		BR_LBO,
		BR_RBO,
		BR_LTO,
		BR_RTO, // right, top, outer
	};
	
	enum {
		FLAG_DEBUGDRAW		= 1 << 0,
		
	};
	
	~OctreeNode() {Clear();}
		
	void Clear();
	
	bool IsSeen();
	
	OctreeNode& SetDebugDraw(bool b=true) {Set(FLAG_DEBUGDRAW, b); return *this;}
	void Set(BitVec mask, bool value) {if (value) SetMaskTrue(mask); else SetMaskFalse(mask);}
	void SetMaskTrue(BitVec mask) {flags |= mask;}
	void SetMaskFalse(BitVec mask) {flags &= ~mask;}
	
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
	mat4 transform;
	bool has_transform = false;
	
public:
	typedef Octree CLASSNAME;
	Octree();
	
	void Initialize(int min_scale_level, int max_scale_level);
	
	int GetScaleLevel(float len) const;
	OctreeNode* GetAddNode(vec3 pos, int scale_level);
	uint64 GetSeekBits(vec3 pos, int level) const;
	
	int LimitLevel(int scale_level) const;
	bool Contains(vec3 pos);
	
};


NAMESPACE_OULU_END


#endif

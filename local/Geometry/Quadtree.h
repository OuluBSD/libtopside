#ifndef _ManyCore_Quadtree_h_
#define _ManyCore_Quadtree_h_

NAMESPACE_TOPSIDE_BEGIN


class QuadtreeNode;

#define QUAD_BRANCHES 4

class QuadtreeNodePool {
	Vector<QuadtreeNode*> recycle;
	SpinLock lock;
	
public:
	QuadtreeNodePool();
	QuadtreeNode* New();
	void Delete(QuadtreeNode* n);
	
};

class QuadtreeNode {
	
protected:
	friend class Quadtree;
	
	typedef byte BitVec;
	
	QuadtreeNode* down = NULL;
	QuadtreeNode* branch[QUAD_BRANCHES] = {0,0,0,0};
	BitVec flags = 0;
	int8 level = 0;
	
	
	static QuadtreeNodePool& Pool() {return Single<QuadtreeNodePool>();}
	
public:
	
	enum {
		BR_LB, // left, bottom
		BR_RB,
		BR_LT,
		BR_RT // right, top
	};
	
	enum {
		FLAG_DEBUGDRAW		= 1 << 0,
		
	};
	
	~QuadtreeNode() {Clear();}
		
	void Clear();
	
	bool IsSeen();
	
	QuadtreeNode& SetDebugDraw(bool b=true) {Set(FLAG_DEBUGDRAW, b); return *this;}
	void Set(BitVec mask, bool value) {if (value) SetMaskTrue(mask); else SetMaskFalse(mask);}
	void SetMaskTrue(BitVec mask) {flags |= mask;}
	void SetMaskFalse(BitVec mask) {flags &= ~mask;}
	
};

class Quadtree {
	QuadtreeNode root;
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
	typedef Quadtree CLASSNAME;
	Quadtree();
	
	void Initialize(int min_scale_level, int max_scale_level);
	
	int GetScaleLevel(float len) const;
	QuadtreeNode* GetAddNode(vec3 pos, int scale_level);
	uint64 GetSeekBits(vec3 pos, int level) const;
	
	int LimitLevel(int scale_level) const;
	bool Contains(vec3 pos);
	
};


NAMESPACE_TOPSIDE_END


#endif

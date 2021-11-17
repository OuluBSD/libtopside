#ifndef _ComputerVision_Struct_h_
#define _ComputerVision_Struct_h_

NAMESPACE_TOPSIDE_BEGIN


struct BBox : Moveable<BBox> {
	double	x;
	double	y;
	double	width;
	double	height;
	
	int		neighbors;
	double	confidence;
	
	
	
	BBox() {Clear();}
	BBox(const BBox& c) {*this = c;}
	
	bool IsEmpty() const {return width <= 0 || height <= 0;}
	void Clear() {x = 0; y = 0; width = 0; height = 0; neighbors = 0; confidence = 0;}
	
	void operator=(const BBox& c) {
		x = c.x;
		y = c.y;
		width = c.width;
		height = c.height;
		neighbors = c.neighbors;
		confidence = c.confidence;
	}
	
	bool operator()(const BBox& a, const BBox& b) const {return a.confidence > b.confidence;}
	
};


bool IsBBoxCollision(const BBox& r1, const BBox& r2);
void GroupRectangles(const Vector<BBox>& rects, Vector<BBox>& result_seq, int min_neighbors = 1);
	



// color conversion
enum {
	COLOR_RGBA2GRAY,
	COLOR_RGB2GRAY,
	COLOR_BGRA2GRAY,
	COLOR_BGR2GRAY,
};

// box blur option
enum {
	BOX_BLUR_NOSCALE = 1
};

// svd options
enum {
	SVD_U_T = 0x01,
	SVD_V_T = 0x02,
};


class BinDescriptor : Moveable<BinDescriptor> {
public:
	union {
		uint32 u32[8];
		byte u8[32];
	};
};

class Keypoint : Moveable<Keypoint> {
	
public:
	int x = 0;
	int y = 0;
	int score = 0;
	int level = 0;
	double angle = -1.0;
	
	Keypoint() {}
	Keypoint(const Keypoint& s) {*this = s;}
	Keypoint(int x, int y) : x(x), y(y) {}
	Keypoint(int x, int y, int score, int level, double angle) {
		this->x = x;
		this->y = y;
		this->score = score;
		this->level = level;
		this->angle = angle;
	}
	
	void Set(int x, int y, int score, int level, double angle) {
		this->x = x;
		this->y = y;
		this->score = score;
		this->level = level;
		this->angle = angle;
	}
	
	void operator=(const Keypoint& s) {
		x = s.x;
		y = s.y;
		score = s.score;
		level = s.level;
		angle = s.angle;
	}
	
	void Clear() {
		x = 0;
		y = 0;
		score = 0;
		level = 0;
		angle = -1.0f;
	}
	
	bool operator()(const Keypoint& a, const Keypoint& b) const {
		return a.score > b.score;
	}
	
};


NAMESPACE_TOPSIDE_END

#endif

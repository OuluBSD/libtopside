#ifndef _ComputerVision_Struct_h_
#define _ComputerVision_Struct_h_

NAMESPACE_TOPSIDE_BEGIN




template <class T>
class data_t {
	
public:
	Vector<T> data;

	data_t() {}
};




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
	
};


bool _group_func(const BBox& r1, const BBox& r2);
void group_rectangles(const Vector<BBox>& rects, Vector<BBox>& result_seq, int min_neighbors = 1);
	



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


class keypoint_t : Moveable<keypoint_t> {
	
public:
	int x = 0;
	int y = 0;
	int score = 0;
	int level = 0;
	double angle = -1.0;
	
	keypoint_t() {}
	keypoint_t(const keypoint_t& s) {*this = s;}
	keypoint_t(int x, int y) : x(x), y(y) {}
	keypoint_t(int x, int y, int score, int level, double angle) {
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
	
	void operator=(const keypoint_t& s) {
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
	
	bool operator()(const keypoint_t& a, const keypoint_t& b) const {
		return a.score > b.score;
	}
	
};


NAMESPACE_TOPSIDE_END

#endif

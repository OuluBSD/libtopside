#ifndef _ComputerVision_Struct_h_
#define _ComputerVision_Struct_h_

NAMESPACE_TOPSIDE_BEGIN


struct ScorePoint : Moveable<ScorePoint> {
	int x, y;
	float score;
	
};


template <class T>
class data_t {
	
public:
	Vector<T> data;

	data_t() {}
};

template <class T>
class matrix_t {
	
public:
	typedef T type;
	Vector<T> data;
	int cols;
	int rows;
	int channels;
	
    // columns, rows, channel
    matrix_t(int c, int r, int ch) {
        ASSERT(c > 0 && r > 0 && ch > 0);
        this->cols = c;
        this->rows = r;
        this->channels = ch;
    }
    matrix_t(int c, int r, int ch, const Vector<T>& data) {
        ASSERT(c > 0 && r > 0 && ch > 0);
        this->cols = c;
        this->rows = r;
        this->channels = ch;
        this.data <<= data;
    }
    
    void allocate() {
        data.SetCount(cols * rows * channels);
    }
    
    void copy_to(matrix_t& other) const {
        ASSERT(other.cols == cols);
        ASSERT(other.rows == rows);
        ASSERT(other.channels == channels);
        other.data <<= data;
    }
    
    void resize(int c, int r, int ch) {
        this->cols = c;
        this->rows = r;
        this->channels = ch;
        allocate();
    }
	
};

using ByteMat = matrix_t<byte>;
using FloatMat = matrix_t<float>;




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
Vector<BBox> group_rectangles(const Vector<BBox>& rects, int min_neighbors = 1);
	




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
	
	keypoint_t(int x, int y, int score, int level, double angle) {
		this->x = x;
		this->y = y;
		this->score = score;
		this->level = level;
		this->angle = angle;
	}
	
	void Clear() {
		x = 0;
		y = 0;
		score = 0;
		level = 0;
		angle = -1.0f;
	}
	
};


NAMESPACE_TOPSIDE_END

#endif

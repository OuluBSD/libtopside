#ifndef _ComputerVision_Struct_h_
#define _ComputerVision_Struct_h_

NAMESPACE_TOPSIDE_BEGIN


// implementation from CCV project
// currently working only with u8,s32,f32
/*enum {
	U8_t = 0x0100,
    S32_t = 0x0200,
    F32_t = 0x0400,
    S64_t = 0x0800,
    F64_t = 0x1000
};

enum {
	C1_t = 0x01,
    C2_t = 0x02,
    C3_t = 0x03,
    C4_t = 0x04
};

extern const int _data_type_size[];


int get_data_type();
int get_channel();
int get_data_type_size();


// data types
global.U8_t = U8_t;
global.S32_t = S32_t;
global.F32_t = F32_t;
global.S64_t = S64_t;
global.F64_t = F64_t;
// data channels
global.C1_t = C1_t;
global.C2_t = C2_t;
global.C3_t = C3_t;
global.C4_t = C4_t;

// popular formats
global.U8C1_t = U8_t | C1_t;
global.U8C3_t = U8_t | C3_t;
global.U8C4_t = U8_t | C4_t;

global.F32C1_t = F32_t | C1_t;
global.F32C2_t = F32_t | C2_t;
global.S32C1_t = S32_t | C1_t;
global.S32C2_t = S32_t | C2_t;


int get_data_type() {
    return type & 0xFF00;
}

int get_channel() {
    return (type & 0xFF);
}

int get_data_type_size() {
    return _data_type_size[(type & 0xFF00) >> 8];
}

*/



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
using FloatMat = matrix_t<double>;




struct BBox : Moveable<BBox> {
	double x;
	double y;
	double width;
	double height;
	
};
	




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

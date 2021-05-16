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


*/

/*const int _data_type_size[] = {-1, 1, 4, -1, 4, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, 8};


int get_data_type() {
    return type & 0xFF00;
}

int get_channel() {
    return (type & 0xFF);
}

int get_data_type_size() {
    return _data_type_size[(type & 0xFF00) >> 8];
}


template <class T>
struct data_t {
	Vector<T> data;

	data_t() {}
};

template <class T>
struct matrix_t {
    // columns, rows, channel
    matrix_t(int c, int r, int ch, data_buffer) {
        this->type = get_data_type(data_type);
        this->channel = get_channel(data_type);
        this->cols = c;
        this->rows = r;
        if (typeof data_buffer === "undefined") {
            this->allocate();
        } else {
            this->buffer = data_buffer;
            // data user asked for
            this->data = this->type&U8_t ? this->buffer.u8 : (this->type&S32_t ? this->buffer.i32 : (this->type&F32_t ? this->buffer.f32 : this->buffer.f64));
        }
    }
    matrix_t.prototype.allocate() {
        // clear references
        delete this->data;
        delete this->buffer;
        //
        this->buffer = new data_t((this->cols * get_data_type_size(this->type) * this->channel) * this->rows);
        this->data = this->type&U8_t ? this->buffer.u8 : (this->type&S32_t ? this->buffer.i32 : (this->type&F32_t ? this->buffer.f32 : this->buffer.f64));
    }
    matrix_t.prototype.copy_to(other) {
        var od = other.data, td = this->data;
        var i = 0, n = (this->cols*this->rows*this->channel);
        for(; i < n-4; i+=4) {
            od[i] = td[i];
            od[i+1] = td[i+1];
            od[i+2] = td[i+2];
            od[i+3] = td[i+3];
        }
        for(; i < n; ++i) {
            od[i] = td[i];
        }
    }
    matrix_t.prototype.resize(c, r, ch) {
        if (typeof ch === "undefined") { ch = this->channel; }
        // relocate buffer only if new size doesnt fit
        var new_size = (c * get_data_type_size(this->type) * ch) * r;
        if(new_size > this->buffer.size) {
            this->cols = c;
            this->rows = r;
            this->channel = ch;
            this->allocate();
        } else {
            this->cols = c;
            this->rows = r;
            this->channel = ch;
        }
    }

    return matrix_t;
})();
*/





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


struct keypoint_t {
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

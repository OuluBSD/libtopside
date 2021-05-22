#ifndef _Local_Version_h_
#define _Local_Version_h_

NAMESPACE_TOPSIDE_BEGIN


// Class for transforming already stored floats to doubles
#define FLOAT__ COMBINE(flo, at)
#define FLOATTRANS COMBINE(Float, Trans)
struct FLOATTRANS : Moveable<FLOATTRANS> {
	double value;
	
	FLOATTRANS() {value = 0;}
	FLOATTRANS(double d) {value = d;}
	void Serialize(Stream& s) {
		if (s.IsLoading()) {
			FLOAT__ f;
			s % f;
			value = f;
		}
		else {
			s % value;
		}
	}
	
	double operator=(double d) {value = d; return d;}
	double operator+=(double d) {value += d; return d;}
	double operator-=(double d) {value -= d; return d;}
	double operator*=(double d) {value *= d; return d;}
	double operator/=(double d) {value /= d; return d;}
	bool operator==(double d) {return value == d;}
	bool operator!=(double d) {return value != d;}
	operator double() const {return value;}
	operator Value() const {return value;}
	String ToString() const {return DblStr(value);}
};







// Version control for persistent binary files
struct Version {
	byte write_v = 0, read_v = 0;
	Stream& s;
	
	Version(byte write_v, Stream& s) : write_v(write_v), s(s) {
		if (s.IsStoring())
			s.Put(&write_v, sizeof(write_v));
		else
			s.Get(&read_v, sizeof(read_v));
	}
	
	bool Is(byte cmp_v) {
		if (s.IsStoring())
			return cmp_v <= write_v;
		else
			return cmp_v <= read_v;
	}
};

#define VER(x) Version v(x, s)
#define FOR_VER(x) if (v.Is(x))


NAMESPACE_TOPSIDE_END

#endif

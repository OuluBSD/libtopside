#ifndef _Local_Coordinate_h_
#define _Local_Coordinate_h_

NAMESPACE_TOPSIDE_BEGIN

typedef double DD;

struct DMS : Moveable<DMS> {
	int16 deg;
	uint8 min;
	double sec;
	
	void operator=(const DD& v) {
		double f = v;
		deg = (int16)f;
		f = fmod(fabs(f), 1) * 60;
		min = (uint8)f;
		f = fmod(f, 1) * 60;
		sec = f;
	}
	
	operator DD() {
		double f = 0;
		f = (double)sec / 3600.0 +
			(double)min / 60.0 +
			(double)deg;
		return f;
	}
	
	void Reset() {deg = 0, min = 0, sec = 0;}
};

struct CoordinateDD : Moveable<CoordinateDD> {
	DD x, y;
	
	CoordinateDD() : x(0), y(0) {}
	CoordinateDD(double y, double x) {this->x = x; this->y = y;}
	
	String ToString() const {
		String s;
		s << DblStr(fabs(y));
		if (y >= 0) s << " N ";
		else s << " S ";
		s << DblStr(fabs(x));
		if (x >= 0) s << " E";
		else s << " W";
		return s;
	}
};

struct CoordinateDMS : Moveable<CoordinateDMS> {
	DMS x, y;
	
	CoordinateDMS() {x.Reset(); y.Reset();}
	CoordinateDMS(const CoordinateDD& dd) {*this = dd;}
	CoordinateDMS(double y, double x) {*this = CoordinateDD(y, x);}
	
	void operator=(const CoordinateDD& dd) {
		x = dd.x;
		y = dd.y;
	}
	String ToString() const {
		//  DDD° MM' SS.S"
		return
			IntStr(abs(y.deg)) + "° " + IntStr(y.min) + "' " + DblStr(y.sec) + "\" " +
			(y.deg >= 0 ? "N " : "S ") +
			IntStr(abs(x.deg)) + "° " + IntStr(x.min) + "' " + DblStr(x.sec) + "\" " +
			(x.deg >= 0 ? "E" : "W");
	}
};

typedef CoordinateDD Coordinate;


NAMESPACE_TOPSIDE_END

#endif

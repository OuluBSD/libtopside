#ifndef _LittleCore_Object_h_
#define _LittleCore_Object_h_


struct Object {
	typedef enum : unsigned char {
		O_EMPTY,
		O_STRING,
		O_INT32,
		O_DOUBLE
	} Type;
	Type type;
	KString str;
	int32 i32 = 0;
	double dbl = 0;
	
	
	Object() {type = O_EMPTY;}
	Object(const KString& s) {str = s; type = O_STRING;}
	Object(int32 i) {i32 = i; type = O_INT32;}
	Object(double d) {dbl = d; type = O_DOUBLE;}
	Object(const Object& o);
	Object(Object&& o);
	
};

#endif

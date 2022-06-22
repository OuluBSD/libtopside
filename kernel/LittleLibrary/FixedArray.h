#ifndef _LittleLibrary_FixedArray_h_
#define _LittleLibrary_FixedArray_h_



template <class T, unsigned N> struct FixedArray {
	T array[N];
public:
	int GetCount() {return N;}
	
	T& operator [] (int i) {return array[i];}
	
	bool IsNull(int i) {return array[i] == 0;}
};

#endif

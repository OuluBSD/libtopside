#ifndef _LittleKernel_OrderedArray_h_
#define _LittleKernel_OrderedArray_h_

#include "Common.h"

uint32 KMemoryAllocateProxy(uint32 size);

template <class T> class OrderedArray {
	uint32 size, max_size;
	T** array;
	
	bool LessThan(T& a, T& b) {return (uint32)&a < (uint32)&b;}
public:
	OrderedArray& Create(uint32 max_size) {
		// KMemoryAllocate is not working when initializing heap
		array = (T**)KMemoryAllocateProxy(max_size * sizeof(T*));
	    memset(array, 0, max_size * sizeof(T*));
	    size = 0;
	    max_size = max_size;
	    return *this;
	}

	OrderedArray& Place(void* addr, uint32 max_size) {
		array = (T**)addr;
	    //memset(array, 0, max_size * sizeof(T));
	    memset(array, 0, max_size * sizeof(T*));
	    size = 0;
	    max_size = max_size;
	    return *this;
	}
	
	void Destroy();
	
	T& Insert(T& item) {
		//ASSERT(array->less_than);
	    uint32 iterator = 0;
	    while (iterator < size && LessThan(*array[iterator], item))
	        iterator++;
	    if (iterator == size) // just add at the end of the array.
	        array[size++] = &item;
	    else
	    {
	        T* tmp = array[iterator];
	        array[iterator] = &item;
	        while (iterator < size)
	        {
	            iterator++;
	            T* tmp2 = array[iterator];
	            array[iterator] = tmp;
	            tmp = tmp2;
	        }
	        size++;
	    }
		return item;
	}

	T& operator [] (uint32 i) {
		ASSERT(i < size);
	    return *array[i];
	}
	
	void Remove(uint32 i) {
		while (i < size) {
	        array[i] = array[i+1];
	        i++;
	    }
	    size--;
	}
	
	uint32 GetSize() {return size;}
};



#endif

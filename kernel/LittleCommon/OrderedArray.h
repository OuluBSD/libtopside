#ifndef _LittleKernel_OrderedArray_h_
#define _LittleKernel_OrderedArray_h_


size_t KMemoryAllocateProxy(size_t size);

template <class T> class OrderedArray {
	size_t size, max_size;
	T** array = 0;
	
	bool LessThan(T& a, T& b) {return (size_t)&a < (size_t)&b;}
public:
	OrderedArray& Create(size_t max_size) {
		// KMemoryAllocate is not working when initializing heap
		array = (T**)KMemoryAllocateProxy(max_size * sizeof(T*));
	    memset(array, 0, max_size * sizeof(T*));
	    size = 0;
	    max_size = max_size;
	    return *this;
	}

	OrderedArray& Place(void* addr, size_t max_size) {
		array = (T**)addr;
	    memset(array, 0, max_size * sizeof(T*));
	    size = 0;
	    max_size = max_size;
	    return *this;
	}
	
	void Destroy();
	
	T& Insert(T& item) {
		//ASSERT(array->less_than);
	    size_t iterator = 0;
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

	T& operator [] (size_t i) {
		ASSERT(i < size);
	    return *array[i];
	}
	
	void Remove(size_t i) {
		while (i < size) {
	        array[i] = array[i+1];
	        i++;
	    }
	    size--;
	}
	
	size_t GetSize() {return size;}
};



#endif

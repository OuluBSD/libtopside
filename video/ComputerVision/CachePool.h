#ifndef _ComputerVision_CachePool_h_
#define _ComputerVision_CachePool_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


struct _pool_node_t {
	_pool_node_t* next;
	
	#ifdef flagDEBUG
	// safe, but memory hungry
	
	Vector<int> i32;
	Vector<float> f32;
	Vector<double> f64;
	Vector<byte> u8;
	int size;
	
	_pool_node_t(int size) {
	    next = 0;
	    resize(size);
	}
	void resize(int size) {
	    f64.SetCount(size / 8);
	    i32.SetCount(size / 4);
	    f32.SetCount(size / 4);
	    u8.SetCount(size);
	    this->size = size;
	}
	
	#else
	// memory efficient, but no memory-range checks
	Vector<byte> data;
	union {
		byte* u8;
		int* i32;
		float* f32;
		double* f64;
	};
	int size;
	
	_pool_node_t(int size) {
	    next = 0;
	    resize(size);
	}
	void resize(int size) {
		data.SetCount(size);
	    u8 = data.Begin();
	    this->size = size;
	}
	
	#endif
	
};


class Cache {
	
public:
	
	
private:
	_pool_node_t* _pool_head = 0;
	_pool_node_t* _pool_tail = 0;
	int _pool_size = 0;
	
	
public:

	Cache() {
		allocate(30, 640*4);
	}
	
	~Cache() {
		Clear();
	}
	
	void Clear() {
		_pool_node_t* it = _pool_head;
		while (it) {
			_pool_node_t* next = it->next;
			delete it;
			it = next;
		}
	}
	
	void allocate(int capacity, int data_size) {
		_pool_head = _pool_tail = new _pool_node_t(data_size);
		for (int i = 0; i < capacity; ++i) {
			_pool_tail = _pool_tail->next = new _pool_node_t(data_size);
			_pool_size++;
		}
	}
	
	_pool_node_t* get_buffer(int size) {
		ASSERT(_pool_head);
		if (!_pool_head) Panic("cache depleted");
		
		_pool_node_t* node = _pool_head;
		_pool_head = _pool_head->next;
		_pool_size--;
		
		if (size > node->size) {
			node->resize(size);
		}
		
		return node;
	}
	
	void put_buffer(_pool_node_t* node) {
		_pool_tail = _pool_tail->next = node;
		_pool_size++;
	}
	
	
	static Cache& Local() {thread_local static Cache c; return c;}
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif

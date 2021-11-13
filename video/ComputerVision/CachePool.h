#ifndef _ComputerVision_CachePool_h_
#define _ComputerVision_CachePool_h_


NAMESPACE_TOPSIDE_BEGIN


class Cache {
	
public:
	
	struct _pool_node_t {
		_pool_node_t* next;
		Vector<int> i32;
		Vector<float> f32;
		int size;
		
		_pool_node_t(int size) {
		    next = 0;
		    i32.SetCount(size);
		    f32.SetCount(size);
		    this->size = size;
		}
		void resize(int size) {
		    i32.SetCount(size);
		    f32.SetCount(size);
		    this->size = size;
		}
		
	};
	
	
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

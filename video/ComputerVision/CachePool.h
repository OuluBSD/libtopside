#ifndef _ComputerVision_CachePool_h_
#define _ComputerVision_CachePool_h_


NAMESPACE_TOPSIDE_BEGIN


class cache {
	int _pool_head;
	int _pool_tail;
	int _pool_size = 0;
	
	
public:

	cache() {
		allocate(30, 640*4);
	}
	
	// very primitive array cache, still need testing if it helps
	// of course V8 has its own powerful cache sys but i'm not sure
	// it caches several multichannel 640x480 buffer creations each frame
	
	struct _pool_node_t {
		/*_pool_node_t(int size_in_bytes) {
		    this->next = null;
		    this->data = new data_t(size_in_bytes);
		    this->size = this->data.size;
		    this->buffer = this->data.buffer;
		    this->u8 = this->data.u8;
		    this->i32 = this->data.i32;
		    this->f32 = this->data.f32;
		    this->f64 = this->data.f64;
		}
		_pool_node_t.prototype.resize(size_in_bytes) {
		    delete this->data;
		    this->data = new data_t(size_in_bytes);
		    this->size = this->data.size;
		    this->buffer = this->data.buffer;
		    this->u8 = this->data.u8;
		    this->i32 = this->data.i32;
		    this->f32 = this->data.f32;
		    this->f64 = this->data.f64;
		}*/
		
	};
	
	void allocate(int capacity, int data_size) {
		_pool_head = _pool_tail = new _pool_node_t(data_size);
		for (int i = 0; i < capacity; ++i) {
			_pool_tail = _pool_tail.next = new _pool_node_t(data_size);
			_pool_size++;
		}
	},
	
	_pool_node_t* get_buffer(int size_in_bytes) {
		// assume we have enough free nodes
		_pool_node_t* node = _pool_head;
		_pool_head = _pool_head.next;
		_pool_size--;
		
		if (size_in_bytes > node.size) {
			node.resize(size_in_bytes);
		}
		
		return node;
	},
	
	void put_buffer(node) {
		_pool_tail = _pool_tail.next = node;
		_pool_size++;
	}
	
};


NAMESPACE_TOPSIDE_END

#endif

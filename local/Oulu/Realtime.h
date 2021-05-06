#ifndef _Oulu_Realtime_h_
#define _Oulu_Realtime_h_


NAMESPACE_OULU_BEGIN


class RealtimeStream {
	
public:
	
	virtual ~RealtimeStream() {}
	
	virtual double GetSeconds() const = 0;
	
	virtual String GetLastError() const {return String();}
	
};


template <class T>
class RealtimePacketBuffer {
	static const int BUFFER_COUNT = 2;
	static const int PACKET_LIMIT = 1024;
	
	RWMutex lock;
	LinkedList<T> packets[BUFFER_COUNT];
	int data_i = 0;
	int queue_size = 0;
	int size_limit = 0;
	
	
public:
	RealtimePacketBuffer() {}
	
	void Dump() {
		LOG("RealtimePacketBuffer: active buf: " << data_i);
		for(int i = 0; i < BUFFER_COUNT; i++) {
			LinkedList<T>& l = packets[i];
			auto iter = l.begin();
			int j = 0;
			for(; iter; ++iter, ++j) {
				LOG("RealtimePacketBuffer: " << i << ": " << j << ": " << iter()->GetOffset().ToString());
			}
		}
	}
	void Clear() {
		lock.EnterWrite();
		for(int i = 0; i < BUFFER_COUNT; i++)
			packets[i].Clear();
		data_i = 0;
		queue_size = 0;
		size_limit = 0;
		lock.LeaveWrite();
	}
	void RemoveFirst(int count=1) {
		lock.EnterWrite();
		count = min(count, queue_size);
		packets[data_i].RemoveFirst(count);
		queue_size -= count;
		lock.LeaveWrite();
	}
	
	void		SetLimit(int i) {size_limit = i;}
	
	int			GetQueueSize() const {return queue_size;}
	bool		IsQueueFull() const {return queue_size >= size_limit;}
	
	off32 GetOffset() const {
		LinkedList<T>& l = const_cast<LinkedList<T>&>(packets[data_i]);
		return l.IsEmpty() ? off32() : (*l.begin())->GetOffset();
	}
	
	T Get(off32 offset) {
		lock.EnterRead();
		ASSERT(data_i >= 0 && data_i < BUFFER_COUNT);
		LinkedList<T>& l = packets[data_i];
		if (l.IsEmpty())
			return T();
		
		// Find given offset frame
		auto iter = l.begin();
		bool found = false;
		while (iter) {
			off32 iter_offset = iter()->GetOffset();
			if (iter_offset == offset) {
				found = true;
				break;
			}
			++iter;
		}
		if (!found)
			return T();
		
		T p = iter();
		lock.LeaveRead();
		
		return p;
	}
	
	void Put(const T& p, bool realtime) {
		lock.EnterWrite();
		if (realtime) {
			packets[data_i].Clear();
			data_i = (data_i + 1) % BUFFER_COUNT;
			LinkedList<T>& l = packets[data_i];
			ASSERT(l.IsEmpty());
			l.Add(p);
			queue_size = 1;
			ASSERT(size_limit > 0);
		}
		else {
			ASSERT(queue_size < size_limit);
			LinkedList<T>& l = packets[data_i];
			l.Add(p);
			++queue_size;
		}
		lock.LeaveWrite();
	}
	
};

NAMESPACE_OULU_END


#endif

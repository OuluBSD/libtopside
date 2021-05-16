#ifndef _Local_Realtime_h_
#define _Local_Realtime_h_


NAMESPACE_TOPSIDE_BEGIN


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
		size_limit = 0;
		lock.LeaveWrite();
	}
	void RemoveFirst(int count=1) {
		lock.EnterWrite();
		count = min(count, packets[data_i].GetCount());
		AUDIOLOG("RealtimePacketBuffer::RemoveFirst: " << IntStr(count));
		packets[data_i].RemoveFirst(count);
		lock.LeaveWrite();
	}
	
	void		SetLimit(int i) {size_limit = i;}
	
	int			GetQueueSize() const {return packets[data_i].GetCount();}
	bool		IsQueueFull() const {return packets[data_i].GetCount() >= size_limit;}
	bool		IsEmpty() const {return packets[data_i].IsEmpty();}
	
	int GetQueueSizeBytes() const {
		int sz = 0;
		for (auto iter = packets[data_i].begin(); iter; ++iter)
			sz += iter()->GetSizeBytes();
		return sz;
	}
	
	off32 GetOffset() const {
		LinkedList<T>& l = const_cast<LinkedList<T>&>(packets[data_i]);
		return l.IsEmpty() ? off32() : (*l.begin())->GetOffset();
	}
	
	T Get(off32 offset) {
		lock.EnterRead();
		ASSERT(data_i >= 0 && data_i < BUFFER_COUNT);
		LinkedList<T>& l = packets[data_i];
		if (l.IsEmpty()) {
			lock.LeaveRead();
			return T();
		}
		
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
		if (!found) {
			lock.LeaveRead();
			return T();
		}
		
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
			ASSERT(size_limit > 0);
		}
		else {
			LinkedList<T>& l = packets[data_i];
			l.Add(p);
		}
		lock.LeaveWrite();
	}
	
};

NAMESPACE_TOPSIDE_END


#endif

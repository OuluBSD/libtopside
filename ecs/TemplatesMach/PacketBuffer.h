#ifndef _TemplatesMach_PacketBuffer_h_
#define _TemplatesMach_PacketBuffer_h_

NAMESPACE_TOPSIDE_BEGIN



template <class T>
class RealtimePacketBuffer {
	static const int BUFFER_COUNT = 2;
	static const int SAMPLE_LIMIT = 3 * T::Class::def_sample_rate; // large default
	
	RWMutex lock;
	LinkedList<T> packets[BUFFER_COUNT];
	int data_i = 0;
	int sample_limit = SAMPLE_LIMIT;
	
	
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
		sample_limit = SAMPLE_LIMIT;
		lock.LeaveWrite();
	}
	void RemoveFirst(int count=1) {
		lock.EnterWrite();
		count = min(count, packets[data_i].GetCount());
		RTLOG("RealtimePacketBuffer::RemoveFirst: " << IntStr(count));
		packets[data_i].RemoveFirst(count);
		lock.LeaveWrite();
	}
	
	void		SetLimit(int samples) {ASSERT(samples > 0); sample_limit = samples;}
	
	int			GetQueueSize() const {return packets[data_i].GetCount();}
	int			GetQueueTotalSamples() const {int bytes = 0; for (auto& p : packets[data_i]) bytes += p->GetSizeTotalSamples(); return bytes;}
	int			GetQueueChannelSamples() const {int bytes = 0; for (auto& p : packets[data_i]) bytes += p->GetSizeChannelSamples(); return bytes;}
	bool		IsQueueFull() const {
		int sz = GetQueueChannelSamples();
		return sz >= sample_limit;
	}
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
			ASSERT(sample_limit > 0);
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
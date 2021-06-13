#ifndef _TemplatesMach_PacketBuffer_h_
#define _TemplatesMach_PacketBuffer_h_

NAMESPACE_TOPSIDE_BEGIN


struct TrackerInfo {
	const RTTI* handler_cls = 0;
	const char* handler_fn = 0;
	const char* file = 0;
	int line = 0;
	
	TrackerInfo() {}
	TrackerInfo(const TrackerInfo& i) {*this = i;}
	TrackerInfo(const RTTI& o) {handler_cls = &o;}
	template <class T> TrackerInfo(const T* o) {handler_cls = &o->GetRTTI();}
	template <class T> TrackerInfo(const T* o, const char* file, int line) : handler_cls(&o->GetRTTI()), file(file), line(line) {}
	TrackerInfo(const char* fn, const char* file, int line) : handler_fn(fn), file(file), line(line) {}
	
	void operator=(const TrackerInfo& i) {
		handler_cls = i.handler_cls;
		handler_fn = i.handler_fn;
		file = i.file;
		line = i.line;
	}
	
	
	String ToString() const;
};



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
		if (l.IsEmpty()) THROW(Exc("RealtimePacketBuffer: empty buffer"));
		return (*l.begin())->GetOffset();
	}
	
	T Pick() {
		lock.EnterWrite();
		ASSERT(data_i >= 0 && data_i < BUFFER_COUNT);
		LinkedList<T>& l = packets[data_i];
		if (l.IsEmpty()) {
			lock.LeaveWrite();
			return T();
		}
		auto iter = l.begin();
		T p = iter();
		l.RemoveFirst(1);
		lock.LeaveWrite();
		
		return p;
	}
	
	T Get() {
		lock.EnterRead();
		ASSERT(data_i >= 0 && data_i < BUFFER_COUNT);
		LinkedList<T>& l = packets[data_i];
		if (l.IsEmpty()) {
			lock.LeaveRead();
			return T();
		}
		auto iter = l.begin();
		T p = iter();
		lock.LeaveRead();
		
		return p;
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

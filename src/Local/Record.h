#ifndef _Local_Record_h_
#define _Local_Record_h_

NAMESPACE_TOPSIDE_BEGIN
class Record;
NAMESPACE_TOPSIDE_END



NAMESPACE_TOPSIDE_BEGIN
using namespace UPP;



class RecordBuffer : NoCopy {
	int rate;
	int length;
	int channels;
	Vector<Vector<float> > data;
	
public:
	
	RecordBuffer() {Clear();}
	
	void Clear() {rate = 0; length = 0; channels = 0;}
	
	int GetSampleRate() const {return rate;}
	float Get(int ch, int i) const {return data[ch][i];}
	int GetCount() const {return length;}
	int GetChannels() const {return channels;}
	
};

class Record :
	public ValueType< Record, UNKNOWN_V, Moveable_<Record> >
{
private:
	struct Data {
		Atomic refcount;

		void   Retain()  { ++refcount; }
		void   Release() { if(--refcount == 0) delete this; }
		
		RecordBuffer buffer;

		Data() {}
	};
	Data* data = 0;
	
public:
	
	Record();
	Record(const Record& r);
	
	
	void operator=(const Record& r);
	
	void Clear();
	void SetData(FFT1& fft, int ch, int pos, int count);
	
	int GetSampleRate() const;
	float Get(int ch, int i) const;
	int GetCount() const;
	int GetChannels() const;
	bool IsEmpty() const;
	
	operator bool() const {return !IsEmpty();}
	
};


class StreamRecord {
	
	
public:
	
	
	
	static Record LoadAny(String path);
	
};

NAMESPACE_TOPSIDE_END




#endif

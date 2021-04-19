#ifndef _Oulu_Sound_h_
#define _Oulu_Sound_h_

NAMESPACE_OULU_BEGIN

struct SoundFormat {
	int var_size = 0;
	int sample_rate = 0;
	int channels = 0;
	int freq = 0;
	bool is_var_float = 0;
	
	bool IsValid() const {return var_size > 0 && sample_rate > 0 && channels > 0 && freq > 0;}
	void Clear() {memset(this, 0, sizeof(SoundFormat));}
	
	bool operator!=(const SoundFormat& fmt) const {return !(*this == fmt);}
	bool operator==(const SoundFormat& fmt) const {
		return	var_size		== fmt.var_size &&
				sample_rate		== fmt.sample_rate &&
				channels		== fmt.channels &&
				freq			== fmt.freq &&
				is_var_float	== fmt.is_var_float;
	}
	
	int GetFrameBytes() const {return var_size * sample_rate * channels;}
	
};

class Sound {
	
public:
	Sound() = default;
	virtual ~Sound() = default;
	
	virtual void Get(void* v, int size) = 0;
	virtual void Put(void* v, int size, bool realtime) = 0;
	virtual int GetQueueSize() const = 0;
	virtual SoundFormat GetFormat() const = 0;
	virtual bool IsQueueFull() const = 0;
	virtual dword GetWriteFrame() const = 0;
#ifdef flagOPENGL
	virtual bool PaintOpenGLTexture(int texture) {return false;}
#endif
	
};


class SoundProxy : public Sound {
	Sound* snd = 0;
	
public:
	SoundProxy() = default;
	SoundProxy(Sound* snd) : snd(snd) {}
	
	void Set(Sound* snd) {this->snd = snd;}
	
	void Get(void* v, int size) override {if (snd) snd->Get(v, size);}
	void Put(void* v, int size, bool realtime) override {if (snd) snd->Put(v, size, realtime);}
	int GetQueueSize() const override {if (snd) return snd->GetQueueSize(); return 0;}
	SoundFormat GetFormat() const override {if (snd) return snd->GetFormat(); return SoundFormat();}
	bool IsQueueFull() const override {if (snd) return snd->IsQueueFull(); return 0;}
	dword GetWriteFrame() const override {if (snd) return snd->GetWriteFrame(); return 0;}
	
};


class VolatileSoundBuffer : public Sound {
	// Settings
	SoundFormat snd_fmt;
	int frames = 0;
	int frame_size = 0;
	SpinLock lock;
	
	// Runtime values
	Vector<byte> data[2];
	int data_i = 0, read_pos = 0, write_pos = 0, queue_size = 0;
	dword write_frame = 0;
	
	#ifdef flagDEBUG
	int size_limit = 10*1024*1024;
	#endif
	
	bool CheckSize(int size);
	
public:
	
	VolatileSoundBuffer() = default;
	
	void SetSize(SoundFormat snd_fmt, int frames=2);
	void Clear();
	void Zero();
	
	byte* GetActiveMem() {return data[data_i].Begin();}
	const byte* GetActiveMem() const {return data[data_i].Begin();}
	int GetMemSize() const {return data[0].GetCount();}
	bool IsEmpty() const {return data[0].IsEmpty();}
	
	void Get(void* v, int size) override;
	void Put(void* v, int size, bool realtime) override;
	int GetQueueSize() const override {return queue_size * snd_fmt.sample_rate;}
	SoundFormat GetFormat() const override {return snd_fmt;}
	bool IsQueueFull() const override {return queue_size >= frames;}
	dword GetWriteFrame() const override {return write_frame;}
	
	#ifdef flagDEBUG
	void SetSizeLimit(int l) {size_limit = l;}
	#else
	void SetSizeLimit(int l) {}
	#endif
	
};


void SoundBufferUnitTest();


NAMESPACE_OULU_END

#endif

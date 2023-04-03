#ifndef _AudioCore_Audio_h_
#define _AudioCore_Audio_h_


NAMESPACE_AUDIO_BEGIN


// TODO: fix use of these compatiblity functions
inline int NotNpos(int i) {
	if (i == std::string::npos || i < 0) return -1;
	return i;
}

inline int NotNpos(size_t i) {
	if (i == std::string::npos) return -1;
	return (int)i;
}

inline int FindFirstOf(const String& str, const String& search, int pos) {
	return NotNpos(std::string(str).find_first_of(search, pos));
}
inline int FindFirstOf(const String& str, int chr, int pos) {
	return NotNpos(std::string(str).find_first_of(chr, pos));
}
inline int FindLastOf(const String& str, const String& search, int pos) {
	return NotNpos(std::string(str).find_last_of(search, pos));
}
inline int FindLastOf(const String& str, int chr, int pos) {
	return NotNpos(std::string(str).find_last_of(chr, pos));
}
inline int FindFirstNotOf(const String& str, const String& search, int pos) {
	return NotNpos(std::string(str).find_first_not_of(search, pos));
}
inline int FindLastNotOf(const String& str, const String& search, int pos) {
	return NotNpos(std::string(str).find_last_not_of(search, pos));
}




class AudioError {
public:
	enum Type {
		STATUS,
		WARNING,
		DEBUG_PRINT,
		MEMORY_ALLOCATION,
		MEMORY_ACCESS,
		FUNCTION_ARGUMENT,
		FILE_NOT_FOUND,
		FILE_UNKNOWN_FORMAT,
		FILE_ERROR,
		PROCESS_THREAD,
		PROCESS_SOCKET,
		PROCESS_SOCKET_IPADDR,
		AUDIO_SYSTEM,
		MIDI_SYSTEM,
		UNSPECIFIED
	};

protected:
	String message_;
	int type_;

public:

	AudioError(const String& message, int type = AudioError::UNSPECIFIED)
		: message_(message), type_(type) {}


	virtual ~AudioError(void) {};

	virtual void printMessage(void) {
		LOG("ERROR: " << message_);
	}

	virtual const int& GetType(void) {
		return type_;
	}

	virtual const String& GetMessage(void) {
		return message_;
	}

	virtual const char* GetMessageCString(void) {
		return message_.Begin();
	}
};


class Audio {
public:

	typedef int AudioFormat;
	static const AudioFormat AUDIO_SINT8;
	static const AudioFormat AUDIO_SINT16;
	static const AudioFormat AUDIO_SINT24;
	static const AudioFormat AUDIO_SINT32;
	static const AudioFormat AUDIO_FLOAT32;
	static const AudioFormat AUDIO_FLOAT64;


	static float GetSampleRate() {
		return srate_;
	}

	static void SetSampleRate( float rate );

	void IgnoreSampleRateChange( bool ignore = true ) {
		IgnoreSampleRateChange_ = ignore;
	};

	static void  ClearAlertList() {
		alertList_.Clear();
	};

	static String GetRawWavePath(void) {
		return RealizeShareFile(rawwavepath_);
	}

	static void SetRawwavePath( String path );
	static void Swap16( unsigned char* ptr );
	static void Swap32( unsigned char* ptr );
	static void Swap64( unsigned char* ptr );
	static void Sleep( int milliseconds );


	static bool InRange( float value, float min, float max ) {
		if ( value < min ) return false;
		else if ( value > max ) return false;
		else return true;
	}

	static void HandleError( int type );
	static void HandleError( const char* message, int type );
	static void HandleError( String message, int type );

	static void ShowWarnings( bool status ) {
		show_warnings_ = status;
	}


	static void printErrors( bool status ) {
		print_errors_ = status;
	}

private:
	static float srate_;
	static String rawwavepath_;
	static bool show_warnings_;
	static bool print_errors_;
	static Vector<Audio*> alertList_;

protected:

	bool IgnoreSampleRateChange_;
	
	Audio();
	virtual ~Audio();
	virtual void SampleRateChanged( float new_rate, float old_rate );
	void AddSampleRateAlert( Audio* ptr );
	void RemoveSampleRateAlert( Audio* ptr );
};






class AudioFrames {
public:
	AudioFrames( int frame_count = 0, int channel_count = 0 );
	AudioFrames( const float& value, int frame_count, int channel_count );
	~AudioFrames();
	AudioFrames( const AudioFrames& f );
	AudioFrames& operator= ( const AudioFrames& f );
	float& operator[] ( size_t n );
	float operator[] ( size_t n ) const;
	AudioFrames operator+(const AudioFrames& frames) const;
	void operator+= ( AudioFrames& f );
	void operator*= ( AudioFrames& f );
	float& operator() ( int frame, int channel );
	float operator() ( int frame, int channel ) const;
	float interpolate( float frame, int channel = 0 ) const;
	
	int GetCount() const {
		return size_;
	};

	bool IsEmpty() const;
	void SetCount( int frame_count, int channel_count = 1 );
	void SetCount( int frame_count, int channel_count, float value );
	AudioFrames& GetChannel(int channel, AudioFrames& dest_frame_count, int dest_chan) const;
	void SetChannel(int channel, const AudioFrames& src_frames, int src_channel);
	
	void Zero() {
		if (data_) memset(data_, 0, size_ * sizeof(float));
	}
	
	int GetChannelCount() const {
		return channel_count_;
	};

	int GetFrameCount() const {
		return (int)frame_count_;
	};

	void SetDataRate( float rate ) {
		dataRate_ = rate;
	};

	float dataRate() const {
		return dataRate_;
	};

private:

	float* data_;
	float dataRate_;
	int frame_count_;
	int channel_count_;
	int size_;
	int bufferSize_;

};

inline bool AudioFrames::IsEmpty() const {
	if ( size_ > 0 ) return false;
	else return true;
}

inline float& AudioFrames::operator[] ( size_t n ) {
	#if defined(flagDEBUG)

	if ( n >= size_ ) {
		
		LOG("AudioFrames::operator[]: invalid index (" << (int)n << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	return data_[n];
}

inline float AudioFrames::operator[] ( size_t n ) const {
	#if defined(flagDEBUG)

	if ( n >= size_ ) {
		
		LOG("AudioFrames::operator[]: invalid index (" << (int)n << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	return data_[n];
}

inline float& AudioFrames::operator() ( int frame, int channel ) {
	#if defined(flagDEBUG)

	if ( frame >= frame_count_ || channel >= channel_count_ ) {
		
		LOG("AudioFrames::operator(): invalid frame (" << (int)frame << ") or channel (" << channel << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	return data_[ frame * channel_count_ + channel ];
}

inline float AudioFrames::operator() ( int frame, int channel ) const {
	#if defined(flagDEBUG)

	if ( frame >= frame_count_ || channel >= channel_count_ ) {
		
		LOG("AudioFrames::operator(): invalid frame (" << (int)frame << ") or channel (" << channel << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	return data_[ frame * channel_count_ + channel ];
}

inline AudioFrames AudioFrames::operator+(const AudioFrames& f) const {
	#if defined(flagDEBUG)

	if ( f.GetFrameCount() != frame_count_ || f.GetChannelCount() != channel_count_ ) {
		
		LOG("AudioFrames::operator+: frames argument must be of equal dimensions!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	AudioFrames sum((int)frame_count_, channel_count_);
	float* sumPtr = &sum[0];
	const float* fptr = f.data_;
	const float* dPtr = data_;

	for (int i = 0; i < size_; i++)
		*sumPtr++ = *fptr++ + *dPtr++;

	return sum;
}

inline void AudioFrames::operator+= ( AudioFrames& f ) {
	#if defined(flagDEBUG)

	if ( f.GetFrameCount() != frame_count_ || f.GetChannelCount() != channel_count_ ) {
		
		LOG("AudioFrames::operator+=: frames argument must be of equal dimensions!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	float* fptr = &f[0];
	float* dptr = data_;

	for ( int i = 0; i < size_; i++ )
		*dptr++ += *fptr++;
}

inline void AudioFrames::operator*= ( AudioFrames& f ) {
	#if defined(flagDEBUG)

	if ( f.GetFrameCount() != frame_count_ || f.GetChannelCount() != channel_count_ ) {
		
		LOG("AudioFrames::operator*=: frames argument must be of equal dimensions!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	float* fptr = &f[0];
	float* dptr = data_;

	for ( int i = 0; i < size_; i++ )
		*dptr++ *= *fptr++;
}


typedef unsigned short UINT16;
typedef int UINT32;
typedef signed short SINT16;
typedef signed int SINT32;
typedef float FLOAT32;
typedef float FLOAT64;


const float SRATE = 44100.0f;

const int RT_BUFFER_SIZE = 512;


#if !defined(RAWWAVE_PATH)
	#define RAWWAVE_PATH "audio/stk/"
#endif

const float PI           = 3.14159265358979f;
const float TWO_PI       = 2.f * PI;
const float ONE_OVER_128 = 0.0078125f;


NAMESPACE_AUDIO_END

#endif

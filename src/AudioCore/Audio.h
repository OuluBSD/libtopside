#ifndef _AudioCore_Audio_h_
#define _AudioCore_Audio_h_


NAMESPACE_AUDIO_BEGIN


// TODO: fix use of these compatiblity functions
inline int NotNpos(int i) {
	if (i == std::string::npos) return -1;

	return i;
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

	typedef unsigned long AudioFormat;
	static const AudioFormat AUDIO_SINT8;
	static const AudioFormat AUDIO_SINT16;
	static const AudioFormat AUDIO_SINT24;
	static const AudioFormat AUDIO_SINT32;
	static const AudioFormat AUDIO_FLOAT32;
	static const AudioFormat AUDIO_FLOAT64;


	static double GetSampleRate() {
		return srate_;
	}

	static void SetSampleRate( double rate );

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
	static void Sleep( unsigned long milliseconds );


	static bool InRange( double value, double min, double max ) {
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
	static double srate_;
	static String rawwavepath_;
	static bool show_warnings_;
	static bool print_errors_;
	static Vector<Audio*> alertList_;

protected:

	bool IgnoreSampleRateChange_;
	
	Audio();
	virtual ~Audio();
	virtual void SampleRateChanged( double new_rate, double old_rate );
	void AddSampleRateAlert( Audio* ptr );
	void RemoveSampleRateAlert( Audio* ptr );
};






class AudioFrames {
public:
	AudioFrames( unsigned int frame_count = 0, unsigned int channel_count = 0 );
	AudioFrames( const double& value, unsigned int frame_count, unsigned int channel_count );
	~AudioFrames();
	AudioFrames( const AudioFrames& f );
	AudioFrames& operator= ( const AudioFrames& f );
	double& operator[] ( size_t n );
	double operator[] ( size_t n ) const;
	AudioFrames operator+(const AudioFrames& frames) const;
	void operator+= ( AudioFrames& f );
	void operator*= ( AudioFrames& f );
	double& operator() ( size_t frame, unsigned int channel );
	double operator() ( size_t frame, unsigned int channel ) const;
	double interpolate( double frame, unsigned int channel = 0 ) const;
	
	size_t GetCount() const {
		return size_;
	};

	bool IsEmpty() const;
	void SetCount( size_t frame_count, unsigned int channel_count = 1 );
	void SetCount( size_t frame_count, unsigned int channel_count, double value );
	AudioFrames& GetChannel(unsigned int channel, AudioFrames& dest_frame_count, unsigned int dest_chan) const;
	void SetChannel(unsigned int channel, const AudioFrames& src_frames, unsigned int src_channel);
	
	void Zero() {
		if (data_) memset(data_, 0, size_ * sizeof(double));
	}
	
	unsigned int GetChannelCount() const {
		return channel_count_;
	};

	unsigned int GetFrameCount() const {
		return (unsigned int)frame_count_;
	};

	void SetDataRate( double rate ) {
		dataRate_ = rate;
	};

	double dataRate() const {
		return dataRate_;
	};

private:

	double* data_;
	double dataRate_;
	size_t frame_count_;
	unsigned int channel_count_;
	size_t size_;
	size_t bufferSize_;

};

inline bool AudioFrames::IsEmpty() const {
	if ( size_ > 0 ) return false;
	else return true;
}

inline double& AudioFrames::operator[] ( size_t n ) {
	#if defined(flagDEBUG)

	if ( n >= size_ ) {
		
		LOG("AudioFrames::operator[]: invalid index (" << (int)n << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	return data_[n];
}

inline double AudioFrames::operator[] ( size_t n ) const {
	#if defined(flagDEBUG)

	if ( n >= size_ ) {
		
		LOG("AudioFrames::operator[]: invalid index (" << (int)n << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	return data_[n];
}

inline double& AudioFrames::operator() ( size_t frame, unsigned int channel ) {
	#if defined(flagDEBUG)

	if ( frame >= frame_count_ || channel >= channel_count_ ) {
		
		LOG("AudioFrames::operator(): invalid frame (" << (int)frame << ") or channel (" << channel << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	return data_[ frame * channel_count_ + channel ];
}

inline double AudioFrames::operator() ( size_t frame, unsigned int channel ) const {
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
	AudioFrames sum((unsigned int)frame_count_, channel_count_);
	double* sumPtr = &sum[0];
	const double* fptr = f.data_;
	const double* dPtr = data_;

	for (unsigned int i = 0; i < size_; i++)
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
	double* fptr = &f[0];
	double* dptr = data_;

	for ( unsigned int i = 0; i < size_; i++ )
		*dptr++ += *fptr++;
}

inline void AudioFrames::operator*= ( AudioFrames& f ) {
	#if defined(flagDEBUG)

	if ( f.GetFrameCount() != frame_count_ || f.GetChannelCount() != channel_count_ ) {
		
		LOG("AudioFrames::operator*=: frames argument must be of equal dimensions!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	double* fptr = &f[0];
	double* dptr = data_;

	for ( unsigned int i = 0; i < size_; i++ )
		*dptr++ *= *fptr++;
}


typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef signed short SINT16;
typedef signed int SINT32;
typedef float FLOAT32;
typedef double FLOAT64;


const double SRATE = 44100.0;

const unsigned int RT_BUFFER_SIZE = 512;


#if !defined(RAWWAVE_PATH)
	#define RAWWAVE_PATH "audio/stk/"
#endif

const double PI           = 3.14159265358979;
const double TWO_PI       = 2 * PI;
const double ONE_OVER_128 = 0.0078125;


NAMESPACE_AUDIO_END

#endif

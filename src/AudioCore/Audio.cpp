#include "AudioCore.h"

NAMESPACE_AUDIO_BEGIN

float Audio::srate_ = (float) SRATE;
String Audio::rawwavepath_ = RAWWAVE_PATH;
const Audio::AudioFormat Audio::AUDIO_SINT8   = 0x1;
const Audio::AudioFormat Audio::AUDIO_SINT16  = 0x2;
const Audio::AudioFormat Audio::AUDIO_SINT24  = 0x4;
const Audio::AudioFormat Audio::AUDIO_SINT32  = 0x8;
const Audio::AudioFormat Audio::AUDIO_FLOAT32 = 0x10;
const Audio::AudioFormat Audio::AUDIO_FLOAT64 = 0x20;
bool Audio::show_warnings_ = true;
bool Audio::print_errors_ = true;
Vector<Audio*> Audio::alertList_;


Audio::Audio()
	: IgnoreSampleRateChange_(false) {
}

Audio::~Audio() {
}

void Audio::SetSampleRate( float rate ) {
	if ( rate > 0.0f && rate != srate_ ) {
		float old_rate = srate_;
		srate_ = rate;

		for ( int i = 0; i < alertList_.GetCount(); i++ )
			alertList_[i]->SampleRateChanged( srate_, old_rate );
	}
}

void Audio::SampleRateChanged( float , float  ) {
}

void Audio::AddSampleRateAlert( Audio* ptr ) {
	for ( int i = 0; i < alertList_.GetCount(); i++ )
		if ( alertList_[i] == ptr ) return;

	alertList_.Add( ptr );
}

void Audio::RemoveSampleRateAlert( Audio* ptr ) {
	for ( int i = 0; i < alertList_.GetCount(); i++ ) {
		if ( alertList_[i] == ptr ) {
			alertList_.Remove( i );
			return;
		}
	}
}

void Audio::SetRawwavePath( String path ) {
	if ( !path.IsEmpty() )
		rawwavepath_ = path;

	if ( rawwavepath_[rawwavepath_.GetCount() - 1] != '/' )
		rawwavepath_ += "/";
}

void Audio::Swap16(unsigned char* ptr) {
	unsigned char val;
	val = *(ptr);
	*(ptr) = *(ptr + 1);
	*(ptr + 1) = val;
}

void Audio::Swap32(unsigned char* ptr) {
	unsigned char val;
	val = *(ptr);
	*(ptr) = *(ptr + 3);
	*(ptr + 3) = val;
	ptr += 1;
	val = *(ptr);
	*(ptr) = *(ptr + 1);
	*(ptr + 1) = val;
}

void Audio::Swap64(unsigned char* ptr) {
	unsigned char val;
	val = *(ptr);
	*(ptr) = *(ptr + 7);
	*(ptr + 7) = val;
	ptr += 1;
	val = *(ptr);
	*(ptr) = *(ptr + 5);
	*(ptr + 5) = val;
	ptr += 1;
	val = *(ptr);
	*(ptr) = *(ptr + 3);
	*(ptr + 3) = val;
	ptr += 1;
	val = *(ptr);
	*(ptr) = *(ptr + 1);
	*(ptr + 1) = val;
}

void Audio::Sleep(int milliseconds) {
	#if defined(__OS_WINDOWS__)
	Sleep((DWORD) milliseconds);
	#elif (defined(__OS_IRIX__) || defined(__OS_LINUX__) || defined(__OS_MACOSX__))
	uSleep( (int) (milliseconds * 1000.0f) );
	#endif
}

void Audio::HandleError( int type ) {
	HandleError( "", type );
}

void Audio::HandleError( const char* message, int type ) {
	String msg( message );
	HandleError( msg, type );
}

void Audio::HandleError( String message, int type ) {
	if ( type == AudioError::WARNING || type == AudioError::STATUS ) {
		if ( !show_warnings_ ) return;

		LOG("WARNING: " << message);
	}
	else if (type == AudioError::DEBUG_PRINT) {
		#if defined(flagDEBUG)
		LOG("ERROR: " << message);
		#endif
	}
	else {
		if ( print_errors_ )
			LOG("ERROR: " << message);

		throw AudioError(message, type);
	}
}





AudioFrames::AudioFrames( int frame_count, int channel_count )
	: data_( 0 ), frame_count_( frame_count ), channel_count_( channel_count ) {
	size_ = frame_count_ * channel_count_;
	bufferSize_ = size_;

	if ( size_ > 0 ) {
		data_ = (float*) calloc( size_, sizeof( float ) );
		#if defined(flagDEBUG)

		if ( data_ == NULL ) {
			LOG("AudioFrames: memory allocation error in constructor!");
			Audio::HandleError( AudioError::MEMORY_ALLOCATION );
		}

		#endif
	}

	dataRate_ = Audio::GetSampleRate();
}

AudioFrames::AudioFrames( const float& value, int frame_count, int channel_count )
	: data_( 0 ), frame_count_( frame_count ), channel_count_( channel_count ) {
	size_ = frame_count_ * channel_count_;
	bufferSize_ = size_;

	if ( size_ > 0 ) {
		data_ = (float*) malloc( size_ * sizeof( float ) );
		#if defined(flagDEBUG)

		if ( data_ == NULL ) {
			LOG("AudioFrames: memory allocation error in constructor!");
			Audio::HandleError( AudioError::MEMORY_ALLOCATION );
		}

		#endif

		for ( long i = 0; i < (long)size_; i++ ) data_[i] = value;
	}

	dataRate_ = Audio::GetSampleRate();
}

AudioFrames::~AudioFrames() {
	if ( data_ ) free( data_ );
}

AudioFrames::AudioFrames( const AudioFrames& f )
	: data_(0), size_(0), bufferSize_(0) {
	SetCount( f.GetFrameCount(), f.GetChannelCount() );
	dataRate_ = Audio::GetSampleRate();

	for ( int i = 0; i < size_; i++ ) data_[i] = f[i];
}

AudioFrames& AudioFrames::operator= ( const AudioFrames& f ) {
	if ( data_ ) free( data_ );

	data_ = 0;
	size_ = 0;
	bufferSize_ = 0;
	SetCount( f.GetFrameCount(), f.GetChannelCount() );
	dataRate_ = Audio::GetSampleRate();

	for ( int i = 0; i < size_; i++ ) data_[i] = f[i];

	return *this;
}

void AudioFrames::SetCount( int frame_count, int channel_count ) {
	frame_count_ = frame_count;
	channel_count_ = channel_count;
	size_ = frame_count_ * channel_count_;

	if ( size_ > bufferSize_ ) {
		if ( data_ ) free( data_ );

		data_ = (float*) malloc( size_ * sizeof( float ) );
		#if defined(flagDEBUG)

		if ( data_ == NULL ) {
			LOG("AudioFrames::SetCount: memory allocation error!");
			Audio::HandleError( AudioError::MEMORY_ALLOCATION );
		}

		#endif
		bufferSize_ = size_;
	}
}

void AudioFrames::SetCount( int frame_count, int channel_count, float value ) {
	this->SetCount( frame_count, channel_count );

	for ( size_t i = 0; i < size_; i++ ) data_[i] = value;
}

AudioFrames& AudioFrames::GetChannel(int src_channel, AudioFrames& dest_frame_count, int dest_chan) const {
	#if defined(flagDEBUG)

	if (src_channel > GetChannelCount() - 1) {
		
		LOG("AudioFrames::GetChannel invalid src_channel (" << src_channel << ")");
		Audio::HandleError(AudioError::FUNCTION_ARGUMENT);
	}

	if (dest_chan > dest_frame_count.GetChannelCount() - 1) {
		
		LOG("AudioFrames::GetChannel invalid dest_chan (" << dest_chan << ")");
		Audio::HandleError(AudioError::FUNCTION_ARGUMENT );
	}

	if (dest_frame_count.GetFrameCount() < GetFrameCount()) {
		
		LOG("AudioFrames::GetChannel destination.GetFrameCount() < GetFrameCount()");
		Audio::HandleError(AudioError::MEMORY_ACCESS);
	}

	#endif
	int sourceHop = channel_count_;
	int destinationHop = dest_frame_count.channel_count_;

	for (int i  = src_channel, j = dest_chan; i < frame_count_ * channel_count_; i += sourceHop, j += destinationHop)
		dest_frame_count[j] = data_[i];

	return dest_frame_count;
}

void AudioFrames::SetChannel(int dest_chan, const AudioFrames& src_frames, int src_channel) {
	#if defined(flagDEBUG)

	if (src_channel > src_frames.GetChannelCount() - 1) {
		
		LOG("AudioFrames::SetChannel invalid src_channel (" << src_channel << ")");
		Audio::HandleError(AudioError::FUNCTION_ARGUMENT);
	}

	if (dest_chan > GetChannelCount() - 1) {
		
		LOG("AudioFrames::SetChannel invalid channel (" << dest_chan << ")");
		Audio::HandleError(AudioError::FUNCTION_ARGUMENT );
	}

	if (src_frames.GetFrameCount() != GetFrameCount()) {
		
		LOG("AudioFrames::SetChannel src_frames.GetFrameCount() != GetFrameCount()");
		Audio::HandleError(AudioError::MEMORY_ACCESS);
	}

	#endif
	int sourceHop = src_frames.channel_count_;
	int destinationHop = channel_count_;

	for (int i  = dest_chan, j = src_channel ; i < frame_count_ * channel_count_; i += destinationHop, j += sourceHop)
		data_[i] = src_frames[j];
}

float AudioFrames::interpolate( float frame, int channel ) const {
	#if defined(flagDEBUG)

	if ( frame < 0.0f || frame > (float) ( frame_count_ - 1 ) || channel >= channel_count_ ) {
		
		LOG("AudioFrames::interpolate: invalid frame (" << frame << ") or channel (" << channel << ") value!");
		Audio::HandleError(AudioError::MEMORY_ACCESS );
	}

	#endif
	size_t iIndex = ( size_t ) frame;
	float output, alpha = frame - (float) iIndex;
	iIndex = iIndex * channel_count_ + channel;
	output = data_[ iIndex ];

	if ( alpha > 0.0f )
		output += ( alpha * ( data_[ iIndex + channel_count_ ] - output ) );

	return output;
}

NAMESPACE_AUDIO_END

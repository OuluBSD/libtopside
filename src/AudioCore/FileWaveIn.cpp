#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FileWaveIn::FileWaveIn( int chunkThreshold, int chunkSize )
	: finished_(true), interpolate_(false), time_(0.0f), rate_(0.0f),
	  chunkThreshold_(chunkThreshold), chunkSize_(chunkSize) {
	Audio::AddSampleRateAlert( this );
}

FileWaveIn::FileWaveIn( String file_name, bool raw, bool doNormalize,
						  int chunkThreshold, int chunkSize )
	: finished_(true), interpolate_(false), time_(0.0f), rate_(0.0f),
	  chunkThreshold_(chunkThreshold), chunkSize_(chunkSize) {
	OpenFile( file_name, raw, doNormalize );
	Audio::AddSampleRateAlert( this );
}

FileWaveIn::~FileWaveIn() {
	this->CloseFile();
	Audio::RemoveSampleRateAlert( this );
}

void FileWaveIn::SampleRateChanged( float new_rate, float old_rate ) {
	if ( !IgnoreSampleRateChange_ )
		this->SetRate( old_rate * rate_ / new_rate );
}

void FileWaveIn::CloseFile() {
	if ( file_.isOpen() ) file_.Close();

	finished_ = true;
	last_frame_.SetCount( 0, 0 );
}

void FileWaveIn::OpenFile( String file_name, bool raw, bool doNormalize ) {
	this->CloseFile();
	file_.Open( file_name, raw );

	if ( file_.fileSize() > chunkThreshold_ ) {
		chunking_ = true;
		chunkPointer_ = 0;
		data_.SetCount( chunkSize_, file_.GetChannelCount() );

		if ( doNormalize ) normalizing_ = true;
		else normalizing_ = false;
	}
	else {
		chunking_ = false;
		data_.SetCount( (size_t) file_.fileSize(), file_.GetChannelCount() );
	}

	file_.Get( data_, 0, doNormalize );
	last_frame_.SetCount( 1, file_.GetChannelCount() );
	fileSize_ = file_.fileSize();

	if ( !chunking_ ) file_.Close();

	this->SetRate( data_.dataRate() / Audio::GetSampleRate() );

	if ( doNormalize & !chunking_ ) this->Normalize();

	this->Reset();
}

void FileWaveIn::Reset(void) {
	time_ = (float) 0.0f;

	for ( int i = 0; i < last_frame_.GetCount(); i++ ) last_frame_[i] = 0.0f;

	finished_ = false;
}

void FileWaveIn::Normalize(void) {
	this->Normalize( 1.0f );
}


void FileWaveIn::Normalize( float peak ) {
	if ( chunking_ ) return;

	int i;
	float max = 0.0f;

	for ( i = 0; i < data_.GetCount(); i++ ) {
		if ( fabs( data_[i] ) > max )
			max = (float) fabs((float) data_[i]);
	}

	if ( max > 0.0f ) {
		max = 1.0f / max;
		max *= peak;

		for ( i = 0; i < data_.GetCount(); i++ )
			data_[i] *= max;
	}
}

void FileWaveIn::SetRate( float rate ) {
	rate_ = rate;

	if ( (rate_ < 0) && (time_ == 0.0f) ) time_ = fileSize_ - 1.0f;

	if ( fmod( rate_, 1.0f ) != 0.0f ) interpolate_ = true;
	else interpolate_ = false;
}

void FileWaveIn::AddTime( float time ) {
	time_ += time;

	if ( time_ < 0.0f ) time_ = 0.0f;

	if ( time_ > fileSize_ - 1.0f ) {
		time_ = fileSize_ - 1.0f;

		for ( int i = 0; i < last_frame_.GetCount(); i++ ) last_frame_[i] = 0.0f;

		finished_ = true;
	}
}

float FileWaveIn::Tick( int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= data_.GetChannelCount() ) {
		LOG("FileWaveIn::Tick(): channel argument and soundfile data are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif

	if ( finished_ ) return 0.0f;

	if ( time_ < 0.0f || time_ > (float) ( fileSize_ - 1.0f ) ) {
		for ( int i = 0; i < last_frame_.GetCount(); i++ ) last_frame_[i] = 0.0f;

		finished_ = true;
		return 0.0f;
	}

	float tyme = time_;

	if ( chunking_ ) {
		if ( ( time_ < (float) chunkPointer_ ) ||
			 ( time_ > (float) ( chunkPointer_ + chunkSize_ - 1 ) ) ) {
			while ( time_ < (float) chunkPointer_ ) {
				chunkPointer_ -= chunkSize_ - 1;

				if ( chunkPointer_ < 0 ) chunkPointer_ = 0;
			}

			while ( time_ > (float) ( chunkPointer_ + chunkSize_ - 1 ) ) {
				chunkPointer_ += chunkSize_ - 1;

				if ( chunkPointer_ + chunkSize_ > fileSize_ )
					chunkPointer_ = fileSize_ - chunkSize_;
			}

			file_.Get( data_, chunkPointer_, normalizing_ );
		}

		tyme -= chunkPointer_;
	}

	if ( interpolate_ ) {
		for ( int i = 0; i < last_frame_.GetCount(); i++ )
			last_frame_[i] = data_.interpolate( tyme, i );
	}
	else {
		for ( int i = 0; i < last_frame_.GetCount(); i++ )
			last_frame_[i] = data_( (size_t) tyme, i );
	}

	time_ += rate_;
	return last_frame_[channel];
}

AudioFrames& FileWaveIn::Tick( AudioFrames& frames, int channel) {
	if ( !file_.isOpen() ) {
		#if defined(flagDEBUG)
		LOG("FileWaveIn::Tick(): no file data is loaded!");
		HandleError( AudioError::DEBUG_PRINT );
		#endif
		return frames;
	}

	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("FileWaveIn::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FileLoop::FileLoop( int chunkThreshold, int chunkSize )
	: FileWaveIn( chunkThreshold, chunkSize ), phase_offset_(0.0f) {
	Audio::AddSampleRateAlert( this );
}

FileLoop::FileLoop( String file_name, bool raw, bool doNormalize,
					  int chunkThreshold, int chunkSize )
	: FileWaveIn( chunkThreshold, chunkSize ), phase_offset_(0.0f) {
	this->OpenFile( file_name, raw, doNormalize );
	Audio::AddSampleRateAlert( this );
}

FileLoop::~FileLoop() {
	Audio::RemoveSampleRateAlert( this );
}

void FileLoop::OpenFile( String file_name, bool raw, bool doNormalize ) {
	this->CloseFile();
	file_.Open( file_name, raw );

	if ( file_.fileSize() > chunkThreshold_ ) {
		chunking_ = true;
		chunkPointer_ = 0;
		data_.SetCount( chunkSize_ + 1, file_.GetChannelCount() );

		if ( doNormalize ) normalizing_ = true;
		else normalizing_ = false;
	}
	else {
		chunking_ = false;
		data_.SetCount( file_.fileSize() + 1, file_.GetChannelCount() );
	}

	file_.Get( data_, 0, doNormalize );

	if ( chunking_ ) {
		first_frame_.SetCount( 1, data_.GetChannelCount() );

		for ( int i = 0; i < data_.GetChannelCount(); i++ )
			first_frame_[i] = data_[i];
	}
	else {
		for ( int i = 0; i < data_.GetChannelCount(); i++ )
			data_( data_.GetFrameCount() - 1, i ) = data_[i];
	}

	last_frame_.SetCount( 1, file_.GetChannelCount() );
	fileSize_ = file_.fileSize();

	if ( !chunking_ ) file_.Close();

	this->SetRate( data_.dataRate() / Audio::GetSampleRate() );

	if ( doNormalize & !chunking_ ) this->Normalize();

	this->Reset();
}

void FileLoop::SetRate( float rate ) {
	rate_ = rate;

	if ( fmod( rate_, 1.0f ) != 0.0f ) interpolate_ = true;
	else interpolate_ = false;
}

void FileLoop::AddTime( float time ) {
	time_ += time;

	while ( time_ < 0.0f )
		time_ += fileSize_;

	while ( time_ >= fileSize_ )
		time_ -= fileSize_;
}

void FileLoop::AddPhase( float angle ) {
	time_ += fileSize_ * angle;

	while ( time_ < 0.0f )
		time_ += fileSize_;

	while ( time_ >= fileSize_ )
		time_ -= fileSize_;
}

void FileLoop::AddPhaseOffset( float angle ) {
	phase_offset_ = fileSize_ * angle;
}

float FileLoop::Tick( int channel ) {
	#if defined(flagDEBUG)

	if ( channel >= data_.GetChannelCount() ) {
		LOG("FileLoop::Tick(): channel argument and soundfile data are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif

	while ( time_ < 0.0f )
		time_ += fileSize_;

	while ( time_ >= fileSize_ )
		time_ -= fileSize_;

	float tyme = time_;

	if ( phase_offset_ ) {
		tyme += phase_offset_;

		while ( tyme < 0.0f )
			tyme += fileSize_;

		while ( tyme >= fileSize_ )
			tyme -= fileSize_;
	}

	if ( chunking_ ) {
		if ( ( time_ < (float) chunkPointer_ ) ||
			 ( time_ > (float) ( chunkPointer_ + chunkSize_ - 1 ) ) ) {
			while ( time_ < (float) chunkPointer_ ) {
				chunkPointer_ -= chunkSize_ - 1;

				if ( chunkPointer_ < 0 ) chunkPointer_ = 0;
			}

			while ( time_ > (float) ( chunkPointer_ + chunkSize_ - 1 ) ) {
				chunkPointer_ += chunkSize_ - 1;

				if ( chunkPointer_ + chunkSize_ > fileSize_ ) {
					chunkPointer_ = fileSize_ - chunkSize_ + 1;

					for ( int j = 0; j < first_frame_.GetChannelCount(); j++ )
						data_( data_.GetFrameCount() - 1, j ) = first_frame_[j];
				}
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

AudioFrames& FileLoop::Tick( AudioFrames& frames, int channel) {
	if ( !file_.isOpen() ) {
		#if defined(flagDEBUG)
		LOG("FileLoop::Tick(): no file data is loaded!");
		HandleError( AudioError::DEBUG_PRINT );
		#endif
		return frames;
	}

	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("FileLoop::Tick(): channel and AudioFrames arguments are incompatible!");
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

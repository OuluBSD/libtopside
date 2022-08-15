#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FileWaveOut::FileWaveOut( unsigned int bufferFrames )
	: bufferFrames_( bufferFrames ) {
}

FileWaveOut::FileWaveOut( String file_name, unsigned int channel_count, FileWrite::FILE_TYPE type, Audio::AudioFormat format, unsigned int bufferFrames )
	: bufferFrames_( bufferFrames ) {
	this->OpenFile( file_name, channel_count, type, format );
}

FileWaveOut::~FileWaveOut() {
	this->CloseFile();
}

void FileWaveOut::CloseFile() {
	if ( file_.isOpen() ) {
		if ( bufferIndex_ > 0 ) {
			data_.SetCount( bufferIndex_, data_.GetChannelCount() );
			file_.write( data_ );
		}

		file_.Close();
		frame_counter_ = 0;
	}
}

void FileWaveOut::OpenFile( String file_name,
							  unsigned int channel_count,
							  FileWrite::FILE_TYPE type,
							  Audio::AudioFormat format ) {
	CloseFile();

	if ( channel_count < 1 ) {
		LOG("FileWaveOut::openFile: the channels argument must be greater than zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	file_.Open( file_name, channel_count, type, format );
	data_.SetCount( bufferFrames_, channel_count );
	bufferIndex_ = 0;
	iData_ = 0;
}

void FileWaveOut::incrementFrame() {
	frame_counter_++;
	bufferIndex_++;

	if ( bufferIndex_ == bufferFrames_ ) {
		file_.write( data_ );
		bufferIndex_ = 0;
		iData_ = 0;
	}
}

void FileWaveOut::Tick( const double sample ) {
	#if defined(flagDEBUG)

	if ( !file_.isOpen() ) {
		LOG("FileWaveOut::Tick(): no file open!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	unsigned int channel_count = data_.GetChannelCount();
	double input = sample;
	ClipTest( input );

	for ( unsigned int j = 0; j < channel_count; j++ )
		data_[iData_++] = input;

	this->incrementFrame();
}

void FileWaveOut::Tick( const AudioFrames& frames ) {
	#if defined(flagDEBUG)

	if ( !file_.isOpen() ) {
		LOG("FileWaveOut::Tick(): no file open!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( data_.GetChannelCount() != frames.GetChannelCount() ) {
		LOG("FileWaveOut::Tick(): incompatible channel value in AudioFrames argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	unsigned int in_frames = 0;
	unsigned int j, channel_count = data_.GetChannelCount();

	for ( unsigned int i = 0; i < frames.GetFrameCount(); i++ ) {
		for ( j = 0; j < channel_count; j++ ) {
			data_[iData_] = frames[in_frames++];
			ClipTest( data_[iData_++] );
		}

		this->incrementFrame();
	}
}

NAMESPACE_AUDIO_END

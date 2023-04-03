#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

FileWaveOut::FileWaveOut( int bufferFrames )
	: bufferFrames_( bufferFrames ) {
}

FileWaveOut::FileWaveOut( String file_name, int channel_count, FileWrite::FILE_TYPE type, Audio::AudioFormat format, int bufferFrames )
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

bool FileWaveOut::OpenFile( String file_name,
							  int channel_count,
							  FileWrite::FILE_TYPE type,
							  Audio::AudioFormat format ) {
	CloseFile();

	if ( channel_count < 1 ) {
		LOG("FileWaveOut::openFile: the channels argument must be greater than zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
		return false;
	}

	file_.Open( file_name, channel_count, type, format );
	data_.SetCount( bufferFrames_, channel_count );
	bufferIndex_ = 0;
	iData_ = 0;
	
	return true;
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

void FileWaveOut::Tick( const float sample ) {
	#if defined(flagDEBUG)

	if ( !file_.isOpen() ) {
		LOG("FileWaveOut::Tick(): no file open!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	int channel_count = data_.GetChannelCount();
	float input = sample;
	ClipTest( input );

	for ( int j = 0; j < channel_count; j++ )
		data_[iData_++] = input;

	this->incrementFrame();
}

void FileWaveOut::Tick( const float l, const float r ) {
	#if defined(flagDEBUG)

	if ( !file_.isOpen() ) {
		LOG("FileWaveOut::Tick(): no file open!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	int channel_count = data_.GetChannelCount();
	
	for(int j = 0; j < channel_count; j++) {
		float input = j == 0 ? l : r;
		ClipTest( input );
		data_[iData_++] = input;
	}

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
	int in_frames = 0;
	int j, channel_count = data_.GetChannelCount();

	for ( int i = 0; i < frames.GetFrameCount(); i++ ) {
		for ( j = 0; j < channel_count; j++ ) {
			data_[iData_] = frames[in_frames++];
			ClipTest( data_[iData_++] );
		}

		this->incrementFrame();
	}
}

NAMESPACE_AUDIO_END

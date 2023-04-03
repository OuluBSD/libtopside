#include "AudioCore.h"


#if 0

NAMESPACE_AUDIO_BEGIN

DevWaveOut::DevWaveOut( int bufferFrames )
	: bufferFrames_( bufferFrames ) {
	channels = 0;
	device <<= SoundSys().GetDefaultOutput().index;
	snd.SetFlags(SND_NOCLIP);
	snd <<= THISBACK(Generator);
	OpenDevice(0);
}

DevWaveOut::~DevWaveOut() {
	snd.Close();
}

void DevWaveOut::OpenDevice(int i, int channels, int sample_rate) {
	if (sample_rate == -1)
		sample_rate = Audio::GetSampleRate();
	
	this->channels = channels;
	data_.SetCount( bufferFrames_, channels );
	data.SetCount(10);
	for(int i = 0; i < data.GetCount(); i++) {
		data[i].SetCount( bufferFrames_, channels );
	}
	data_write = 0;
	data_read = 0;
	iData_ = 0;
	initializing = true;
	
	snd.SetSampleRate(sample_rate).SetFramesPerBuffer((bufferFrames_>0)?(int)bufferFrames_:1);
	snd.Open(Null,StreamParameters(i,channels,SND_FLOAT32,SoundDevice(i).LowOutputLatency));
	if (CheckError()) return;
	snd.Start();
	
	initializing = false;
}

bool DevWaveOut::CheckError() {
	if (snd.IsError()){
		//error<<="[1 Error: "+snd.GetError();
		return true;
	}
	//error<<="";
	return false;
}

void DevWaveOut::Generator(StreamCallbackArgs& arg){
	ASSERT(data_.GetChannelCount() == channels);
	float* out = (float*)arg.output;
	int k = 0;
	
	if (initializing) {
		return;
	}
	
	while (data_read == data_write)
		Sleep(1);
	
	AudioFrames& src = data[data_read];
	ASSERT(arg.fpb == src.GetFrameCount());
	int count = src.GetFrameCount();
	for (int i = 0; i < count; i++){
		for(int j = 0; j < channels; j++) {
			*out = src[k];
			out++;
			k++;
		}
	}
	data_read++;
	if (data_read >= data.GetCount()) data_read = 0;
	
}

void DevWaveOut::Tick( const float sample ) {
	#if defined(flagDEBUG)
	if (!snd.IsOpen()) {
		LOG("DevWaveOut::Tick(): no file open!");
		HandleError( AudioError::WARNING );
		return;
	}
	#endif
	
	int channel_count = data_.GetChannelCount();
	float input = sample;
	ClipTest( input );
	
	AudioFrames& dst = data[data_write];
	
	for ( int j = 0; j < channel_count; j++ )
		dst[iData_++] = input;
	
	if (iData_ >= dst.GetCount()) {
		data_write++;
		if (data_write >= data.GetCount()) data_write = 0;
		iData_ = 0;
	}
}

void DevWaveOut::Tick( const AudioFrames& frames ) {
	#if defined(flagDEBUG)
	if (!snd.IsOpen()) {
		LOG("DevWaveOut::Tick(): no file open!");
		HandleError( AudioError::WARNING );
		return;
	}
	if (data_.GetChannelCount() != frames.GetChannelCount()) {
		LOG("DevWaveOut::Tick(): incompatible channel value in AudioFrames argument!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}
	#endif
	
	int in_frames = 0;
	int j, channel_count = data_.GetChannelCount();
	
	AudioFrames& dst = data[data_write];
	
	for ( int i = 0; i < frames.GetFrameCount(); i++ ) {
		for ( j = 0; j < channel_count; j++ ) {
			data_[iData_] = frames[in_frames++];
			ClipTest( data_[iData_++] );
		}
		
		if (iData_ >= dst.GetCount()) {
			data_write++;
			if (data_write >= data.GetCount()) data_write = 0;
			iData_ = 0;
		}
	}
}

NAMESPACE_AUDIO_END

#endif

#include "AudioCore.h"


NAMESPACE_TOPSIDE_BEGIN;
namespace Portaudio {

extern "C"{
	//this is a C callable function, to wrap U++ Callback into PaStreamCallback
	int StreamCallback(const void *input, void *output, int frames,
	          const PaStreamCallbackTimeInfo *timeinfo, int flags, void *data)
	{
		StreamCallbackData *scd = static_cast<StreamCallbackData*>(data);
		StreamCallbackArgs sca(input, output, frames, timeinfo, flags,scd->data);
		scd->func(sca);
		return(sca.state);
	}

	//this is a C callable function, to wrap WhenFinish into PaStreamFinishedCallback
	void StreamFinishedCallback(void *data){
		StreamCallbackData *scd = static_cast<StreamCallbackData*>(data);
		scd->finish(scd->data);
	}
}











AudioBase::AudioBase() : err(paNoError), flags(SND_NOFLAG){
	pa_fmt.freq = 44100;
	pa_fmt.sample_rate = 1024;
	pa_fmt.channels = 2;
	SetFormat(2, SND_FLOAT32);
	stream = 0;
	AudioSys();
}

void AudioBase::OpenStream(PaStreamCallback* cb, void* data,
                        const StreamParameters& inparam, const StreamParameters& outparam){
	ASSERT(AudioSystem::Exists());
	const PaStreamParameters* noparam=NULL;
	err = Pa_OpenStream(&stream, IsNull(inparam)?noparam:inparam, IsNull(outparam)?noparam:outparam,
	                    pa_fmt.freq, pa_fmt.sample_rate, flags, cb, data);
	CHECK_ERR;
	
	TODO // set fmt values from params
}

void AudioBase::OpenDefaultStream(PaStreamCallback* cb, void* data,
                               int inchannels,int outchannels, SampleFormat format) {
	ASSERT(AudioSystem::Exists());
	SetFormat(outchannels, format);
	err = Pa_OpenDefaultStream(&stream, inchannels, outchannels, format, pa_fmt.freq, pa_fmt.sample_rate, cb, data);
	CHECK_ERR;
}

void AudioBase::SetFormat(int out_ch, SampleFormat format) {
	pa_fmt.channels = out_ch;
	pa_fmt.fmt = format;
}

void AudioBase::Close(){
	if (IsOpen()) {
		err = Pa_CloseStream(stream);
		CHECK_ERR;
		stream = NULL;
	}
}

bool AudioBase::IsStopped() const{
	int err = Pa_IsStreamStopped(stream);
	CHECK_ERR;
	return err;
}

bool AudioBase::IsActive() const{
	int err = Pa_IsStreamActive(stream);
	CHECK_ERR;
	return err;
}

float AudioBase::GetInputLatency() const{
	const PaStreamInfo *info = Pa_GetStreamInfo(stream);
	if (info != NULL) return info->inputLatency;
	else return 0;
}

float AudioBase::GetOutputLatency() const{
	const PaStreamInfo *info = Pa_GetStreamInfo(stream);
	if (info != NULL) return info->outputLatency;
	else return 0;
}

float AudioBase::GetFrequency() const{
	const PaStreamInfo *info = Pa_GetStreamInfo(stream);
	if (info != NULL) return info->sampleRate;
	else return 0;
}













void AudioDeviceStream::Open(void* data, const StreamParameters& inparam, const StreamParameters& outparam) {
	scallback = StreamCallbackData(WhenAction, WhenFinished, data);
	OpenStream(&StreamCallback, static_cast<void *>(&scallback), inparam, outparam);
	if (err == paNoError)
		SetFinishCallback();
}


void AudioDeviceStream::Open(const StreamParameters& inparam,const StreamParameters& outparam){
	Open(NULL, inparam, outparam);
}

void AudioDeviceStream::OpenDefault(void* data, int inchannels, int outchannels, SampleFormat format){
	scallback = StreamCallbackData(WhenAction, WhenFinished, data);
	OpenDefaultStream(&StreamCallback, static_cast<void *>(&scallback), inchannels, outchannels, format);
	if (err == paNoError)
		SetFinishCallback();
}


void AudioDeviceStream::OpenDefault(int inchannels, int outchannels, SampleFormat format){
	OpenDefault(NULL, inchannels, outchannels, format);
}

void AudioDeviceStream::SetFinishCallback(){
	err = Pa_SetStreamFinishedCallback(stream, &StreamFinishedCallback);
	CHECK_ERR;
}




}
NAMESPACE_TOPSIDE_END;


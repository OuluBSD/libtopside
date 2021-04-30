#include "System.h"
#include "Internal.h"
#include "Sound.h"


NAMESPACE_OULU_BEGIN;

extern "C"{
	//this is a C callable function, to wrap U++ Callback into PaStreamCallback
	int StreamCallback(const void *input, void *output, unsigned long frames,
	          const PaStreamCallbackTimeInfo *timeinfo, unsigned long flags, void *data)
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


/* ASound */

ASound::ASound() : err(paNoError), flags(SND_NOFLAG){
	fmt.freq = 44100;
	fmt.sample_rate = 1024;
	SetFormat(2, SND_FLOAT32);
	SoundSys();
}

void ASound::OpenStream(PaStreamCallback* cb, void* data,
                        const StreamParameters& inparam, const StreamParameters& outparam){
	ASSERT(SoundSystem::Exists());
	const PaStreamParameters* noparam=NULL;
	err = Pa_OpenStream(&stream, IsNull(inparam)?noparam:inparam, IsNull(outparam)?noparam:outparam,
	                    fmt.freq, fmt.sample_rate, flags, cb, data);
	CHECK_ERR;
	
	TODO // set fmt values from params
}

void ASound::OpenDefaultStream(PaStreamCallback* cb, void* data,
                               int inchannels,int outchannels, SampleFormat format) {
	ASSERT(SoundSystem::Exists());
	SetFormat(outchannels, format);
	err = Pa_OpenDefaultStream(&stream, inchannels, outchannels, format, fmt.freq, fmt.sample_rate, cb, data);
	CHECK_ERR;
}

void ASound::SetFormat(int out_ch, SampleFormat format) {
	fmt.channels = out_ch;
	fmt.is_var_float = format == SND_FLOAT32;
	switch (format) {
		case SND_FLOAT32:
		case SND_INT32:
			fmt.var_size = 4;
			break;
		case SND_INT24:
			fmt.var_size = 3;
			break;
		case SND_INT16:
			fmt.var_size = 2;
			break;
		case SND_INT8:
		case SND_UINT8:
			fmt.var_size = 1;
			break;
		default:
			fmt.var_size = 0;
	}
}

void ASound::Close(){
	if (IsOpen()){
		err = Pa_CloseStream(stream);
		CHECK_ERR;
		stream = NULL;
	}
}

void ASound::Get(void* data, int size) {
	int vars = size / fmt.var_size;
	ASSERT(size % fmt.var_size == 0);
	int samples = vars / fmt.channels;
	ASSERT(vars % fmt.channels == 0);
	int frames = samples / fmt.sample_rate;
	ASSERT(samples % fmt.sample_rate == 0);
	total_frames += frames;
	err = Pa_ReadStream(stream, data, samples);
	CHECK_ERR;
}

void ASound::Put(void* data, int size, bool realtime) {
	int vars = size / fmt.var_size;
	ASSERT(size % fmt.var_size == 0);
	int samples = vars / fmt.channels;
	ASSERT(vars % fmt.channels == 0);
	int frames = samples / fmt.sample_rate;
	ASSERT(samples % fmt.sample_rate == 0);
	total_frames += frames;
	err = Pa_WriteStream(stream,data,samples);
	CHECK_ERR;
}

bool ASound::IsStopped() const{
	int err = Pa_IsStreamStopped(stream);
	CHECK_ERR;
	return err;
}

bool ASound::IsActive() const{
	int err = Pa_IsStreamActive(stream);
	CHECK_ERR;
	return err;
}

double ASound::GetInputLatency() const{
	const PaStreamInfo *info = Pa_GetStreamInfo(stream);
	if (info != NULL) return info->inputLatency;
	else return 0;
}

double ASound::GetOutputLatency() const{
	const PaStreamInfo *info = Pa_GetStreamInfo(stream);
	if (info != NULL) return info->outputLatency;
	else return 0;
}

double ASound::GetFrequency() const{
	const PaStreamInfo *info = Pa_GetStreamInfo(stream);
	if (info != NULL) return info->sampleRate;
	else return 0;
}

/* PaSound */

void PaSound::Open(void* data, const StreamParameters& inparam,const StreamParameters& outparam){
	scallback=StreamCallbackData(WhenAction,WhenFinished,data);
	OpenStream(&StreamCallback,static_cast<void *>(&scallback),inparam,outparam);
	if(err==paNoError) SetFinishCallback();
}

void PaSound::Open(const StreamParameters& inparam,const StreamParameters& outparam){
	Open(NULL, inparam, outparam);
}

void PaSound::OpenDefault(void* data, int inchannels,int outchannels, SampleFormat format){
	scallback=StreamCallbackData(WhenAction,WhenFinished,data);
	OpenDefaultStream(&StreamCallback, static_cast<void *>(&scallback),inchannels,outchannels,format);
	if(err==paNoError) SetFinishCallback();
}

void PaSound::OpenDefault(int inchannels, int outchannels, SampleFormat format){
	OpenDefault(NULL, inchannels, outchannels, format);
}

void PaSound::SetFinishCallback(){
	err=Pa_SetStreamFinishedCallback(stream,&StreamFinishedCallback);
	CHECK_ERR;
}



BufferedPaSound::BufferedPaSound() {
	WhenAction << THISBACK(SinkCallback);
}

void BufferedPaSound::SinkCallback(StreamCallbackArgs& args) {
	if (args.output) {
		int size = fmt.GetFrameBytes();
		if (buf.GetQueueSize()) {
			ASSERT(args.fpb == fmt.sample_rate);
			buf.Get(args.output, size);
			
			if (0) {
				SoundFormat fmt = buf.GetSoundFormat();
				if (fmt.var_size == 4 && fmt.is_var_float) {
					float* it = (float*)args.output;
					int samples = fmt.sample_rate * fmt.channels;
					float* end = it + samples;
					double sum = 0;
					while (it != end)
						sum += *it++;
					LOG(sum);
				}
			}
		}
		else {
			memset(args.output, 0, size);
		}
	}
}

void BufferedPaSound::OpenDefault(void* data, int inchannels,int outchannels, SampleFormat format){
	PaSound::OpenDefault(data, inchannels, outchannels, format);
	buf.SetSize(fmt);
}

void BufferedPaSound::OpenDefault(int inchannels, int outchannels, SampleFormat format){
	PaSound::OpenDefault(inchannels, outchannels, format);
	buf.SetSize(fmt);
}

NAMESPACE_OULU_END;


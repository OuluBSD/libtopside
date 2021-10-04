#include "AudioCore.h"


NAMESPACE_TOPSIDE_BEGIN;
namespace Portaudio {
	


void AudioStream::Open(const StreamParameters& inparam, const StreamParameters& outparam) {
	OpenStream(NULL, NULL, inparam, outparam);
}

void AudioStream::OpenDefault(int inchannels, int outchannels, SampleFormat format) {
	OpenDefaultStream(NULL, NULL, inchannels, outchannels, format);
}

int AudioStream::ReadAvailable() {
	int n = Pa_GetStreamReadAvailable(stream);
	if (n < 0) {
		err = n;
		CHECK_ERR;
		return -1;
	}
	else
		return n;
}

int AudioStream::WriteAvailable() {
	int n = Pa_GetStreamWriteAvailable(stream);
	if (n < 0) {
		err = n;
		CHECK_ERR;
		return -1;
	}
	else
		return n;
}



}
NAMESPACE_TOPSIDE_END

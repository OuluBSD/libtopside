#include "AudioHost.h"

#ifdef flagMAIN

#include <sndfile.hh>
#include <string>

int main(int argc, char** argv) {
	Vector<float> audio_in;
	Vector<float> audio_out;
	audio_in.SetCount(44100 * 5);
	audio_out.SetCount(44100 * 10);
	
	SndfileHandle outfile("lvtwohostTest.wav" , SFM_WRITE,  SF_FORMAT_WAV | SF_FORMAT_FLOAT , 2 , 44100);
	
	// instantiate LV2 host class
	String plugin_uri = "http://www.openavproductions.com/artyfx#roomy";
	Lv2Host* host = new Lv2Host(0, 44100, 1024, plugin_uri);
	
	// process buffer size
	int nframes = 128;
	
	SndfileHandle infile("test.wav");
	infile.read(audio_in, 44100 * 10);
	
	float** audio_buf = host->GetAudioBuffers();
	
	for (int i = 0; i < ceil(44100 * 5 / 128); i++) {
		// copy input
		std::copy(&audio_in[i * 128], &audio_in[i * 128] + 128, audio_buf[0]);
		host->Process(nframes);
		// copy output
		
		for (int x = 0; x < 128; x++) {
			audio_out[i * 256 + 2 * x] = audio_buf[1][x];
			audio_out[i * 256 + 1 + 2 * x] = audio_buf[1][x];
		}
	}
	
	// save audio to disk
	outfile.write(audio_out, 44100 * 10);
	
	// cleanup
	delete host;
	delete[] audio_in;
	delete[] audio_out;
	
	return 0;
}

#endif

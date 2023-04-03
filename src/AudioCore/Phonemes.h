#ifndef _AudioCore_PHONEMES_H
#define _AudioCore_PHONEMES_H


NAMESPACE_AUDIO_BEGIN


class Phonemes : public Audio {
public:
	Phonemes();
	~Phonemes();
	static const char* name( int index );
	static float GetVoiceGain( int index );
	static float GetNoiseGain( int index );
	static float GetFormantFrequency( int index, int partial );
	static float GetFormantRadius( int index, int partial );
	static float GetFormantGain( int index, int partial );

private:

	static const char phoneme_names[][4];
	static const float phoneme_gains[][2];
	static const float phoneme_parameters[][4][3];
};

NAMESPACE_AUDIO_END

#endif

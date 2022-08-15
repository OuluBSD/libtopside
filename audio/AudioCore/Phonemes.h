#ifndef _AudioCore_PHONEMES_H
#define _AudioCore_PHONEMES_H


NAMESPACE_AUDIO_BEGIN


class Phonemes : public Audio {
public:
	Phonemes();
	~Phonemes();
	static const char* name( unsigned int index );
	static double GetVoiceGain( unsigned int index );
	static double GetNoiseGain( unsigned int index );
	static double GetFormantFrequency( unsigned int index, unsigned int partial );
	static double GetFormantRadius( unsigned int index, unsigned int partial );
	static double GetFormantGain( unsigned int index, unsigned int partial );

private:

	static const char phoneme_names[][4];
	static const double phoneme_gains[][2];
	static const double phoneme_parameters[][4][3];
};

NAMESPACE_AUDIO_END

#endif

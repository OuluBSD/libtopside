#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

const char Phonemes::phoneme_names[32][4] = {
	"eee", "ihh", "ehh", "aaa",
	"ahh", "aww", "ohh", "uhh",
	"uuu", "ooo", "rrr", "lll",
	"mmm", "nnn", "nng", "ngg",
	"fff", "sss", "thh", "shh",
	"xxx", "hee", "hoo", "hah",
	"bbb", "ddd", "jjj", "ggg",
	"vvv", "zzz", "thz", "zhh"
};

const float Phonemes::phoneme_gains[32][2] = {
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},

	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},
	{1.0f, 0.0f},

	{0.0f, 0.7},
	{0.0f, 0.7},
	{0.0f, 0.7},
	{0.0f, 0.7},

	{0.0f, 0.7},
	{0.0f, 0.1},
	{0.0f, 0.1},
	{0.0f, 0.1},

	{1.0f, 0.1},
	{1.0f, 0.1},
	{1.0f, 0.1},
	{1.0f, 0.1},

	{1.0f, 1.0f},
	{1.0f, 1.0f},
	{1.0f, 1.0f},
	{1.0f, 1.0f}
};

const float Phonemes::phoneme_parameters[32][4][3] = {
	{	{ 273, 0.996,  10},
		{2086, 0.945, -16},
		{2754, 0.979, -12},
		{3270, 0.440, -17}
	},
	{	{ 385, 0.987,  10},
		{2056, 0.930, -20},
		{2587, 0.890, -20},
		{3150, 0.400, -20}
	},
	{	{ 515, 0.977,  10},
		{1805, 0.810, -10},
		{2526, 0.875, -10},
		{3103, 0.400, -13}
	},
	{	{ 773, 0.950,  10},
		{1676, 0.830,  -6},
		{2380, 0.880, -20},
		{3027, 0.600, -20}
	},

	{	{ 770, 0.950,   0},
		{1153, 0.970,  -9},
		{2450, 0.780, -29},
		{3140, 0.800, -39}
	},
	{	{ 637, 0.910,   0},
		{ 895, 0.900,  -3},
		{2556, 0.950, -17},
		{3070, 0.910, -20}
	},
	{	{ 637, 0.910,   0},
		{ 895, 0.900,  -3},
		{2556, 0.950, -17},
		{3070, 0.910, -20}
	},
	{	{ 561, 0.965,   0},
		{1084, 0.930, -10},
		{2541, 0.930, -15},
		{3345, 0.900, -20}
	},

	{	{ 515, 0.976,   0},
		{1031, 0.950,  -3},
		{2572, 0.960, -11},
		{3345, 0.960, -20}
	},
	{	{ 349, 0.986, -10},
		{ 918, 0.940, -20},
		{2350, 0.960, -27},
		{2731, 0.950, -33}
	},
	{	{ 394, 0.959, -10},
		{1297, 0.780, -16},
		{1441, 0.980, -16},
		{2754, 0.950, -40}
	},
	{	{ 462, 0.990,  +5},
		{1200, 0.640, -10},
		{2500, 0.200, -20},
		{3000, 0.100, -30}
	},

	{	{ 265, 0.987, -10},
		{1176, 0.940, -22},
		{2352, 0.970, -20},
		{3277, 0.940, -31}
	},
	{	{ 204, 0.980, -10},
		{1570, 0.940, -15},
		{2481, 0.980, -12},
		{3133, 0.800, -30}
	},
	{	{ 204, 0.980, -10},
		{1570, 0.940, -15},
		{2481, 0.980, -12},
		{3133, 0.800, -30}
	},
	{	{ 204, 0.980, -10},
		{1570, 0.940, -15},
		{2481, 0.980, -12},
		{3133, 0.800, -30}
	},

	{	{1000, 0.300,   0},
		{2800, 0.860, -10},
		{7425, 0.740,   0},
		{8140, 0.860,   0}
	},
	{	{0,    0.000,   0},
		{2000, 0.700, -15},
		{5257, 0.750,  -3},
		{7171, 0.840,   0}
	},
	{	{ 100, 0.900,   0},
		{4000, 0.500, -20},
		{5500, 0.500, -15},
		{8000, 0.400, -20}
	},
	{	{2693, 0.940,   0},
		{4000, 0.720, -10},
		{6123, 0.870, -10},
		{7755, 0.750, -18}
	},

	{	{1000, 0.300, -10},
		{2800, 0.860, -10},
		{7425, 0.740,   0},
		{8140, 0.860,   0}
	},
	{	{ 273, 0.996, -40},
		{2086, 0.945, -16},
		{2754, 0.979, -12},
		{3270, 0.440, -17}
	},
	{	{ 349, 0.986, -40},
		{ 918, 0.940, -10},
		{2350, 0.960, -17},
		{2731, 0.950, -23}
	},
	{	{ 770, 0.950, -40},
		{1153, 0.970,  -3},
		{2450, 0.780, -20},
		{3140, 0.800, -32}
	},

	{	{2000, 0.700, -20},
		{5257, 0.750, -15},
		{7171, 0.840,  -3},
		{9000, 0.900,   0}
	},
	{	{ 100, 0.900,   0},
		{4000, 0.500, -20},
		{5500, 0.500, -15},
		{8000, 0.400, -20}
	},
	{	{2693, 0.940,   0},
		{4000, 0.720, -10},
		{6123, 0.870, -10},
		{7755, 0.750, -18}
	},
	{	{2693, 0.940,   0},
		{4000, 0.720, -10},
		{6123, 0.870, -10},
		{7755, 0.750, -18}
	},

	{	{2000, 0.700, -20},
		{5257, 0.750, -15},
		{7171, 0.840,  -3},
		{9000, 0.900,   0}
	},
	{	{ 100, 0.900,   0},
		{4000, 0.500, -20},
		{5500, 0.500, -15},
		{8000, 0.400, -20}
	},
	{	{2693, 0.940,   0},
		{4000, 0.720, -10},
		{6123, 0.870, -10},
		{7755, 0.750, -18}
	},
	{	{2693, 0.940,   0},
		{4000, 0.720, -10},
		{6123, 0.870, -10},
		{7755, 0.750, -18}
	}
};

Phonemes::Phonemes(void) {
}

Phonemes::~Phonemes(void) {
}

const char* Phonemes::name( int index ) {
	if ( index > 31 ) {
		LOG("WARNING: Phonemes::name: index is greater than 31!");
		return 0;
	}

	return phoneme_names[index];
}

float Phonemes::GetVoiceGain( int index ) {
	if ( index > 31 ) {
		LOG("WARNING: Phonemes::GetVoiceGain: index is greater than 31!");
		return 0.0f;
	}

	return phoneme_gains[index][0];
}

float Phonemes::GetNoiseGain( int index ) {
	if ( index > 31 ) {
		LOG("WARNING: Phonemes::GetNoiseGain: index is greater than 31!");
		return 0.0f;
	}

	return phoneme_gains[index][1];
}

float Phonemes::GetFormantFrequency( int index, int partial ) {
	if ( index > 31 ) {
		LOG("WARNING: Phonemes::GetFormantFrequency: index is greater than 31!");
		return 0.0f;
	}

	if ( partial > 3 ) {
		LOG("WARNING: Phonemes::GetFormantFrequency: partial is greater than 3!");
		return 0.0f;
	}

	return phoneme_parameters[index][partial][0];
}

float Phonemes::GetFormantRadius( int index, int partial ) {
	if ( index > 31 ) {
		LOG("WARNING: Phonemes::GetFormantRadius: index is greater than 31!");
		return 0.0f;
	}

	if ( partial > 3 ) {
		LOG("WARNING: Phonemes::GetFormantRadius: partial is greater than 3!");
		return 0.0f;
	}

	return phoneme_parameters[index][partial][1];
}

float Phonemes::GetFormantGain( int index, int partial ) {
	if ( index > 31 ) {
		LOG("WARNING: Phonemes::GetFormantGain: index is greater than 31!");
		return 0.0f;
	}

	if ( partial > 3 ) {
		LOG("WARNING: Phonemes::GetFormantGain: partial is greater than 3!");
		return 0.0f;
	}

	return phoneme_parameters[index][partial][2];
}

NAMESPACE_AUDIO_END

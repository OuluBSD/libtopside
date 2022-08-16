#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN


const double MARACA_SOUND_DECAY = 0.95;
const double MARACA_SYSTEM_DECAY = 0.999;
const double MARACA_GAIN = 4.0;
const double MARACA_NUM_BEANS = 25;
const int MARACA_RESONANCES = 1;
const double MARACA_FREQUENCIES[MARACA_RESONANCES] = { 3200 };
const double MARACA_RADII[MARACA_RESONANCES] = { 0.96 };
const double MARACA_GAINS[MARACA_RESONANCES] = { 1.0 };


const double CABASA_SOUND_DECAY = 0.96;
const double CABASA_SYSTEM_DECAY = 0.997;
const double CABASA_GAIN = 8.0;
const double CABASA_NUM_BEADS = 512;
const int CABASA_RESONANCES = 1;
const double CABASA_FREQUENCIES[CABASA_RESONANCES] = { 3000 };
const double CABASA_RADII[CABASA_RESONANCES] = { 0.7 };
const double CABASA_GAINS[CABASA_RESONANCES] = { 1.0 };


const double SEKERE_SOUND_DECAY = 0.96;
const double SEKERE_SYSTEM_DECAY = 0.999;
const double SEKERE_GAIN = 4.0;
const double SEKERE_NUM_BEANS = 64;
const int SEKERE_RESONANCES = 1;
const double SEKERE_FREQUENCIES[SEKERE_RESONANCES] = { 5500 };
const double SEKERE_RADII[SEKERE_RESONANCES] = { 0.6 };
const double SEKERE_GAINS[SEKERE_RESONANCES] = { 1.0 };


const double BAMBOO_SOUND_DECAY = 0.9;
const double BAMBOO_SYSTEM_DECAY = 0.9999;
const double BAMBOO_GAIN = 0.4;
const double BAMBOO_NUM_TUBES = 1.2;
const int BAMBOO_RESONANCES = 3;
const double BAMBOO_FREQUENCIES[BAMBOO_RESONANCES] = { 2800, 0.8 * 2800.0, 1.2 * 2800.0 };
const double BAMBOO_RADII[BAMBOO_RESONANCES] = { 0.995, 0.995, 0.995 };
const double BAMBOO_GAINS[BAMBOO_RESONANCES] = { 1.0, 1.0, 1.0 };


const double TAMBOURINE_SOUND_DECAY = 0.95;
const double TAMBOURINE_SYSTEM_DECAY = 0.9985;
const double TAMBOURINE_GAIN = 1.0;
const double TAMBOURINE_NUM_TIMBRELS = 32;
const int TAMBOURINE_RESONANCES = 3;
const double TAMBOURINE_FREQUENCIES[TAMBOURINE_RESONANCES] = { 2300, 5600, 8100 };
const double TAMBOURINE_RADII[TAMBOURINE_RESONANCES] = { 0.96, 0.99, 0.99 };
const double TAMBOURINE_GAINS[TAMBOURINE_RESONANCES] = { 0.1, 0.8, 1.0 };


const double SLEIGH_SOUND_DECAY = 0.97;
const double SLEIGH_SYSTEM_DECAY = 0.9994;
const double SLEIGH_GAIN = 1.0;
const double SLEIGH_NUM_BELLS = 32;
const int SLEIGH_RESONANCES = 5;
const double SLEIGH_FREQUENCIES[SLEIGH_RESONANCES] = { 2500, 5300, 6500, 8300, 9800 };
const double SLEIGH_RADII[SLEIGH_RESONANCES] = { 0.99, 0.99, 0.99, 0.99, 0.99 };
const double SLEIGH_GAINS[SLEIGH_RESONANCES] = { 1.0, 1.0, 1.0, 0.5, 0.3 };


const double SANDPAPER_SOUND_DECAY = 0.999;
const double SANDPAPER_SYSTEM_DECAY = 0.999;
const double SANDPAPER_GAIN = 0.5;
const double SANDPAPER_NUM_GRAINS = 128;
const int SANDPAPER_RESONANCES = 1;
const double SANDPAPER_FREQUENCIES[SANDPAPER_RESONANCES] = { 4500 };
const double SANDPAPER_RADII[SANDPAPER_RESONANCES] = { 0.6 };
const double SANDPAPER_GAINS[SANDPAPER_RESONANCES] = { 1.0 };


const double COKECAN_SOUND_DECAY = 0.97;
const double COKECAN_SYSTEM_DECAY = 0.999;
const double COKECAN_GAIN = 0.5;
const double COKECAN_NUM_PARTS = 48;
const int COKECAN_RESONANCES = 5;
const double COKECAN_FREQUENCIES[COKECAN_RESONANCES] = { 370, 1025, 1424, 2149, 3596 };
const double COKECAN_RADII[COKECAN_RESONANCES] = { 0.99, 0.992, 0.992, 0.992, 0.992 };
const double COKECAN_GAINS[COKECAN_RESONANCES] = { 1.0, 1.8, 1.8, 1.8, 1.8 };


const double ANGKLUNG_SOUND_DECAY = 0.95;
const double ANGKLUNG_SYSTEM_DECAY = 0.9999;
const double ANGKLUNG_GAIN = 0.5;
const double ANGKLUNG_NUM_TUBES = 1.2;
const int ANGKLUNG_RESONANCES = 7;
const double ANGKLUNG_FREQUENCIES[ANGKLUNG_RESONANCES] = { 1046.6, 1174.8, 1397.0, 1568, 1760, 2093.3, 2350 };
const double ANGKLUNG_RADII[ANGKLUNG_RESONANCES] = { 0.996, 0.996, 0.996, 0.996, 0.996, 0.996, 0.996 };
const double ANGKLUNG_GAINS[ANGKLUNG_RESONANCES] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };


const double GUIRO_SOUND_DECAY = 0.95;
const double GUIRO_GAIN = 0.4;
const double GUIRO_NUM_PARTS = 128;
const int GUIRO_RESONANCES = 2;
const double GUIRO_FREQUENCIES[GUIRO_RESONANCES] = { 2500, 4000 };
const double GUIRO_RADII[GUIRO_RESONANCES] = { 0.97, 0.97 };
const double GUIRO_GAINS[GUIRO_RESONANCES] = { 1.0, 1.0 };


const double WRENCH_SOUND_DECAY = 0.95;
const double WRENCH_GAIN = 0.4;
const double WRENCH_NUM_PARTS = 128;
const int WRENCH_RESONANCES = 2;
const double WRENCH_FREQUENCIES[WRENCH_RESONANCES] = { 3200, 8000 };
const double WRENCH_RADII[WRENCH_RESONANCES] = { 0.99, 0.992 };
const double WRENCH_GAINS[WRENCH_RESONANCES] = { 1.0, 1.0 };


const double WATER_SOUND_DECAY = 0.95;
const double WATER_SYSTEM_DECAY = 0.996;
const double WATER_GAIN = 1.0;
const double WATER_NUM_SOURCES = 10;
const int WATER_RESONANCES = 3;
const double WATER_FREQUENCIES[WATER_RESONANCES] = { 450, 600, 750 };
const double WATER_RADII[WATER_RESONANCES] = { 0.9985, 0.9985, 0.9985 };
const double WATER_GAINS[WATER_RESONANCES] = { 1.0, 1.0, 1.0 };





const double STIX1_SOUND_DECAY = 0.96;
const double STIX1_SYSTEM_DECAY = 0.998;
const double STIX1_GAIN = 6.0;
const double STIX1_NUM_BEANS = 2;
const int STIX1_RESONANCES = 1;
const double STIX1_FREQUENCIES[STIX1_RESONANCES] = { 5500 };
const double STIX1_RADII[STIX1_RESONANCES] = { 0.6 };
const double STIX1_GAINS[STIX1_RESONANCES] = { 1.0 };


const double CRUNCH1_SOUND_DECAY = 0.95;
const double CRUNCH1_SYSTEM_DECAY = 0.99806;
const double CRUNCH1_GAIN = 4.0;
const double CRUNCH1_NUM_BEADS = 7;
const int CRUNCH1_RESONANCES = 1;
const double CRUNCH1_FREQUENCIES[CRUNCH1_RESONANCES] = { 800 };
const double CRUNCH1_RADII[CRUNCH1_RESONANCES] = { 0.95 };
const double CRUNCH1_GAINS[CRUNCH1_RESONANCES] = { 1.0 };


const double NEXTMUG_SOUND_DECAY = 0.97;
const double NEXTMUG_SYSTEM_DECAY = 0.9995;
const double NEXTMUG_GAIN = 0.8;
const double NEXTMUG_NUM_PARTS = 3;
const int NEXTMUG_RESONANCES = 4;
const double NEXTMUG_FREQUENCIES[NEXTMUG_RESONANCES] = { 2123, 4518, 8856, 10753 };
const double NEXTMUG_RADII[NEXTMUG_RESONANCES] = { 0.997, 0.997, 0.997, 0.997 };
const double NEXTMUG_GAINS[NEXTMUG_RESONANCES] = { 1.0, 0.8, 0.6, 0.4 };

const int COIN_RESONANCES = 3;
const double PENNY_FREQUENCIES[COIN_RESONANCES] = { 11000, 5200, 3835 };
const double PENNY_RADII[COIN_RESONANCES] = { 0.999, 0.999, 0.999 };
const double PENNY_GAINS[COIN_RESONANCES] = { 1.0, 0.8, 0.5 };

const double NICKEL_FREQUENCIES[COIN_RESONANCES] = { 5583, 9255, 9805 };
const double NICKEL_RADII[COIN_RESONANCES] = { 0.9992, 0.9992, 0.9992 };
const double NICKEL_GAINS[COIN_RESONANCES] = { 1.0, 0.8, 0.5 };

const double DIME_FREQUENCIES[COIN_RESONANCES] = { 4450, 4974, 9945 };
const double DIME_RADII[COIN_RESONANCES] = { 0.9993, 0.9993, 0.9993 };
const double DIME_GAINS[COIN_RESONANCES] = { 1.0, 0.8, 0.5 };

const double QUARTER_FREQUENCIES[COIN_RESONANCES] = { 1708, 8863, 9045 };
const double QUARTER_RADII[COIN_RESONANCES] = { 0.9995, 0.9995, 0.9995 };
const double QUARTER_GAINS[COIN_RESONANCES] = { 1.0, 0.8, 0.5 };

const double FRANC_FREQUENCIES[COIN_RESONANCES] = { 5583, 11010, 1917 };
const double FRANC_RADII[COIN_RESONANCES] = { 0.9995, 0.9995, 0.9995 };
const double FRANC_GAINS[COIN_RESONANCES] = { 0.7, 0.4, 0.3 };

const double PESO_FREQUENCIES[COIN_RESONANCES] = { 7250, 8150, 10060 };
const double PESO_RADII[COIN_RESONANCES] = { 0.9996, 0.9996, 0.9996 };
const double PESO_GAINS[COIN_RESONANCES] = { 1.0, 1.2, 0.7 };


const double BIGROCKS_SOUND_DECAY = 0.98;
const double BIGROCKS_SYSTEM_DECAY = 0.9965;
const double BIGROCKS_GAIN = 4.0;
const double BIGROCKS_NUM_PARTS = 23;
const int BIGROCKS_RESONANCES = 1;
const double BIGROCKS_FREQUENCIES[BIGROCKS_RESONANCES] = { 6460 };
const double BIGROCKS_RADII[BIGROCKS_RESONANCES] = { 0.932 };
const double BIGROCKS_GAINS[BIGROCKS_RESONANCES] = { 1.0 };


const double LITTLEROCKS_SOUND_DECAY = 0.98;
const double LITTLEROCKS_SYSTEM_DECAY = 0.99586;
const double LITTLEROCKS_GAIN = 4.0;
const double LITTLEROCKS_NUM_PARTS = 1600;
const int LITTLEROCKS_RESONANCES = 1;
const double LITTLEROCKS_FREQUENCIES[LITTLEROCKS_RESONANCES] = { 9000 };
const double LITTLEROCKS_RADII[LITTLEROCKS_RESONANCES] = { 0.843 };
const double LITTLEROCKS_GAINS[LITTLEROCKS_RESONANCES] = { 1.0 };

Shakers::Shakers( int type ) {
	shakerType_ = -1;
	this->SetType( type );
}

void Shakers::SetType( int type ) {
	if ( shakerType_ == type ) return;

	varyFactor_ = 0.0;
	shakerType_ = type;

	if ( type == 1 ) {
		nResonances_ = CABASA_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = CABASA_NUM_BEADS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = CABASA_RADII[i];
			baseFrequencies_[i] = CABASA_FREQUENCIES[i];
			filters_[i].gain = CABASA_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = CABASA_SYSTEM_DECAY;
		base_gain_ = CABASA_GAIN;
		soundDecay_ = CABASA_SOUND_DECAY;
		decayScale_ = 0.97;
		SetEqualization( 1.0, -1.0, 0.0 );
	}
	else if ( type == 2 ) {
		nResonances_ = SEKERE_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = SEKERE_NUM_BEANS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = SEKERE_RADII[i];
			baseFrequencies_[i] = SEKERE_FREQUENCIES[i];
			filters_[i].gain = SEKERE_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = SEKERE_SYSTEM_DECAY;
		base_gain_ = SEKERE_GAIN;
		soundDecay_ = SEKERE_SOUND_DECAY;
		decayScale_ = 0.94;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 3 ) {
		nResonances_ = TAMBOURINE_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = TAMBOURINE_NUM_TIMBRELS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = TAMBOURINE_RADII[i];
			baseFrequencies_[i] = TAMBOURINE_FREQUENCIES[i];
			filters_[i].gain = TAMBOURINE_GAINS[i];
			doVaryFrequency_[i] = true;
		}

		doVaryFrequency_[0] = false;
		baseDecay_ = TAMBOURINE_SYSTEM_DECAY;
		base_gain_ = TAMBOURINE_GAIN;
		soundDecay_ = TAMBOURINE_SOUND_DECAY;
		decayScale_ = 0.95;
		varyFactor_ = 0.05;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 4 ) {
		nResonances_ = SLEIGH_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = SLEIGH_NUM_BELLS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = SLEIGH_RADII[i];
			baseFrequencies_[i] = SLEIGH_FREQUENCIES[i];
			filters_[i].gain = SLEIGH_GAINS[i];
			doVaryFrequency_[i] = true;
		}

		baseDecay_ = SLEIGH_SYSTEM_DECAY;
		base_gain_ = SLEIGH_GAIN;
		soundDecay_ = SLEIGH_SOUND_DECAY;
		decayScale_ = 0.9;
		varyFactor_ = 0.03;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 5 ) {
		nResonances_ = BAMBOO_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = BAMBOO_NUM_TUBES;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = BAMBOO_RADII[i];
			baseFrequencies_[i] = BAMBOO_FREQUENCIES[i];
			filters_[i].gain = BAMBOO_GAINS[i];
			doVaryFrequency_[i] = true;
		}

		baseDecay_ = BAMBOO_SYSTEM_DECAY;
		base_gain_ = BAMBOO_GAIN;
		soundDecay_ = BAMBOO_SOUND_DECAY;
		decayScale_ = 0.7;
		varyFactor_ = 0.2;
		SetEqualization( 1.0, 0.0, 0.0 );
	}
	else if ( type == 6 ) {
		nResonances_ = SANDPAPER_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = SANDPAPER_NUM_GRAINS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = SANDPAPER_RADII[i];
			baseFrequencies_[i] = SANDPAPER_FREQUENCIES[i];
			filters_[i].gain = SANDPAPER_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = SANDPAPER_SYSTEM_DECAY;
		base_gain_ = SANDPAPER_GAIN;
		soundDecay_ = SANDPAPER_SOUND_DECAY;
		decayScale_ = 0.97;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 7 ) {
		nResonances_ = COKECAN_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = COKECAN_NUM_PARTS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = COKECAN_RADII[i];
			baseFrequencies_[i] = COKECAN_FREQUENCIES[i];
			filters_[i].gain = COKECAN_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = COKECAN_SYSTEM_DECAY;
		base_gain_ = COKECAN_GAIN;
		soundDecay_ = COKECAN_SOUND_DECAY;
		decayScale_ = 0.95;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 8 ) {
		nResonances_ = STIX1_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = STIX1_NUM_BEANS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = STIX1_RADII[i];
			baseFrequencies_[i] = STIX1_FREQUENCIES[i];
			filters_[i].gain = STIX1_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = STIX1_SYSTEM_DECAY;
		base_gain_ = STIX1_GAIN;
		soundDecay_ = STIX1_SOUND_DECAY;
		decayScale_ = 0.96;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 9 ) {
		nResonances_ = CRUNCH1_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = CRUNCH1_NUM_BEADS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = CRUNCH1_RADII[i];
			baseFrequencies_[i] = CRUNCH1_FREQUENCIES[i];
			filters_[i].gain = CRUNCH1_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = CRUNCH1_SYSTEM_DECAY;
		base_gain_ = CRUNCH1_GAIN;
		soundDecay_ = CRUNCH1_SOUND_DECAY;
		decayScale_ = 0.96;
		SetEqualization( 1.0, -1.0, 0.0 );
	}
	else if ( type == 10 ) {
		nResonances_ = BIGROCKS_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = BIGROCKS_NUM_PARTS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = BIGROCKS_RADII[i];
			baseFrequencies_[i] = BIGROCKS_FREQUENCIES[i];
			filters_[i].gain = BIGROCKS_GAINS[i];
			doVaryFrequency_[i] = true;
		}

		baseDecay_ = BIGROCKS_SYSTEM_DECAY;
		base_gain_ = BIGROCKS_GAIN;
		soundDecay_ = BIGROCKS_SOUND_DECAY;
		decayScale_ = 0.95;
		varyFactor_ = 0.11;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 11 ) {
		nResonances_ = LITTLEROCKS_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = LITTLEROCKS_NUM_PARTS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = LITTLEROCKS_RADII[i];
			baseFrequencies_[i] = LITTLEROCKS_FREQUENCIES[i];
			filters_[i].gain = LITTLEROCKS_GAINS[i];
			doVaryFrequency_[i] = true;
		}

		baseDecay_ = LITTLEROCKS_SYSTEM_DECAY;
		base_gain_ = LITTLEROCKS_GAIN;
		soundDecay_ = LITTLEROCKS_SOUND_DECAY;
		decayScale_ = 0.95;
		varyFactor_ = 0.18;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type > 11 && type < 19 ) {
		nResonances_ = NEXTMUG_RESONANCES;

		if ( type > 12 )
			nResonances_ += COIN_RESONANCES;

		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = NEXTMUG_NUM_PARTS;

		for ( int i = 0; i < NEXTMUG_RESONANCES; i++ ) {
			baseRadii_[i] = NEXTMUG_RADII[i];
			baseFrequencies_[i] = NEXTMUG_FREQUENCIES[i];
			filters_[i].gain = NEXTMUG_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = NEXTMUG_SYSTEM_DECAY;
		base_gain_ = NEXTMUG_GAIN;
		soundDecay_ = NEXTMUG_SOUND_DECAY;
		decayScale_ = 0.95;
		SetEqualization( 1.0, 0.0, -1.0 );

		if ( type == 13 ) {
			for ( int i = 0; i < COIN_RESONANCES; i++ ) {
				baseRadii_[i + NEXTMUG_RESONANCES] = PENNY_RADII[i];
				baseFrequencies_[i + NEXTMUG_RESONANCES] = PENNY_FREQUENCIES[i];
				filters_[i + NEXTMUG_RESONANCES].gain = PENNY_GAINS[i];
				doVaryFrequency_[i + NEXTMUG_RESONANCES] = false;
			}
		}
		else if ( type == 14 ) {
			for ( int i = 0; i < COIN_RESONANCES; i++ ) {
				baseRadii_[i + NEXTMUG_RESONANCES] = NICKEL_RADII[i];
				baseFrequencies_[i + NEXTMUG_RESONANCES] = NICKEL_FREQUENCIES[i];
				filters_[i + NEXTMUG_RESONANCES].gain = NICKEL_GAINS[i];
				doVaryFrequency_[i + NEXTMUG_RESONANCES] = false;
			}
		}
		else if ( type == 15 ) {
			for ( int i = 0; i < COIN_RESONANCES; i++ ) {
				baseRadii_[i + NEXTMUG_RESONANCES] = DIME_RADII[i];
				baseFrequencies_[i + NEXTMUG_RESONANCES] = DIME_FREQUENCIES[i];
				filters_[i + NEXTMUG_RESONANCES].gain = DIME_GAINS[i];
				doVaryFrequency_[i + NEXTMUG_RESONANCES] = false;
			}
		}
		else if ( type == 16 ) {
			for ( int i = 0; i < COIN_RESONANCES; i++ ) {
				baseRadii_[i + NEXTMUG_RESONANCES] = QUARTER_RADII[i];
				baseFrequencies_[i + NEXTMUG_RESONANCES] = QUARTER_FREQUENCIES[i];
				filters_[i + NEXTMUG_RESONANCES].gain = QUARTER_GAINS[i];
				doVaryFrequency_[i + NEXTMUG_RESONANCES] = false;
			}
		}
		else if ( type == 17 ) {
			for ( int i = 0; i < COIN_RESONANCES; i++ ) {
				baseRadii_[i + NEXTMUG_RESONANCES] = FRANC_RADII[i];
				baseFrequencies_[i + NEXTMUG_RESONANCES] = FRANC_FREQUENCIES[i];
				filters_[i + NEXTMUG_RESONANCES].gain = FRANC_GAINS[i];
				doVaryFrequency_[i + NEXTMUG_RESONANCES] = false;
			}
		}
		else if ( type == 18 ) {
			for ( int i = 0; i < COIN_RESONANCES; i++ ) {
				baseRadii_[i + NEXTMUG_RESONANCES] = PESO_RADII[i];
				baseFrequencies_[i + NEXTMUG_RESONANCES] = PESO_FREQUENCIES[i];
				filters_[i + NEXTMUG_RESONANCES].gain = PESO_GAINS[i];
				doVaryFrequency_[i + NEXTMUG_RESONANCES] = false;
			}
		}
	}
	else if ( type == 19 ) {
		nResonances_ = GUIRO_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = GUIRO_NUM_PARTS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = GUIRO_RADII[i];
			baseFrequencies_[i] = GUIRO_FREQUENCIES[i];
			filters_[i].gain = GUIRO_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		base_gain_ = GUIRO_GAIN;
		soundDecay_ = GUIRO_SOUND_DECAY;
		ratchetCount_ = 0;
		baseRatchetDelta_ = 0.0001;
		ratchetDelta_ = baseRatchetDelta_;
		lastRatchetValue_ = -1;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 20 ) {
		nResonances_ = WRENCH_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = WRENCH_NUM_PARTS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = WRENCH_RADII[i];
			baseFrequencies_[i] = WRENCH_FREQUENCIES[i];
			filters_[i].gain = WRENCH_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		base_gain_ = WRENCH_GAIN;
		soundDecay_ = WRENCH_SOUND_DECAY;
		ratchetCount_ = 0;
		baseRatchetDelta_ = 0.00015;
		ratchetDelta_ = baseRatchetDelta_;
		lastRatchetValue_ = -1;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else if ( type == 21 ) {
		nResonances_ = WATER_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		tempFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = WATER_NUM_SOURCES;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = WATER_RADII[i];
			baseFrequencies_[i] = WATER_FREQUENCIES[i];
			tempFrequencies_[i] = WATER_FREQUENCIES[i];
			filters_[i].gain = WATER_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = WATER_SYSTEM_DECAY;
		base_gain_ = WATER_GAIN;
		soundDecay_ = WATER_SOUND_DECAY;
		decayScale_ = 0.8;
		SetEqualization( -1.0, 0.0, 1.0 );
	}
	else if ( type == 22 ) {
		nResonances_ = ANGKLUNG_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = ANGKLUNG_NUM_TUBES;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = ANGKLUNG_RADII[i];
			baseFrequencies_[i] = ANGKLUNG_FREQUENCIES[i];
			filters_[i].gain = ANGKLUNG_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = ANGKLUNG_SYSTEM_DECAY;
		base_gain_ = ANGKLUNG_GAIN;
		soundDecay_ = ANGKLUNG_SOUND_DECAY;
		decayScale_ = 0.7;
		SetEqualization( 1.0, 0.0, -1.0 );
	}
	else {
		shakerType_ = 0;
		nResonances_ = MARACA_RESONANCES;
		filters_.SetCount( nResonances_ );
		baseFrequencies_.SetCount( nResonances_ );
		baseRadii_.SetCount( nResonances_ );
		doVaryFrequency_.SetCount( nResonances_ );
		baseObjects_ = MARACA_NUM_BEANS;

		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			baseRadii_[i] = MARACA_RADII[i];
			baseFrequencies_[i] = MARACA_FREQUENCIES[i];
			filters_[i].gain = MARACA_GAINS[i];
			doVaryFrequency_[i] = false;
		}

		baseDecay_ = MARACA_SYSTEM_DECAY;
		base_gain_ = MARACA_GAIN;
		soundDecay_ = MARACA_SOUND_DECAY;
		decayScale_ = 0.97;
		SetEqualization( 1.0, -1.0, 0.0 );
	}

	shakeEnergy_ = 0.0;
	sndLevel_ = 0.0;
	nObjects_ = baseObjects_;
	systemDecay_ = baseDecay_;
	currentGain_ = log( nObjects_ ) * base_gain_ / nObjects_;

	for ( unsigned int i = 0; i < nResonances_; i++ )
		SetResonance( filters_[i], baseFrequencies_[i], baseRadii_[i] );
}

const double MAX_SHAKE = 1.0;

void Shakers::NoteOn( double frequency, double amplitude ) {
	int note_number = (int) ((12 * log(frequency / 220.0) / log(2.0)) + 57.01) % 32;

	if ( shakerType_ != note_number ) this->SetType( note_number );

	shakeEnergy_ += amplitude * MAX_SHAKE * 0.1;

	if ( shakeEnergy_ > MAX_SHAKE ) shakeEnergy_ = MAX_SHAKE;

	if ( shakerType_ == 19 || shakerType_ == 20 ) ratchetCount_ += 1;
}

void Shakers::NoteOff( double amplitude ) {
	shakeEnergy_ = 0.0;

	if ( shakerType_ == 19 || shakerType_ == 20 ) ratchetCount_ = 0;
}

void Shakers::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0, 128.0 ) == false ) {
		LOG("Shakers::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if ( number == __SK_Breath_ || number == __SK_AfterTouch_Cont_ ) {
		if ( shakerType_ == 19 || shakerType_ == 20 ) {
			if ( lastRatchetValue_ < 0.0 ) ratchetCount_++;
			else ratchetCount_ = (int) fabs(value - lastRatchetValue_);

			ratchetDelta_ = baseRatchetDelta_ * ratchetCount_;
			lastRatchetValue_ = (int) value;
		}
		else {
			shakeEnergy_ += normalizedValue * MAX_SHAKE * 0.1;

			if ( shakeEnergy_ > MAX_SHAKE ) shakeEnergy_ = MAX_SHAKE;
		}
	}
	else if ( number == __SK_ModFrequency_ )
		systemDecay_ = baseDecay_ + ( 2.0 * (normalizedValue - 0.5) * decayScale_ * (1.0 - baseDecay_) );
	else if ( number == __SK_FootControl_ ) {
		nObjects_ = (double) ( 2.0 * normalizedValue * baseObjects_ ) + 1.1;
		currentGain_ = log( nObjects_ ) * base_gain_ / nObjects_;
	}
	else if ( number == __SK_ModWheel_ ) {
		for ( unsigned int i = 0; i < nResonances_; i++ ) {
			double temp = baseFrequencies_[i] * pow( 4.0, normalizedValue - 0.5 );
			SetResonance( filters_[i], temp, baseRadii_[i] );
		}
	}
	else  if (number == __SK_ShakerInst_) {
		unsigned int type = (unsigned int) (value + 0.5);
		this->SetType( type );
	}

	#if defined(flagDEBUG)
	else {
		LOG("Shakers::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END

#ifndef _AudioCore_MESH2D_H
#define _AudioCore_MESH2D_H


NAMESPACE_AUDIO_BEGIN


const unsigned short NXMAX = 12;
const unsigned short NYMAX = 12;

class Mesh2D : public Instrument {
public:

	Mesh2D( unsigned short nX = NXMAX/2, unsigned short nY = NYMAX/2 );
	~Mesh2D();
	void Clear();
	void SetNX( unsigned short lenX );
	void SetNY( unsigned short lenY );
	void SetInputPosition( float xFactor, float yFactor );
	void SetDecay( float decayFactor );
	void NoteOn( float frequency, float amplitude );
	void NoteOff( float amplitude );
	float GetEnergy();
	float InputTick( float input );
	void ControlChange( int number, float value );
	float Tick( int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, int channel = 0 );

protected:

	float tick0();
	float tick1();
	void ClearMesh();

	unsigned short NX_, NY_;
	unsigned short xInput_, yInput_;
	OnePole  filterX_[NXMAX];
	OnePole  filterY_[NYMAX];
	float v_[NXMAX - 1][NYMAX - 1];
	float vxp_[NXMAX][NYMAX];
	float vxm_[NXMAX][NYMAX];
	float vyp_[NXMAX][NYMAX];
	float vym_[NXMAX][NYMAX];

	float vxp1_[NXMAX][NYMAX];
	float vxm1_[NXMAX][NYMAX];
	float vyp1_[NXMAX][NYMAX];
	float vym1_[NXMAX][NYMAX];

	int counter_;
};

inline AudioFrames& Mesh2D::Tick( AudioFrames& frames, int channel ) {
	int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Mesh2D::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	float* samples = &frames[channel];
	int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif

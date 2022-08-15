#ifndef _AudioCore_MESH2D_H
#define _AudioCore_MESH2D_H


NAMESPACE_AUDIO_BEGIN


const unsigned short NXMAX = 12;
const unsigned short NYMAX = 12;

class Mesh2D : public Instrument {
public:

	Mesh2D( unsigned short nX, unsigned short nY );
	~Mesh2D();
	void Clear();
	void SetNX( unsigned short lenX );
	void SetNY( unsigned short lenY );
	void SetInputPosition( double xFactor, double yFactor );
	void SetDecay( double decayFactor );
	void NoteOn( double frequency, double amplitude );
	void NoteOff( double amplitude );
	double GetEnergy();
	double InputTick( double input );
	void ControlChange( int number, double value );
	double Tick( unsigned int channel = 0 );
	AudioFrames& Tick( AudioFrames& frames, unsigned int channel = 0 );

protected:

	double tick0();
	double tick1();
	void ClearMesh();

	unsigned short NX_, NY_;
	unsigned short xInput_, yInput_;
	OnePole  filterX_[NXMAX];
	OnePole  filterY_[NYMAX];
	double v_[NXMAX - 1][NYMAX - 1];
	double vxp_[NXMAX][NYMAX];
	double vxm_[NXMAX][NYMAX];
	double vyp_[NXMAX][NYMAX];
	double vym_[NXMAX][NYMAX];

	double vxp1_[NXMAX][NYMAX];
	double vxm1_[NXMAX][NYMAX];
	double vyp1_[NXMAX][NYMAX];
	double vym1_[NXMAX][NYMAX];

	int counter_;
};

inline AudioFrames& Mesh2D::Tick( AudioFrames& frames, unsigned int channel ) {
	unsigned int channel_count = last_frame_.GetChannelCount();
	#if defined(flagDEBUG)

	if ( channel > frames.GetChannelCount() - channel_count ) {
		LOG("Mesh2D::Tick(): channel and AudioFrames arguments are incompatible!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	#endif
	double* samples = &frames[channel];
	unsigned int j, step = frames.GetChannelCount() - channel_count;

	if ( channel_count == 1 ) {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step )
			* samples++ = Tick();
	}
	else {
		for ( unsigned int i = 0; i < frames.GetFrameCount(); i++, samples += step ) {
			*samples++ = Tick();

			for ( j = 1; j < channel_count; j++ )
				*samples++ = last_frame_[j];
		}
	}

	return frames;
}

NAMESPACE_AUDIO_END

#endif

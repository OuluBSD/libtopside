#include "AudioCore.h"


NAMESPACE_AUDIO_BEGIN

Mesh2D::Mesh2D( unsigned short nX, unsigned short nY ) {
	if ( nX == 0.0 || nY == 0.0 ) {
		LOG("Mesh2D::Mesh2D: one or more argument is equal to zero!");
		HandleError( AudioError::FUNCTION_ARGUMENT );
	}

	this->SetNX( nX );
	this->SetNY( nY );
	double pole = 0.05;
	unsigned short i;

	for ( i = 0; i < NYMAX; i++ ) {
		filterY_[i].SetPole( pole );
		filterY_[i].SetGain( 0.99 );
	}

	for ( i = 0; i < NXMAX; i++ ) {
		filterX_[i].SetPole( pole );
		filterX_[i].SetGain( 0.99 );
	}

	this->ClearMesh();
	counter_ = 0;
	xInput_ = 0;
	yInput_ = 0;
}

Mesh2D::~Mesh2D() {
}

void Mesh2D::Clear() {
	this->ClearMesh();
	unsigned short i;

	for ( i = 0; i < NY_; i++ )
		filterY_[i].Clear();

	for ( i = 0; i < NX_; i++ )
		filterX_[i].Clear();

	counter_ = 0;
}

void Mesh2D::ClearMesh() {
	int x, y;

	for ( x = 0; x < NXMAX - 1; x++ ) {
		for ( y = 0; y < NYMAX - 1; y++ )
			v_[x][y] = 0;
	}

	for ( x = 0; x < NXMAX; x++ ) {
		for ( y = 0; y < NYMAX; y++ ) {
			vxp_[x][y] = 0;
			vxm_[x][y] = 0;
			vyp_[x][y] = 0;
			vym_[x][y] = 0;
			vxp1_[x][y] = 0;
			vxm1_[x][y] = 0;
			vyp1_[x][y] = 0;
			vym1_[x][y] = 0;
		}
	}
}

double Mesh2D::GetEnergy() {
	int x, y;
	double t;
	double e = 0;

	if ( counter_ & 1 ) {
		for ( x = 0; x < NX_; x++ ) {
			for ( y = 0; y < NY_; y++ ) {
				t = vxp1_[x][y];
				e += t * t;
				t = vxm1_[x][y];
				e += t * t;
				t = vyp1_[x][y];
				e += t * t;
				t = vym1_[x][y];
				e += t * t;
			}
		}
	}
	else {
		for ( x = 0; x < NX_; x++ ) {
			for ( y = 0; y < NY_; y++ ) {
				t = vxp_[x][y];
				e += t * t;
				t = vxm_[x][y];
				e += t * t;
				t = vyp_[x][y];
				e += t * t;
				t = vym_[x][y];
				e += t * t;
			}
		}
	}

	return e;
}

void Mesh2D::SetNX( unsigned short lenX ) {
	if ( lenX < 2 ) {
		LOG("Mesh2D::SetNX(" << lenX << "): Minimum GetCount is 2!");
		HandleError( AudioError::WARNING );
		return;
	}
	else if ( lenX > NXMAX ) {
		LOG("Mesh2D::SetNX(" << lenX << "): Maximum GetCount is " << NXMAX << '!');
		HandleError( AudioError::WARNING );
		return;
	}

	NX_ = lenX;
}

void Mesh2D::SetNY( unsigned short lenY ) {
	if ( lenY < 2 ) {
		LOG("Mesh2D::SetNY(" << lenY << "): Minimum GetCount is 2!");
		HandleError( AudioError::WARNING );
		return;
	}
	else if ( lenY > NYMAX ) {
		LOG("Mesh2D::SetNY(" << lenY << "): Maximum GetCount is " << NXMAX << '!');
		HandleError( AudioError::WARNING );
		return;
	}

	NY_ = lenY;
}

void Mesh2D::SetDecay( double decayFactor ) {
	if ( decayFactor < 0.0 || decayFactor > 1.0 ) {
		LOG("Mesh2D::SetDecay: decayFactor is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	int i;

	for ( i = 0; i < NYMAX; i++ )
		filterY_[i].SetGain( decayFactor );

	for (i = 0; i < NXMAX; i++)
		filterX_[i].SetGain( decayFactor );
}

void Mesh2D::SetInputPosition( double xFactor, double yFactor ) {
	if ( xFactor < 0.0 || xFactor > 1.0 ) {
		LOG("Mesh2D::SetInputPosition xFactor value is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	if ( yFactor < 0.0 || yFactor > 1.0 ) {
		LOG("Mesh2D::SetInputPosition yFactor value is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	xInput_ = (unsigned short) (xFactor * (NX_ - 1));
	yInput_ = (unsigned short) (yFactor * (NY_ - 1));
}

void Mesh2D::NoteOn( double frequency, double amplitude ) {
	if ( counter_ & 1 ) {
		vxp1_[xInput_][yInput_] += amplitude;
		vyp1_[xInput_][yInput_] += amplitude;
	}
	else {
		vxp_[xInput_][yInput_] += amplitude;
		vyp_[xInput_][yInput_] += amplitude;
	}
}

void Mesh2D::NoteOff( double amplitude ) {
	return;
}

double Mesh2D::InputTick( double input ) {
	if ( counter_ & 1 ) {
		vxp1_[xInput_][yInput_] += input;
		vyp1_[xInput_][yInput_] += input;
		last_frame_[0] = tick1();
	}
	else {
		vxp_[xInput_][yInput_] += input;
		vyp_[xInput_][yInput_] += input;
		last_frame_[0] = tick0();
	}

	counter_++;
	return last_frame_[0];
}

double Mesh2D::Tick( unsigned int ) {
	last_frame_[0] = ((counter_ & 1) ? this->tick1() : this->tick0());
	counter_++;
	return last_frame_[0];
}

const double VSCALE = 0.5;

double Mesh2D::tick0() {
	int x, y;
	double outsamp = 0;

	for (x = 0; x < NX_ - 1; x++) {
		for (y = 0; y < NY_ - 1; y++) {
			v_[x][y] = ( vxp_[x][y] + vxm_[x + 1][y] +
						 vyp_[x][y] + vym_[x][y + 1] ) * VSCALE;
		}
	}

	for (x = 0; x < NX_ - 1; x++) {
		for (y = 0; y < NY_ - 1; y++) {
			double vxy = v_[x][y];
			vxp1_[x + 1][y] = vxy - vxm_[x + 1][y];
			vyp1_[x][y + 1] = vxy - vym_[x][y + 1];
			vxm1_[x][y] = vxy - vxp_[x][y];
			vym1_[x][y] = vxy - vyp_[x][y];
		}
	}

	for (y = 0; y < NY_ - 1; y++) {
		vxp1_[0][y] = filterY_[y].Tick(vxm_[0][y]);
		vxm1_[NX_ - 1][y] = vxp_[NX_ - 1][y];
	}

	for (x = 0; x < NX_ - 1; x++) {
		vyp1_[x][0] = filterX_[x].Tick(vym_[x][0]);
		vym1_[x][NY_ - 1] = vyp_[x][NY_ - 1];
	}

	outsamp = vxp_[NX_ - 1][NY_ - 2] + vyp_[NX_ - 2][NY_ - 1];
	return outsamp;
}

double Mesh2D::tick1() {
	int x, y;
	double outsamp = 0;

	for (x = 0; x < NX_ - 1; x++) {
		for (y = 0; y < NY_ - 1; y++) {
			v_[x][y] = ( vxp1_[x][y] + vxm1_[x + 1][y] +
						 vyp1_[x][y] + vym1_[x][y + 1] ) * VSCALE;
		}
	}

	for (x = 0; x < NX_ - 1; x++) {
		for (y = 0; y < NY_ - 1; y++) {
			double vxy = v_[x][y];
			vxp_[x + 1][y] = vxy - vxm1_[x + 1][y];
			vyp_[x][y + 1] = vxy - vym1_[x][y + 1];
			vxm_[x][y] = vxy - vxp1_[x][y];
			vym_[x][y] = vxy - vyp1_[x][y];
		}
	}

	for (y = 0; y < NY_ - 1; y++) {
		vxp_[0][y] = filterY_[y].Tick(vxm1_[0][y]);
		vxm_[NX_ - 1][y] = vxp1_[NX_ - 1][y];
	}

	for (x = 0; x < NX_ - 1; x++) {
		vyp_[x][0] = filterX_[x].Tick(vym1_[x][0]);
		vym_[x][NY_ - 1] = vyp1_[x][NY_ - 1];
	}

	outsamp = vxp1_[NX_ - 1][NY_ - 2] + vyp1_[NX_ - 2][NY_ - 1];
	return outsamp;
}

void Mesh2D::ControlChange( int number, double value ) {
	#if defined(flagDEBUG)

	if ( Audio::InRange( value, 0.0, 128.0 ) == false ) {
		LOG("Mesh2D::controlChange: value (" << value << ") is out of range!");
		HandleError( AudioError::WARNING );
		return;
	}

	#endif
	double normalizedValue = value * ONE_OVER_128;

	if ( number == 2 )
		this->SetNX( (unsigned short) (normalizedValue * (NXMAX - 2) + 2) );
	else if ( number == 4 )
		this->SetNY( (unsigned short) (normalizedValue * (NYMAX - 2) + 2) );
	else if ( number == 11 )
		this->SetDecay( 0.9 + (normalizedValue * 0.1) );
	else if ( number == __SK_ModWheel_ )
		this->SetInputPosition( normalizedValue, normalizedValue );

	#if defined(flagDEBUG)
	else {
		LOG("Mesh2D::controlChange: undefined Control number (" << number << ")!");
		HandleError( AudioError::WARNING );
	}

	#endif
}

NAMESPACE_AUDIO_END

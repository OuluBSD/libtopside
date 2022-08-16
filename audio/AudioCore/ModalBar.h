#ifndef _AudioCore_MODALBAR_H
#define _AudioCore_MODALBAR_H


NAMESPACE_AUDIO_BEGIN

class ModalBar : public Modal {
public:

	ModalBar();
	~ModalBar();
	void SetStickHardness( double hardness );
	void SetStrikePosition( double position );
	void SetPreset( int preset );
	void SetModulationDepth( double mod_depth );
	void ControlChange( int number, double value ) override;
};

NAMESPACE_AUDIO_END

#endif

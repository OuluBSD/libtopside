#ifndef _AudioCore_MODALBAR_H
#define _AudioCore_MODALBAR_H


NAMESPACE_AUDIO_BEGIN

class ModalBar : public Modal {
public:

	ModalBar();
	~ModalBar();
	void SetStickHardness( float hardness );
	void SetStrikePosition( float position );
	void SetPreset( int preset );
	void SetModulationDepth( float mod_depth );
	void ControlChange( int number, float value ) override;
};

NAMESPACE_AUDIO_END

#endif

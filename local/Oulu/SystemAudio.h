#ifndef _Oulu_SystemAudio_h_
#define _Oulu_SystemAudio_h_


NAMESPACE_UPP


class SystemAudio : public Oulu::AudioProxy {
public:
	
	
};

/*struct VirtualAudio {
	virtual SystemAudio&	BeginPlay() = 0;
	virtual void			CommitPlay() = 0;
	virtual bool			IsAudioSampleFloating() = 0;
	virtual int				GetAudioSampleSize() = 0;
	virtual int				GetAudioSampleRate() = 0;
	virtual int				GetAudioChannels() = 0;
	virtual int				GetAudioFrequency() = 0;
	virtual void			UndoPlay() = 0;
	
};

extern VirtualAudio* VirtualAudioPtr;*/


//#define SOUNDPLATFORM_CTRL_TOP_DECLS   Ctrl *owner_window;
//#define SOUNDPLATFORM_CTRL_DECLS_INCLUDE <VirtualAudioAlt/Ctrl.h>
//#define SOUNDPLATFORM_TOPWINDOW_DECLS_INCLUDE <VirtualAudioAlt/Top.h>
//#define SOUNDPLATFORM_INCLUDE_AFTER <VirtualAudioAlt/After.h>
//#define SOUNDPLATFORM_INCLUDE_AFTER_ECSLIB <VirtualAudioAlt/AfterEcsLib.h>


END_UPP_NAMESPACE

#endif

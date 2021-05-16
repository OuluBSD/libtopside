#ifndef _Local_SystemAudio_h_
#define _Local_SystemAudio_h_


NAMESPACE_UPP


class SystemAudio : public Topside::AudioProxy {
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
//#define SOUNDPLATFORM_CTRL_DECLS_INCLUDE <VirtualAudio/Ctrl.h>
//#define SOUNDPLATFORM_TOPWINDOW_DECLS_INCLUDE <VirtualAudio/Top.h>
//#define SOUNDPLATFORM_INCLUDE_AFTER <VirtualAudio/After.h>
//#define SOUNDPLATFORM_INCLUDE_AFTER_ECSLIB <VirtualAudio/AfterEcsLib.h>


END_UPP_NAMESPACE

#endif

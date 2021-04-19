#ifndef _VirtualSound_VirtualSound_h_
#define _VirtualSound_VirtualSound_h_


#ifdef flagALTCORE
	#include <CoreAlt/Core.h>
#else
	#include <Core/Core.h>
#endif

#include <Oulu/Before.h>
#include <Oulu/Sound.h>


NAMESPACE_UPP


class SystemSound : public Oulu::SoundProxy {
public:
	
	
};

/*struct VirtualSound {
	virtual SystemSound&	BeginPlay() = 0;
	virtual void			CommitPlay() = 0;
	virtual bool			IsAudioSampleFloating() = 0;
	virtual int				GetAudioSampleSize() = 0;
	virtual int				GetAudioSampleRate() = 0;
	virtual int				GetAudioChannels() = 0;
	virtual int				GetAudioFrequency() = 0;
	virtual void			UndoPlay() = 0;
	
};

extern VirtualSound* VirtualSoundPtr;*/


//#define SOUNDPLATFORM_CTRL_TOP_DECLS   Ctrl *owner_window;
//#define SOUNDPLATFORM_CTRL_DECLS_INCLUDE <VirtualSoundAlt/Ctrl.h>
//#define SOUNDPLATFORM_TOPWINDOW_DECLS_INCLUDE <VirtualSoundAlt/Top.h>
//#define SOUNDPLATFORM_INCLUDE_AFTER <VirtualSoundAlt/After.h>
//#define SOUNDPLATFORM_INCLUDE_AFTER_ECSLIB <VirtualSoundAlt/AfterEcsLib.h>


END_UPP_NAMESPACE




NAMESPACE_UPP



END_UPP_NAMESPACE

#endif

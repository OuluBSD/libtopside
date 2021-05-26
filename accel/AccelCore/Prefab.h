#ifndef _AccelCore_Prefab_h_
#define _AccelCore_Prefab_h_

NAMESPACE_TOPSIDE_BEGIN


/*PREFAB_BEGIN(CompleteAccel)
		AccelDisplaySource,
		AccelAudioSource,
		AccelContextComponent
PREFAB_END*/

/*PREFAB_BEGIN(VideoOnlyAccel)
		AccelDisplaySource,
		AccelContextComponent
PREFAB_END*/

PREFAB_BEGIN(AudioOnlyAccel)
		AccelAudioConvertInputComponent,
		AccelAudioPipeComponent,
		AccelAudioConvertOutputComponent,
		AccelContextComponent
PREFAB_END


NAMESPACE_TOPSIDE_END

#endif

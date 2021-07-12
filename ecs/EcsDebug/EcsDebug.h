#ifndef _EcsDebug_EcsDebug_h_
#define _EcsDebug_EcsDebug_h_

#include <EcsLib/EcsLib.h>
#include <EcsAudioCore/EcsAudioCore.h>

#include "AudioGenerator.h"
#include "SideExt.h"
#include "ConvExt.h"
#include "SoundCard.h"
#include "Verifier.h"
#include "Testers.h"
#include "Mixer.h"



NAMESPACE_ECS_BEGIN



void DebugMain(String eon_file, VectorMap<String,Object>& args, MachineVerifier* ver=0, bool dbg_ref_visits=false, uint64 dbg_ref=0);


NAMESPACE_ECS_END

#endif

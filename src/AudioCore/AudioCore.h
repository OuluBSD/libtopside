#ifndef _AudioCore_AudioCore_h_
#define _AudioCore_AudioCore_h_

#if (defined(__OS_IRIX__) || defined(__OS_LINUX__) || defined(__OS_MACOSX__))
	#include <unistd.h>
#elif defined(__OS_WINDOWS__)
	#include <windows.h>
#endif

#include <sys/stat.h>

#include <Local/Local.h>
#include <Geometry/Geometry.h>
#include <MidiFile/MidiFile.h>


#define NAMESPACE_AUDIO_BEGIN NAMESPACE_TOPSIDE_BEGIN namespace Audio {
#define NAMESPACE_AUDIO_END   NAMESPACE_TOPSIDE_END }

#define DEFAULT_LOWEST_FREQ 60

#include "Audio.h"
#include "Instrument.h"
#include "Filter.h"
#include "Function.h"
#include "Generator.h"
#include "Effect.h"

#include "DelayL.h"
#include "DelayA.h"
#include "ReedTable.h"
#include "PoleZero.h"
#include "SineWave.h"
#include "Noise.h"
#include "Envelope.h"
#include "OneZero.h"
#include "TwoZero.h"
#include "JetTable.h"
#include "OnePole.h"
#include "ADSR.h"
#include "BiQuad.h"
#include "BowTable.h"
#include "Fir.h"
#include "Iir.h"

#include "Twang.h"

#include "WaveIn.h"
#include "WaveOut.h"
#include "FileRead.h"
#include "FileWaveIn.h"
#include "FileLoop.h"
#include "FileWrite.h"
#include "FileWaveOut.h"

#include "FM.h"
#include "Modulate.h"
#include "SingWave.h"
#include "FormSwep.h"
#include "Sampler.h"
#include "Modal.h"
#include "Delay.h"
#include "Sphere.h"

#include "Clarinet.h"
#include "BlowHole.h"
#include "Saxofony.h"
#include "Flute.h"
#include "Brass.h"
#include "BlowBottle.h"
#include "Bowed.h"
#include "Plucked.h"
#include "StifKarp.h"
#include "Sitar.h"
#include "Mandolin.h"
#include "Rhodey.h"
#include "Wurley.h"
#include "TubeBell.h"
#include "HeavyMetal.h"
#include "PercFlut.h"
#include "BeeThree.h"
#include "FMVoices.h"
#include "VoiceFormant.h"
#include "Moog.h"
#include "Simple.h"
#include "Drummer.h"
#include "BandedWaveGuide.h"
#include "Shakers.h"
#include "ModalBar.h"
#include "Mesh2D.h"
#include "Resonate.h"
#include "Whistle.h"

#include "Voicer.h"
#include "JCRev.h"


#include "DevWaveOut.h"

#include "ScriptTbl.h"
#include "Script.h"
#include "Messenger.h"
#include "ScriptMsg.h"


#include "Asymptionic.h"
#include "BlitSaw.h"
#include "BlitSquare.h"
#include "Blit.h"
#include "Chorus.h"
#include "Echo.h"
#include "Phonemes.h"
#include "FreeVerb.h"
#include "Granulate.h"
#include "Guitar.h"
#include "LentPitchShift.h"
#include "MidiFileIn.h"
#include "PitchShift.h"
#include "PRCRev.h"
#include "TapDelay.h"
#include "TwoPole.h"
#include "NRev.h"

#include "Compressor.h"

#endif

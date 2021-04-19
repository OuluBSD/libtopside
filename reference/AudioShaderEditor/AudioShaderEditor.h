#ifndef _AudioShaderEditor_AudioShaderEditor_h
#define _AudioShaderEditor_AudioShaderEditor_h

#include <Complete/Complete.h>
using namespace Upp;

#define LAYOUTFILE <AudioShaderEditor/AudioShaderEditor.lay>
#include <CtrlCore/lay.h>


#include "Editor.h"


NAMESPACE_OULU_BEGIN




class AudioShaderEditor :
	public TopWindow
{
	TabMgrCtrl tabs;
	
	TimeCallback tc, data_tc;
	TimeStop ts;
	
	void MachineUpdater();
	
	
public:
	typedef AudioShaderEditor CLASSNAME;
	AudioShaderEditor();
	
	bool InitializeDefault(String audio_path);
	
	void Updated() override;
	void OnError();
	
	
};



void Startup();


NAMESPACE_OULU_END


#endif

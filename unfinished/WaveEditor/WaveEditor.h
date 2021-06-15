#ifndef _WaveEditor_WaveEditor_h_
#define _WaveEditor_WaveEditor_h_

#include <AudioCtrl/AudioCtrl.h>


NAMESPACE_TOPSIDE_BEGIN

class WaveEditor : public TopWindow {
	
protected:
	friend class AudioViewCtrl;
	friend class AudioPlotCtrl;
	friend class AudioHeatmapCtrl;
	Record file;
	
	AudioViewCtrl view;
	
public:
	typedef WaveEditor CLASSNAME;
	WaveEditor();
	~WaveEditor();
	
	ToolBar tool;
	
	void RefreshToolBar();
	void ToolMenu(Bar& bar);
	void MainMenu(Bar& bar);
	
	void OpenFilePath(String s);
	void CloseFile();
	
	void PopupMainMenu();
	void NewFile();
	void OpenFile();
	void SaveFile();
	void Play();
	void Pause();
	void Stop();
	
	
	void LowPass(double f);
	void BandPass(double f1, double f2);
	void HighPass(double f);
	void Reverb();
	
};

NAMESPACE_TOPSIDE_END

#endif

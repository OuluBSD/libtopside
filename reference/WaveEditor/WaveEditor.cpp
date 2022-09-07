#include "WaveEditor.h"

NAMESPACE_TOPSIDE_BEGIN

WaveEditor::WaveEditor() {
	Title("WaveEditor");
	MaximizeBox(true);
	MinimizeBox(true);
	Sizeable();
	
	AddFrame(tool);
	RefreshToolBar();
	
	Add(view.SizePos());
	
}

WaveEditor::~WaveEditor() {
	file.Clear();
}

void WaveEditor::OpenFilePath(String s) {
	if (file) CloseFile();
	
	
	file = StreamRecord::LoadAny(s);
	
	view.RefreshData();
	
}

void WaveEditor::CloseFile() {
	if (!file) return;
	if (PromptYesNo("Do you want to save current file?"))
		SaveFile();
	file.Clear();
}

void WaveEditor::RefreshToolBar() {
	tool.Clear();
	tool.Set(THISBACK(ToolMenu));
}

void WaveEditor::ToolMenu(Bar& bar) {
	
	bar.Add(Images::view_list_details_symbolic(), THISBACK(PopupMainMenu));
	bar.Separator();
	bar.Add("New File", Images::document_new(), THISBACK(NewFile));
	bar.Add("Open File", Images::document_open(), THISBACK(OpenFile));
	bar.Add("Save File", Images::document_save(), THISBACK(SaveFile));
	bar.Separator();
	bar.Add("Play", Images::media_playback_start(), THISBACK(Play));
	bar.Add("Pause", Images::media_playback_pause(), THISBACK(Pause));
	bar.Add("Stop", Images::media_playback_stop(), THISBACK(Stop));
	
}

void WaveEditor::MainMenu(Bar& bar) {
	bar.Add("Low-pass", THISBACK1(LowPass, 0.6));
	bar.Add("Band-pass", THISBACK2(BandPass, 0.2, 0.6));
	bar.Add("High-pass", THISBACK1(HighPass, 0.4));
	bar.Separator();
	bar.Add("Reverb", THISBACK(Reverb));
	
}

void WaveEditor::PopupMainMenu() {
	MenuBar::Execute(THISBACK(MainMenu));
}

void WaveEditor::NewFile() {
	
}

void WaveEditor::OpenFile() {
	PromptOK("THIS IS UNIMPLIMENTED YET. Run this program with the wav file path as argument. (WAV must be 16-bit unsigned, not 32-float. Also, it should be < 20 seconds.)");
}

void WaveEditor::SaveFile() {
	
}

void WaveEditor::Play() {
	if (!file) return;
	
	#ifndef flagFREEBSD
	PromptOK("Audio backend is not implemented in this system");
	return;
	#endif
	
	SoundOutStream s = SoundOutStream::OpenDefault();
	if (!s) return;
	
	s.Put(file);
}

void WaveEditor::Pause() {
	
}

void WaveEditor::Stop() {
	
}

void WaveEditor::LowPass(double f) {
	
	if (!file) return;
	
	/*double freq = AudioCore::GetFrequency(f, 300, 5000);
	
	LowPass lp;
	lp.SetFrequency(freq);
	lp.Process(*file);
	
	view.RefreshData();*/
	
}

void WaveEditor::BandPass(double f1, double f2) {
	
	if (!file) return;
	
	/*double freq1 = AudioCore::GetFrequency(f1, 300, 5000);
	double freq2 = AudioCore::GetFrequency(f2, 300, 5000);
	
	AudioCore::BandPass bp;
	bp.SetFrequency(freq1, freq2);
	bp.Process(*file);
	
	view.RefreshData();*/
	
}

void WaveEditor::HighPass(double f) {
	
	if (!file) return;
	
	/*double freq = AudioCore::GetFrequency(f, 300, 5000);
	
	AudioCore::HighPass hp;
	hp.SetFrequency(freq);
	hp.Process(*file);
	
	view.RefreshData();*/
	
}

void WaveEditor::Reverb() {
	
	if (!file) return;
	
	/*AudioCore::Reverb rv;
	
	rv.Process(*file);
	
	view.RefreshData();*/
	
}

NAMESPACE_TOPSIDE_END



GUI_APP_MAIN {
	TS::WaveEditor ed;
	
	const auto& args = CommandLine();
	if (args.GetCount())
		ed.OpenFilePath(args.Top());
	
	ed.Run();
}


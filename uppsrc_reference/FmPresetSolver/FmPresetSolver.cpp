#include "FmPresetSolver.h"



FmPresetSolver::FmPresetSolver() {
	
}

	
bool FmPresetSolver::LoadFile(String path) {
	Vector<String> lines = Split(UPP::LoadFile(path), "\n");
	
	VectorMap<String, int> notes;
	notes.Add("C",   0);
	notes.Add("C#",  1);
	notes.Add("D",   2);
	notes.Add("D#",  3);
	notes.Add("E",   4);
	notes.Add("F",   5);
	notes.Add("F#",  6);
	notes.Add("G",   7);
	notes.Add("G#",  8);
	notes.Add("A",   9);
	notes.Add("A#", 10);
	notes.Add("B",  11);
	
	Sample& s = samples.Add();
	s.src_file = path;
	s.directory = GetFileDirectory(path);
	
	for (String line : lines) {
		Vector<String> parts = Split(line, ":");
		for (String& p : parts) p = TrimBoth(p);
		
		if (parts.GetCount() == 2) {
			String key = parts[0];
			String value = parts[1];
			LOG(key << ": " << value);
			
			if (key == "note") {
				String n12;
				String oct;
				if (value.Mid(1,1) == "#") {
					n12 = value.Left(2);
					oct = value.Mid(2);
				}
				else {
					n12 = value.Left(1);
					oct = value.Mid(1);
				}
				
				int i = notes.Get(n12, -1);
				int j = StrInt(oct);
				if (i >= -1) {
					s.note = (2 + j) * 12 + i;
					s.freq = SoftSynth::Voice::NoteToFrequency(s.note);
				}
			}
			else if (key == "standard") {
				s.std = StrInt(value);
			}
			else if (key == "sample") {
				s.filepath = value;
				if (!FileExists(value))
					s.filepath = AppendFileName(GetFileDirectory(path), s.filepath);
				
				String tmp = AppendFileName(GetHomeDirectory(), "tmp.pcm");
				DeleteFile(tmp);
				
				String cmd = "ffmpeg -i \"" + s.filepath + "\" -f f32le -ac 2 -ar 44100 \"" + tmp + "\"", out;
				LOG(cmd);
				Sys(cmd, out);
				
				String pcm = UPP::LoadFile(tmp);
				const char* c = pcm.Begin();
				int samples = pcm.GetCount() / (4*2);
				
				s.data.SetCount(2);
				Vector<float>& l = s.data[0];
				Vector<float>& r = s.data[1];
				l.Clear();
				r.Clear();
				const float* f = (const float*)c;
				for(int i = 0; i < samples; i++) {
					l.Add(f[0]);
					r.Add(f[1]);
					f += 2;
				}
				
				//if (GetHashValue(l) == GetHashValue(r))
				//	s.data.SetCount(1);
				
				//DUMPC(l);
				
			}
		}
		
		
	}
	
	DUMPC(samples);
	
	return true;
}

void FmPresetSolver::Solve() {
	for (Sample& s : samples) {
		Solve(s);
	}
}

void FmPresetSolver::Solve(Sample& s) {
	COUTLOG("Solving sample " << s.filepath);
	
	s.syn.Init(44100);
	
	int params = SoftSynth::PARAM_END;
	int ops = SYNTH_OPERATORS;
	int dimension = ops * params;
	#ifdef flagDEBUG
	int population = 10;
	int generations = 1;
	#else
	int population = 20;
	int generations = 10;
	#endif
	
	s.opt.SetMaxGenerations(generations);
	s.opt.SetRandomTypeManual();
	s.opt.Init(dimension, population);
	
	Index<String> presets;
	presets.Add("angry_overture.fmp");
	presets.Add("clocky.fmp");
	presets.Add("expressive_harp.fmp");
	presets.Add("lead_pad.fmp");
	presets.Add("old_school_organ.fmp");
	presets.Add("retro_sci_fi.fmp");
	presets.Add("square_emotions.fmp");
	
	Vector<Vector<double>> preset_values;
	for (String p : presets) {
		Vector<double>& pv = preset_values.Add();
		pv.SetCount(dimension);
		
		String file = RealizeShareFile("presets/fmsynth/presets/" + p);
		String content = TS::LoadFile(file);
		
		SoftSynth::FmSynth::PresetMetadata meta;
		s.syn.Reset();
		SoftSynth::Status status = s.syn.LoadPreset(meta, content.Begin(), content.GetCount());
		ASSERT((int)status == 0);
		
		double* d = pv.Begin();
		double* d_end = pv.End();
		for(int i = 0; i < SYNTH_OPERATORS; i++) {
			float* param = (float*)&s.syn.params.voices[i].amp;
			for(int j = 0; j < SoftSynth::PARAM_END; j++) {
				ASSERT(d != d_end);
				*d++ = param[j];
			}
		}
	}
	
	for (int i = 0; i < population; i++) {
		const Vector<double>& preset = preset_values[i % preset_values.GetCount()];
		for (int j = 0; j < dimension; j++)
			s.opt.population[i][j] = preset[j] + (Randomf() - 0.5) * 0.01;
	}
	
	Vector<Vector<float>> trial_sound;
	trial_sound.SetCount(s.data.GetCount());
	for(int i = 0; i < s.data.GetCount(); i++)
		trial_sound[i].SetCount(s.data[i].GetCount());
	Vector<float>& trial_l = trial_sound[0];
	Vector<float>& trial_r = trial_sound[1];
	float* trial_lp = trial_l.Begin();
	float* trial_rp = trial_r.Begin();
	int samples = min(trial_l.GetCount(), trial_r.GetCount());
	
	const float* orig_lp = s.data[0].Begin();
	const float* orig_rp = s.data[1].Begin();
	
	FFT1 orig_fft(s.data[0]);
	orig_fft.ForwardFFT();
	orig_fft.FFTShift();
	const Vector<Complex>& orig_fft_v = orig_fft.GetFFTShifted();
	
	double best = -DBL_MAX;
	int iter = 0;
	while (!s.opt.IsEnd()) {
		const Vector<double>& trial = s.opt.GetTrialSolution();
		
		if (iter % population == 0) {
			int gen = iter / population;
			COUTLOG("Starting generation " << gen+1 << "/" << generations);
		}
		
		s.syn.Reset();
		
		s.opt.Start();
		
		const double* d = trial.Begin();
		const double* d_end = trial.End();
		for(int i = 0; i < SYNTH_OPERATORS; i++) {
			float* param = (float*)&s.syn.params.voices[i].amp;
			for(int j = 0; j < SoftSynth::PARAM_END; j++) {
				ASSERT(d != d_end);
				param[j] = (float)*d++;
			}
		}
		
		s.syn.NoteOn(s.note, 127);
		
		memset(trial_lp, 0, samples * sizeof(float));
		memset(trial_rp, 0, samples * sizeof(float));
		s.syn.Render(trial_lp, trial_rp, samples);
		
		// TODO fft comparison
		#if 1
		OnlineAverage av, trial_mean;
		for(int i = 0; i < samples; i++) {
			float l = trial_lp[i];
			float r = trial_rp[i];
			float l_diff = fabsf(l - orig_lp[i]);
			float r_diff = fabsf(r - orig_rp[i]);
			ASSERT(IsFin(l_diff));
			ASSERT(IsFin(r_diff));
			av.Add(l_diff);
			av.Add(r_diff);
			trial_mean.Add(fabsf(l));
			trial_mean.Add(fabsf(r));
		}
		// detect silence
		double mean_difference = av.GetMean();
		if (trial_mean.GetMean() < 0.01)
			mean_difference = FLT_MAX;
		
		#else
		OnlineAverage av;
		FFT1 trial_fft(trial_l);
		trial_fft.ForwardFFT();
		trial_fft.FFTShift();
		const Vector<Complex>& trial_fft_v = trial_fft.GetFFTShifted();
		int c = trial_fft_v.GetCount();
		for(int i = 0; i < c; i++) {
			const Complex& c0 = orig_fft_v[i];
			const Complex& c1 = trial_fft_v[i];
			double diff = fabs(c0.imag() - c1.imag()) + fabs(c0.real() - c1.real());
			av.Add(diff);
		}
		double mean_difference = av.GetMean();
		#endif
		
		s.opt.Stop(-mean_difference);
		
		if (-mean_difference > best) {
			best = -mean_difference;
			COUTLOG("Iter " << iter << " New best: " << best);
		}
		
		
		//const Vector<double>& best = s.opt.GetBestSolution();
		
		iter++;
	}
	
	COUTLOG("Final best: " << best);
	//DUMPC(s.opt.GetBestSolution());
	
	const Vector<double>& best_sol = s.opt.GetBestSolution();
	s.syn.Reset();
	const double* d = best_sol.Begin();
	const double* d_end = best_sol.End();
	for(int i = 0; i < SYNTH_OPERATORS; i++) {
		float* param = (float*)&s.syn.params.voices[i].amp;
		for(int j = 0; j < SoftSynth::PARAM_END; j++) {
			ASSERT(d != d_end);
			param[j] = (float)*d++;
		}
	}
	
	
	int preset_sz = s.syn.GetPresetSize();
	Vector<byte> preset;
	preset.SetCount(preset_sz, 0);
	SoftSynth::FmSynth::PresetMetadata meta;
	meta.name = GetFileTitle(s.filepath);
	s.syn.SavePreset(meta, (byte*)preset.Begin(), preset_sz);
	
	String preset_path = AppendFileName(s.directory, GetFileTitle(s.src_file) + ".fmp");
	COUTLOG("Preset path: " << preset_path);
	FileOut fout(preset_path);
	fout.Put((byte*)preset.Begin(), preset_sz);
	fout.Close();
}

	
CONSOLE_APP_MAIN {
	#ifdef flagWIN32
		#error Todo Win32 directory
	#endif
	
	SetCoutLog();
	
	COUTLOG("THIS DOES NOT WORK!");
	COUTLOG("This was just a curiosity.");
	
	String dir = AppendFileName(GetHomeDirectory(), "libtopside/share/presets/fmsynth/generated");
	
	Index<String> files;
	GetDirectoryFiles(dir, files);
	
	for (String path : files) {
		String ext = GetFileExt(path);
		if (ext != ".in")
			continue;
		
		COUTLOG(path);
		
		FmPresetSolver s;
		
		if (!s.LoadFile(path))
			break;
		
		s.Solve();
		
	}
	
}

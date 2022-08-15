#ifndef _FmPresetSolver_FmPresetSolver_h_
#define _FmPresetSolver_FmPresetSolver_h_

#include <Local/Local.h>
#include <SoftSynth/SoftSynth.h>
using namespace TS;


struct FmPresetSolver {
	
	struct Sample {
		int note = -1;
		int std = -1;
		float freq = 0;
		String filepath;
		Vector<Vector<float>> data;
		SoftSynth::FmSynth syn;
		GeneticOptimizer opt;
		String src_file;
		String directory;
		
		String ToString() const {
			String s = "note: " + IntStr(note) + ", freq: " + DblStr(freq) + ", std: " + IntStr(std) + ", file: " + filepath;
			return s;
		}
		
		void LoadSound();
	};
	
	Array<Sample> samples;
	
	FmPresetSolver();
	bool LoadFile(String path);
	
	
	void Solve();
	void Solve(Sample& s);
	
};

#endif

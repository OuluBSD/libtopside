#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN


void BuildModel(PCFG& pcfg) {
	String model_path = ConfigFile("PcfgModel.bin");
	
	if (FileExists(model_path)) {
		pcfg.LoadModel(model_path);
		return;
	}
	
	LOG("Building the Grammar Model");
	TimeStop ts;
	
	String natlang_dir = ShareDirFile("natlang");
	
	String tmp_dir = ConfigFile("tmp");
	RealizeDirectory(tmp_dir);
	if (!DirectoryExists(tmp_dir)) {LOG("Failed to create temp directory"); return;}
	
	// Normalise the treebanks
	String questionbank_norm = ConfigFile("tmp") + DIR_SEPS + "4000qs.json";
	if (!FileExists(questionbank_norm)) {
		String questionbank_data = AppendFileName(natlang_dir, "QuestionBank" DIR_SEPS "4000qs.txt");
		String questionbank_penn_data = ConfigFile("tmp") + DIR_SEPS "penn_4000qs.txt";
		
		NormalizeQuestionbank(questionbank_data, questionbank_penn_data);
		
		Vector<String> paths;
		paths.Add(questionbank_penn_data);
		GenerateNormal(questionbank_norm, paths);
	}
	
	String penntreebank_norm = ConfigFile("tmp") + DIR_SEPS + "penn_treebank.json";
	if (!FileExists(penntreebank_norm)) {
		Vector<String> paths;
		FindFile ff;
		if (ff.Search(AppendFileName(natlang_dir, "PennTreebank" DIR_SEPS "*.mrg"))) {
			do {
				paths.Add(ff.GetPath());
			}
			while (ff.Next());
		}
		GenerateNormal(penntreebank_norm, paths);
	}
	
	String treebank_model_path = ConfigFile("tmp") + DIR_SEPS + "model_treebank.json";
	{
		int i = 0;
		FileOut model(treebank_model_path);
		FileOut dat(ConfigFile("tmp") + DIR_SEPS + "test.dat");
		FileOut key(ConfigFile("tmp") + DIR_SEPS + "test.key");
		
		for(int i = 0; i < 2; i++) {
			String treebank = i == 0 ? questionbank_norm : penntreebank_norm;
			FileIn fin(treebank);
			while (!fin.IsEof()) {
				String line = fin.GetLine();
				i++;
				if ((i % 100) == 0) {
					One<Node> n;
					n.Create();
					LoadFromJson(*n, line);
					int words = 0;
					WString sentence = GetSentence(*n, words);
					//LOG(sentence);
					if (words > 7 && words < 20) {
						dat.PutLine(sentence.ToString());
						key.PutLine(line);
					}
					else
						i--;
				}
				model.PutLine(line);
			}
		}
	}
	
	// Learn PCFG
	Vector<String> paths;
	paths.Add(treebank_model_path);
	pcfg.LearnFromTreebanks(paths);
	pcfg.SaveModel(model_path);
	
	LOG("Building took " << ts.ToString());
}


NAMESPACE_LANGUAGE_END

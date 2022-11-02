#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN


String GetAceEnglish(String txt, String erg_file, String dir) {
	if (erg_file.IsEmpty())
		erg_file = "erg-2018-x86-64-0.9.34.dat";
	if (dir.IsEmpty())
		dir = GetHomeDirFile("bin");
	
	txt = GetSentenceLines(txt);
	
	String exe = AppendFileName(dir, "ace");
	String erg = AppendFileName(dir, erg_file);
	String input = ConfigFile("ace.in");
	String cmd = exe + " -f \"" + input + "\" -g \"" + erg + "\"  -1 --report-labels";
	//LOG(cmd);
	
	static StaticMutex lock;
	lock.Enter();
	
	String ace_out;
	Vector<String> lines = Split(txt, "\n");
	for(int i = 0; i < lines.GetCount(); i++) {
		String line = lines[i];
		FileOut fout(input);
		fout << line;
		fout.Close();
		
		String out;
		Sys(cmd, out);
		
		ace_out += out + "\n\n";
	}
	
	lock.Leave();
	
	
	return ace_out;
}


bool AceParser::Parse(String txt) {
	root.Create();
	root->SetType(NODE_ROOT);
	
	int sent = 0;
	while (sent >= 0 && sent < txt.GetCount()) {
		
		int next_sent = txt.Find("\nSENT: ", sent+1);
		if (next_sent == -1)
			next_sent = txt.GetCount();
		
		String sent_data = txt.Mid(sent, next_sent-sent);
		//LOG(sent_data);
		
		int a = sent_data.Find("RELS: < [ ");
		lemmas.Clear();
		if (a >= 0) {
			a += 11;
			int b = sent_data.Find("_", a);
			String lemma;
			if (b >= 0)
				lemma = sent_data.Mid(a, b-a);
			lemmas.Add(lemma);
			
			while ((a = sent_data.Find("\n [ _", a+1)) >= 0) {
				a += 5;
				b = sent_data.Find("_", a);
				String lemma;
				if (b >= 0)
					lemma = sent_data.Mid(a, b-a);
				lemmas.Add(lemma);
			}
		}
		
		//DUMPC(lemmas);
		
		a = sent_data.Find("ICONS: <");
		if (a >= 0)
			a = sent_data.Find(";", a);
		if (a >= 0) {
			a += 1;
			int b = sent_data.Find("\n", a);
			String code;
			if (b >= 0)
				code = sent_data.Mid(a, b-a);
			//LOG(code);
			
			Node& n = root->Add(NODE_SENTENCE);
			
			try {
				p.Set(code);
				Parse(n);
				int counter = 0;
				ReadLemma(*root, n, counter);
				RemoveRecursiveDuplicates(n);
				//LOG(NodeTreeString(n));
			}
			catch (Exc e) {
				LOG("error: " << e);
			}
		}
		
		sent = next_sent;
	}
	
	return txt.GetCount();
}

void AceParser::Parse(Node& n) {
	
	if (p.Char('(')) {
		Node& n0 = n.Add(NODE_NL);
		String type = p.ReadString();
		n0.SetText(type.ToWString());
		
		while (p.IsChar('('))
			Parse(n0);
		
		if (n0.GetCount() == 0)
			n0.SetType(NODE_TEXT);
		
		p.PassChar(')');
	}
	
}

void AceParser::ReadLemma(Node& par, Node& n, int& counter) {
	
	if (n.IsType(NODE_TEXT)) {
		Node& l = par.Add(NODE_LEMMA);
		if (counter < lemmas.GetCount())
			l.SetText(lemmas[counter].ToWString());
		counter++;
	}
	else {
		for(int i = 0; i < n.GetCount(); i++) {
			ReadLemma(n, n.At(i), counter);
		}
	}
}



NAMESPACE_LANGUAGE_END

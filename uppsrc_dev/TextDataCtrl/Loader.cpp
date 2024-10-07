#include "TextDataCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


TextDataLoader::TextDataLoader() {
	CtrlLayout(*this);
	Title("SongData loader");
	
	PostCallback(THISBACK(Start));
}

TextDatabase& TextDataLoader::GetDatabase() {
	return MetaDatabase::Single().db;
}

void TextDataLoader::Process() {
	TextDatabase& db = GetDatabase();
	String share = MetaDatabase::Single().share;
	
	if (share == "share") {
		LoadLibtopside();
	}
	else if (share == "share-fi") {
		TODO
	}
	
	//db.src_data.Store();
	PostCallback(THISBACK(Stop));
}

void TextDataLoader::LoadLibtopside() {
	
}

#if 0
void TextDataLoader::LoadHuggingArtists() {
	String dir;
	#ifdef flagWIN32
	dir = AppendFileName(GetHomeDirectory(), "SongData\\huggingartists");
	#elif defined flagPOSIX
	dir = GetHomeDirFile("SongData/huggingartists");
	#endif
	if (!DirectoryExists(dir)) {
		PromptOK("Directory doesn't exist: " + dir);
		return;
	}
	
	TextDatabase& db = GetDatabase();
	db.src_data.entities.Clear();
	
	PostMessage("Searching for huggingartists dataset json files");
	PostProgress(0,1);
	
	Vector<String> files;
	FindFile ff(AppendFileName(dir, "*.json"));
	do {
		if (!ff.IsFile()) continue;
		String path = ff.GetPath();
		
		String title = ToLower(GetFileTitle(path));
		title.Replace("-", " ");
		if (title == "25 17" ||
			title == "5nizza" ||
			title == "5opka" ||
			title == "6ix9ine" ||
			title == "agata christie" ||
			title == "aikko" ||
			title == "aimer" ||
			title == "arash" ||
			title == "ariya" ||
			title == "asper x" ||
			title == "baklan" ||
			title == "big baby tape" ||
			title == "big russian boss" ||
			title == "booker" ||
			title == "boris grebenshikov" ||
			title == "bushido zho" ||
			title == "denderty" ||
			title == "dj artem artemov" ||
			title == "dzhizus" ||
			title == "egor kreed" ||
			title == "egor letov" ||
			title == "face" ||
			title == "galenskaparna and after shave" ||
			title == "ghostemane" ||
			title == "ghostmane" ||
			title == "grigory leps" ||
			title == "gpsd" ||
			title == "hillsong worship" ||
			title == "hyuna" ||
			title == "idktime" ||
			title == "jah khalib" ||
			title == "kasta" ||
			title == "kipelov" ||
			title == "kishlak" ||
			title == "kizaru" ||
			title == "krechet" ||
			title == "little big" ||
			title == "lizer" ||
			title == "lovv66" ||
			title == "lumen" ||
			title == "lyapis trubetskoy" ||
			title == "macan" ||
			title == "mashina vremeni" ||
			title == "max korzh" ||
			title == "mayot" ||
			title == "mikhail gorshenev" ||
			title == "mikhail krug" ||
			title == "miyagi" ||
			title == "mnogoznaal" ||
			title == "morgenshtern" ||
			title == "mumiy troll" ||
			title == "nautilus pompilius" ||
			title == "nervy" ||
			title == "noize mc" ||
			title == "obladaet" ||
			title == "og buda" ||
			title == "olga buzova" ||
			title == "ot rus" ||
			title == "oxxxymiron" ||
			title == "pharaoh" ||
			title == "platina" ||
			title == "pyrokinesis" ||
			title == "ramil" ||
			title == "rammstein" ||
			title == "rocket" ||
			title == "sam kim" ||
			title == "scriptonite" ||
			title == "sektor gaza" ||
			title == "sergei letov" ||
			title == "shadowraze" ||
			title == "sid sriram" ||
			title == "slava kpss" ||
			title == "slava marlow" ||
			title == "sqwore" ||
			title == "t fest" ||
			title == "tanzy minus" ||
			title == "the king and the jester" ||
			title == "the the pigs" ||
			title == "till lindemann" ||
			title == "tony raut and garry topor" ||
			title == "totpoc" ||
			title == "v x v prince" ||
			title == "viktor tsoi" ||
			title == "vladimir vysotsky" ||
			title == "zemfira")
			continue;
		
		files << path;
	}
	while (ff.Next());
	
	for(int i = 0; i < files.GetCount(); i++) {
		String path = files[i];
		String title = GetFileTitle(path);
		
		EntityDataset& artist = db.src_data.entities.Add();
		artist.name = Capitalize(title);
		if (GetDefaultCharset() != CHARSET_UTF8)
			artist.name = ToCharset(CHARSET_UTF8, artist.name, CHARSET_DEFAULT);
		
		Vector<String> name_parts = Split(artist.name, "-");
		for (String& n : name_parts)
			n = Capitalize(ToLower(n));
		artist.name = Join(name_parts, " ");
		
		PostMessage("Loading artist: " + artist.name);
		PostProgress(i, files.GetCount());
		
		String s = LoadFile(path);
		ValueArray js = ParseJSON(s)[0];
		//DUMPC(js);
		
		for(int i = 0; i < js.GetCount(); i++) {
			ScriptDataset& l = artist.scripts.Add();
			l.name = IntStr(i);
			l.text = js[i];
			l.text.Replace("\r", "");
		}
	}
}

void TextDataLoader::LoadHuggingFinn() {
	String dir;
	#ifdef flagWIN32
	dir = AppendFileName(GetHomeDirectory(), "SongData\\huggingfinn");
	#elif defined flagPOSIX
	dir = GetHomeDirFile("SongData/huggingfinn");
	#endif
	if (!DirectoryExists(dir)) {
		PromptOK("Directory doesn't exist: " + dir);
		return;
	}
	
	TextDatabase& db = GetDatabase();
	db.src_data.entities.Clear();
	
	PostMessage("Searching for huggingfinn dataset json files");
	PostProgress(0,1);
	
	VectorMap<String,Vector<String>> files;
	int total_files = 0;
	FindFile ff(AppendFileName(dir, "*"));
	do {
		if (!ff.IsDirectory() || ff.GetName().Left(1) == ".") continue;
		String path = ff.GetPath();
		
		auto& afiles = files.Add(Capitalize(ff.GetName()));
		
		FindFile fl(AppendFileName(path, "*.txt"));
		do {
			afiles << fl.GetPath();
			total_files++;
		}
		while (fl.Next());
	}
	while (ff.Next());
	
	int actual = 0;
	for(int i = 0; i < files.GetCount(); i++) {
		EntityDataset& artist = db.src_data.entities.Add();
		artist.name = files.GetKey(i);
		if (GetDefaultCharset() != CHARSET_UTF8)
			artist.name = ToCharset(CHARSET_UTF8, artist.name, CHARSET_DEFAULT);
		const auto& v = files[i];
		
		PostMessage("Loading artist: " + artist.name);
		
		for(int j = 0; j < v.GetCount(); j++) {
			PostMessage("Loading: " + artist.name + " - " + GetFileTitle(v[j]));
			PostProgress(actual++, total_files);
			
			ScriptDataset& l = artist.scripts.Add();
			l.name = GetFileTitle(v[j]);
			if (GetDefaultCharset() != CHARSET_UTF8)
				l.name = ToCharset(CHARSET_UTF8, l.name, CHARSET_DEFAULT);
			l.text = LoadFile(v[j]);
			l.text.Replace("\r", "");
		}
	}
}

void TextDataLoader::LoadHuggingTweets() {
	String dir;
	#ifdef flagWIN32
	dir = AppendFileName(GetHomeDirectory(), "SongTool\\dataset\\twitter");
	#elif defined flagPOSIX
	dir = GetHomeDirFile("SongTool/dataset/twitter");
	#endif
	if (!DirectoryExists(dir)) {
		PromptOK("Directory doesn't exist: " + dir);
		return;
	}
	
	TextDatabase& db = GetDatabase();
	db.src_data.entities.Clear();
	
	PostMessage("Searching for twitter dataset txt files");
	PostProgress(0,1);
	
	VectorMap<String,String> data;
	
	FindFile ff(AppendFileName(dir, "*.txt"));
	do {
		if (!ff.IsFile()) continue;
		String path = ff.GetPath();
		
		String title = ToLower(GetFileTitle(path));
		
		Vector<String> parts = Split(title, "_");
		if (parts.GetCount() != 2)
			continue;
		
		String name = parts[0];
		int name_part = ScanInt(parts[1]);
		
		String content = LoadFile(path);
		data.GetAdd(name) << "\n" << content;
		
	}
	while (ff.Next());
	
	int story_count = 0;
	for(int i = 0; i < data.GetCount(); i++) {
		String title = data.GetKey(i);
		String content = data[i];
		
		EntityDataset& company = db.src_data.entities.Add();
		company.name = Capitalize(title);
		if (GetDefaultCharset() != CHARSET_UTF8)
			company.name = ToCharset(CHARSET_UTF8, company.name, CHARSET_DEFAULT);
		
		Vector<String> name_parts = Split(company.name, "-");
		for (String& n : name_parts)
			n = Capitalize(ToLower(n));
		company.name = Join(name_parts, " ");
		
		PostMessage("Loading company: " + company.name);
		PostProgress(i, data.GetCount());
		
		content.Replace("\r", "");
		Vector<String> lines = Split(content, "\n");
		
		for(int i = 0; i < lines.GetCount();) {
			ScriptDataset& l = company.scripts.Add();
			l.name = IntStr(i);
			
			for(int j = 0; j < 50 && i < lines.GetCount(); j++, i++) {
				l.text << lines[i] << "\n";
			}
			l.text.Replace("\r", "");
			story_count++;
		}
	}
	LOG("Total story count: " << story_count);
}

void TextDataLoader::LoadHuggingBlogs() {
	String dir;
	#ifdef flagWIN32
	dir = AppendFileName(GetHomeDirectory(), "datasets\\blogs");
	#elif defined flagPOSIX
	dir = GetHomeDirFile("datasets/blogs");
	#endif
	if (!DirectoryExists(dir)) {
		PromptOK("1/2: Directory doesn't exist: " + dir);
		PromptOK(DeQtf("2/2: Download: https://huggingface.co/datasets/blog_authorship_corpus/resolve/main/data/blogs.zip?download=true"));
		return;
	}
	
	TextDatabase& db = GetDatabase();
	db.src_data.entities.Clear();
	
	PostMessage("Searching for blog dataset xml files");
	PostProgress(0,1);
	
	
	int total_size = 0;
	
	Vector<String> files;
	FindFile ff(AppendFileName(dir, "*.xml"));
	do {
		if (!ff.IsFile()) continue;
		files << ff.GetPath();
	}
	while (ff.Next());
	
	Sort(files, StdLess<String>());
	
	int i = 0;
	int story_count = 0;
	for (String& path : files) {
		String title = ToLower(GetFileTitle(path));
		Vector<String> parts = Split(title, ".");
		if (parts.GetCount() != 5)
			continue;
		String content = LoadFile(path);
		content.Replace("\r", "");
		
		
		// Get blogger's name
		String blogger_name = ToLower(title);
		if (GetDefaultCharset() != CHARSET_UTF8)
			blogger_name = ToCharset(CHARSET_UTF8, blogger_name, CHARSET_DEFAULT);
		
		Vector<String> name_parts = Split(blogger_name, "-");
		for (String& n : name_parts)
			n = Capitalize(ToLower(n));
		blogger_name = Join(name_parts, " ");
		
		// Update progress
		PostMessage("Loading blogger: " + blogger_name);
		PostProgress(i++, files.GetCount());
		
		
		VectorMap<String, String> entries;
		try {
			XmlNode xn = ParseXML(content);
			const XmlNode& blog = xn[0];
			
			String total_content;
			
			for(int i = 1; i < blog.GetCount(); i+=2) {
				const XmlNode& date = blog[i-1];
				const XmlNode& post = blog[i];
				ASSERT(date.GetTag() == "date");
				ASSERT(post.GetTag() == "post");
				
				for(int j = 0; j < post.GetCount(); j++) {
					String txt = TrimBoth(post[j].GetText());
					
					// Hotfix blog texts
					txt.Replace(".  ", ".\n");
					txt.Replace("   ", " ");
					txt.Replace("\n   ", "\n");
					txt.Replace("\n  ", "\n");
					txt.Replace("\n ", "\n");
					txt.Replace(". The ", ".\nThe ");
					txt.Replace(". This ", ".\nThis ");
					txt.Replace(". I ", ".\nI ");
					txt.Replace(". You ", ".\nYou ");
					txt.Replace(". Oh ", ".\nOh ");
					txt.Replace("...", "...\n");
					txt.Replace("\n....", "\n");
					txt.Replace("\n...", "\n");
					txt.Replace("\n..", "\n");
					txt.Replace("\n.", "\n");
					
					// Trim lines
					Vector<String> lines = Split(txt, "\n");
					for (String& l : lines) l = TrimBoth(l);
					txt = Join(lines, "\n");
					
					
					txt.Replace("\nurlLink", "\nurlLink\n");
					txt.Replace("\nurlLink", "\nurlLink\n");
					txt.Replace("\nurlLink", "\nurlLink\n");
					txt.Replace("urlLink", "(urlLink)");
					
					HotfixReplaceWord(txt);
					
					txt.Replace("Mrs.", "Mrs");
					txt.Replace("Mr.", "Mr");
					txt.Replace("Ms.", "Ms");
					txt.Replace("mrs.", "mrs");
					txt.Replace("mr.", "mr");
					txt.Replace("ms.", "ms");
					txt.Replace("etc.", "etc");
					
					txt.Replace(",\"", "\"\n");
					txt.Replace("...\"", "\"\n");
					txt.Replace(".\"", "\"\n");
					txt.Replace(".\'", "\'\n");
					txt.Replace(".)", ")\n");
					txt.Replace("(", "\n");
					txt.Replace(")", "\n");
					
					for(int i = 1; i <= 20; i++) {
						String s = IntStr(i) + ".";
						txt.Replace(s, "\n" + IntStr(i) + s);
					}
					
					// Split txt to parts
					txt.Replace("...", "\n");
					txt.Replace(".", "\n");
					//txt.Replace(",", "\n");
					txt.Replace("!", "\n");
					txt.Replace("?", "\n");
					txt.Replace(":", "\n");
					txt.Replace(".\n", "\n");
					
					txt.Replace("\n\" ", "\n\"");
					txt.Replace("\n\"\n", "\"\n");
					
					for(int i = 0; i < 3; i++)
						txt.Replace("\n\n", "\n");
					
					
					// Trim lines
					lines = Split(txt, "\n");
					for (String& l : lines) l = TrimBoth(l);
					txt = Join(lines, "\n");
					if (txt.GetCount() && txt.Right(1) == ".")
						txt = txt.Left(txt.GetCount()-1);
					
					
					entries.Add(date[0].GetText(), txt);
				}
			}
			
			if (total_size >= size_limit)
				break;
		}
		catch (XmlError e) {
			LOG("XmlError: " << title << ": " << e);
		}
		
		if (entries.GetCount()) {
			EntityDataset& blogger = db.src_data.entities.Add();
			blogger.name = blogger_name;
			
			for(int i = 0; i < entries.GetCount(); i++) {
				
				ScriptDataset& l = blogger.scripts.Add();
				l.name = entries.GetKey(i);
				l.text = entries[i];
				story_count++;
				
				total_size += l.text.GetCount();
			}
		}
	}
	LOG("Total blogger count: " << db.src_data.entities.GetCount());
	LOG("Total story count: " << story_count);
	LOG("Total byte size of stories: " << total_size/1000 << "Kb");
}

void TextDataLoader::LoadHuggingDialogue() {
	String dir;
	#ifdef flagWIN32
	dir = AppendFileName(GetHomeDirectory(), "datasets\\dialog");
	#elif defined flagPOSIX
	dir = GetHomeDirFile("datasets/dialog");
	#endif
	if (!DirectoryExists(dir)) {
		PromptOK("1/2: Directory doesn't exist: " + dir);
		PromptOK(DeQtf("2/2: Download files and extract to ~/datasets/dialog: https://huggingface.co/datasets/RUCAIBox/Open-Dialogue"));
		return;
	}
	
	Vector<String> training_files;
	training_files << "ed";
	training_files << "pc";
	training_files << "dd";
	training_files << "dream";
	
	TextDatabase& db = GetDatabase();
	db.src_data.entities.Clear();
	
	PostMessage("Searching for dialog dataset tgt files");
	PostProgress(0,1);
	
	
	int total_size = 0;
	
	Vector<String> files;
	for (String& f : training_files) {
		String path = AppendFileName(AppendFileName(dir, f), "train.tgt");
		if (FileExists(path))
			files << path;
		
		#if 0
		// These files have too much discontinuation between lines
		path = AppendFileName(AppendFileName(dir, f), "test.tgt");
		if (FileExists(path))
			files << path;
		path = AppendFileName(AppendFileName(dir, f), "valid.tgt");
		if (FileExists(path))
			files << path;
		#endif
	}
	if (files.IsEmpty()) return;
	
	Sort(files, StdLess<String>());
	
	int per_file_limit = size_limit / files.GetCount();
	
	int i = 0;
	int line_count = 0;
	for (String& path : files) {
		String file_title = ToLower(GetFileTitle(path));
		String dir = GetFileDirectory(path);
		dir = dir.Left(dir.GetCount()-1);
		String dir_title = ToLower(GetFileTitle(dir));
		String title = dir_title + " - " + file_title;
		
		String content = LoadFile(path);
		content.Replace("\r", "");
		
		
		// Update progress
		PostMessage("Loading dialog: " + title);
		PostProgress(i++, files.GetCount());
		
		
		EntityDataset& d = db.src_data.entities.Add();
		d.name = title;
			
		Vector<String> lines = Split(content, "\n");
		
		int per_entry = 50;
		int idx = 0;
		int entity_size = 0;
		for(int i = 0; i < lines.GetCount(); i+=per_entry) {
			int end = min(i + per_entry, lines.GetCount());
			String txt;
			for(int j = i, l = 0; j < end; j++, l++) {
				if (l) txt.Cat('\n');
				txt += TrimBoth(lines[j]);
			}
			// Hotfix blog texts
			txt.Replace("\"", "");
			txt.Replace("\'", "");
			txt.Replace("   ", " ");
			txt.Replace("\n   ", "\n");
			txt.Replace("\n  ", "\n");
			txt.Replace("\n ", "\n");
			txt.Replace(". The ", ".\nThe ");
			txt.Replace(". This ", ".\nThis ");
			txt.Replace(". I ", ".\nI ");
			txt.Replace(". You ", ".\nYou ");
			txt.Replace(". Oh ", ".\nOh ");
			txt.Replace("...", "...\n");
			txt.Replace("\n....", "\n");
			txt.Replace("\n...", "\n");
			txt.Replace("\n..", "\n");
			txt.Replace("\n.", "\n");
			
			txt.Replace("Mrs.", "Mrs");
			txt.Replace("Mr.", "Mr");
			txt.Replace("Ms.", "Ms");
			txt.Replace("mrs.", "mrs");
			txt.Replace("mr.", "mr");
			txt.Replace("ms.", "ms");
			txt.Replace("etc.", "etc");
			
			txt.Replace(".)", ")\n");
			txt.Replace("(", "\n");
			txt.Replace(")", "\n");
			
			HotfixReplaceWord(txt);
			
			// Trim lines
			Vector<String> lines = Split(txt, "\n");
			for (String& l : lines) l = TrimBoth(l);
			txt = Join(lines, "\n");
			
			for(int i = 1; i <= 20; i++) {
				String s = IntStr(i) + ".";
				txt.Replace(s, "\n" + IntStr(i) + s);
			}
			
			// Split txt to parts
			txt.Replace("...", "\n");
			txt.Replace(".", "\n");
			//txt.Replace(",", "\n");
			txt.Replace("!", "\n");
			txt.Replace("?", "\n");
			txt.Replace(":", "\n");
			txt.Replace(".\n", "\n");
			
			txt.Replace("\n\" ", "\n\"");
			txt.Replace("\n\"\n", "\"\n");
			
			for(int i = 0; i < 3; i++)
				txt.Replace("\n\n", "\n");
			
			
			// Trim lines
			lines = Split(txt, "\n");
			for(int i = 0; i < lines.GetCount(); i++) {
				String& l = lines[i];
				l = TrimBoth(l);
				if (l.IsEmpty())
					lines.Remove(i--);
			}
			txt = Join(lines, "\n");
			
			if (txt.GetCount() && txt.Right(1) == ".")
				txt = txt.Left(txt.GetCount()-1);
			
			ScriptDataset& l = d.scripts.Add();
			l.name = "#" + IntStr(idx++);
			l.text = txt;
			
			line_count += lines.GetCount();
			total_size += l.text.GetCount();
			entity_size += l.text.GetCount();
			
			if (entity_size >= per_file_limit)
				break;
		}
		
		if (total_size >= size_limit)
			break;
	}
	LOG("Total dialogue file count: " << db.src_data.entities.GetCount());
	LOG("Total line count: " << line_count);
	LOG("Total byte size of dialogues: " << total_size/1000 << "Kb");
}

void TextDataLoader::LoadHuggingStoryboard() {
	String dir;
	#ifdef flagWIN32
	dir = AppendFileName(GetHomeDirectory(), "datasets\\captions");
	#elif defined flagPOSIX
	dir = GetHomeDirFile("datasets/captions");
	#endif
	if (!DirectoryExists(dir)) {
		PromptOK("1/2: Directory doesn't exist: " + dir);
		PromptOK(DeQtf("2/2: Download files and extract to ~/datasets/captions: https://antoyang.github.io/vidchapters.html"));
		// https://huggingface.co/datasets/open_subtitles/tree/refs%2Fconvert%2Fparquet/en-hi/train
		// https://cs.stanford.edu/people/ranjaykrishna/densevid/captions.zip
		// https://antoyang.github.io/vidchapters.html
		return;
	}
	
	
	String file = AppendFileName(dir, "train.json");
	if (!FileExists(file))
		return;
	
	TextDatabase& db = GetDatabase();
	db.src_data.entities.Clear();
	
	PostMessage("Searching for dialog dataset tgt files");
	PostProgress(0,1);
	
	
	int total_size = 0;
	
	String content = LoadFile(file);
	ValueMap js = ParseJSON(content);
	
	int line_count = 0;
	for(int i = 0; i < js.GetCount(); i++) {
		String title = js.GetKey(i);
		ValueMap sb = js.At(i);
		ValueArray sentences = sb.GetAdd("sentences");
		//DUMPM(sb);
		
		
		// Update progress
		PostMessage("Loading dialog: " + title);
		PostProgress(i++, js.GetCount());
		
		
		EntityDataset& d = db.src_data.entities.Add();
		d.name = title;
		
		
		String txt;
		int entity_size = 0;
		for(int i = 0; i < sentences.GetCount(); i++) {
			if (!txt.IsEmpty()) txt.Cat('\n');
			txt += (String)sentences[i];
		}
		// Hotfix blog texts
		/*txt.Replace("\"", "");
		txt.Replace("\'", "");
		txt.Replace("   ", " ");
		txt.Replace("\n   ", "\n");
		txt.Replace("\n  ", "\n");
		txt.Replace("\n ", "\n");
		txt.Replace(". The ", ".\nThe ");
		txt.Replace(". This ", ".\nThis ");
		txt.Replace(". I ", ".\nI ");
		txt.Replace(". You ", ".\nYou ");
		txt.Replace(". Oh ", ".\nOh ");
		txt.Replace("...", "...\n");
		txt.Replace("\n....", "\n");
		txt.Replace("\n...", "\n");
		txt.Replace("\n..", "\n");
		txt.Replace("\n.", "\n");
		
		txt.Replace("Mrs.", "Mrs");
		txt.Replace("Mr.", "Mr");
		txt.Replace("Ms.", "Ms");
		txt.Replace("mrs.", "mrs");
		txt.Replace("mr.", "mr");
		txt.Replace("ms.", "ms");
		txt.Replace("etc.", "etc");
		
		txt.Replace(".)", ")\n");
		txt.Replace("(", "\n");
		txt.Replace(")", "\n");*/
		
		HotfixReplaceWord(txt);
		
		// Trim lines
		Vector<String> lines = Split(txt, "\n");
		for (String& l : lines) l = TrimBoth(l);
		txt = Join(lines, "\n");
		
		for(int i = 1; i <= 20; i++) {
			String s = IntStr(i) + ".";
			txt.Replace(s, "\n" + IntStr(i) + s);
		}
		
		// Split txt to parts
		/*txt.Replace("...", "\n");
		txt.Replace(".", "\n");
		txt.Replace(",", "\n");
		txt.Replace("!", "\n");
		txt.Replace("?", "\n");
		txt.Replace(":", "\n");*/
		
		txt.Replace(".\n", "\n");
		txt.Replace("\n\" ", "\n\"");
		txt.Replace("\n\"\n", "\"\n");
		
		for(int i = 0; i < 3; i++)
			txt.Replace("\n\n", "\n");
		
		
		// Trim lines
		lines = Split(txt, "\n");
		for(int i = 0; i < lines.GetCount(); i++) {
			String& l = lines[i];
			l = TrimBoth(l);
			if (l.IsEmpty())
				lines.Remove(i--);
		}
		txt = Join(lines, "\n");
		
		if (txt.GetCount() && txt.Right(1) == ".")
			txt = txt.Left(txt.GetCount()-1);
		
		ScriptDataset& l = d.scripts.Add();
		l.name = "#" + IntStr(i);
		l.text = txt;
		
		line_count += lines.GetCount();
		total_size += l.text.GetCount();
		entity_size += l.text.GetCount();
		
		if (total_size >= size_limit)
			break;
	}
	LOG("Total dialogue file count: " << db.src_data.entities.GetCount());
	LOG("Total line count: " << line_count);
	LOG("Total byte size of dialogues: " << total_size/1000 << "Kb");
}

void TextDataLoader::LoadHuggingMarketing() {
	
	String dir;
	#ifdef flagWIN32
	dir = AppendFileName(GetHomeDirectory(), "datasets\\marketing");
	#elif defined flagPOSIX
	dir = GetHomeDirFile("datasets/marketing");
	#endif
	if (!DirectoryExists(dir)) {
		PromptOK("1/2: Directory doesn't exist: " + dir);
		PromptOK(DeQtf("2/2: Download train.jsonl and extract to ~/datasets/marketing: https://huggingface.co/datasets/SetFit/enron_spam"));
		return;
	}
	
	
	String file = AppendFileName(dir, "train.jsonl");
	if (!FileExists(file))
		return;
	
	TextDatabase& db = GetDatabase();
	db.src_data.entities.Clear();
	
	PostMessage("Searching for dialog dataset tgt files");
	PostProgress(0,1);
	
	
	int total_size = 0;
	int line_count = 0;
	EntityDataset& d = db.src_data.entities.Add();
	d.name = "Enron spam dataset";
	
	String content = LoadFile(file);
	int b = -1, i = 0;
	while (b < content.GetCount()) {
		// Locate row
		int a = b+1;
		b = content.Find("\n", a);
		if (b < 0)
			b = content.GetCount();
		String json = content.Mid(a,b-a);
		
		ValueMap js = ParseJSON(json);
		
		
		{
			String txt = js.GetAdd("text");
			
			if (txt.Find("<td>") >= 0 || txt.Find("<tr>") >= 0)
				continue;
			if (txt.Find(" es ") >= 0)
				continue;
			if (txt.Find("\n>") >= 0)
				continue;
			if (txt.Find(" child ") >= 0)
				continue;
			
			// Update progress
			if (i % 10 == 0) {
				PostMessage("Loading item: #" + IntStr(i));
				PostProgress(i, js.GetCount());
			}
			i++;
			
			
			HotfixReplaceWord(txt);
			
			// Trim lines
			Vector<String> lines = Split(txt, "\n");
			for (String& l : lines) l = TrimBoth(l);
			txt = Join(lines, "\n");
			
			for(int i = 1; i <= 20; i++) {
				String s = IntStr(i) + ".";
				txt.Replace(s, "\n" + IntStr(i) + s);
			}
			
			txt.Replace(".\n", "\n");
			txt.Replace("\n\" ", "\n\"");
			txt.Replace("\n\"\n", "\"\n");
			
			for(int i = 0; i < 3; i++)
				txt.Replace("\n\n", "\n");
			
			
			// Trim lines
			lines = Split(txt, "\n");
			for(int i = 0; i < lines.GetCount(); i++) {
				String& l = lines[i];
				l = TrimBoth(l);
				if (l.IsEmpty())
					lines.Remove(i--);
			}
			txt = Join(lines, "\n");
			
			if (txt.GetCount() && txt.Right(1) == ".")
				txt = txt.Left(txt.GetCount()-1);
			
			ScriptDataset& l = d.scripts.Add();
			l.name = "#" + IntStr(i);
			l.text = txt;
			
			line_count += lines.GetCount();
			total_size += l.text.GetCount();
			
			if (total_size >= size_limit)
				break;
		}
	}
	LOG("Total marketing file count: " << db.src_data.entities.GetCount());
	LOG("Total line count: " << line_count);
	LOG("Total byte size of marketing: " << total_size/1000 << "Kb");
}
#endif

END_TEXTLIB_NAMESPACE


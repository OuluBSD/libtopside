#include "ShaderDownloader.h"

#define COUT(x) {Cout() << x << "\n"; LOG(x);}

String SimplifyName(String s) {
	s.Replace("- ", "");
	String o;
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		if (IsAlpha(chr))
			o.Cat(ToLower(chr));
		else if (IsDigit(chr) || chr == '-' || chr == '_')
			o.Cat(chr);
		else if (IsSpace(chr))
			o.Cat('_');
	}
	return o;
}

void PrepareRequest(HttpRequest& h) {
	//HttpRequest::Trace(true);
	h.Url("https://www.shadertoy.com/shadertoy");
	h.POST();
	h.Header("Referer", "https://www.shadertoy.com/");
	h.UserAgent("Mozilla/5.0 (X11; Linux x86_64; rv:85.0) Gecko/20100101 Firefox/85.0");
}

bool IsAlphaNum(String s) {
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		if (!IsAlpha(chr) && !IsDigit(chr))
			return false;
	}
	return true;
}

CONSOLE_APP_MAIN
{
	bool verbose = false;
	
	const Vector<String>& cmdline = CommandLine();
	String dir;
	if (cmdline.GetCount() != 1) {
		COUT("Expecting asset directory as argument");
		return;
	}
	dir = cmdline[0];
	
	String cat_path = AppendFileName(dir, "categories.txt");
	String list_path = AppendFileName(dir, "list.txt");
	String singlepass_path = AppendFileName(dir, "single_pass.txt");
	String multipass_path = AppendFileName(dir, "multi_pass.txt");
	String skip_path = AppendFileName(dir, "skip.txt");
	String search_dir = AppendFileName(dir, "search_results");
	String json_dir = AppendFileName(dir, "jsons");
	String common_dir = AppendFileName(dir, "common");
	RealizeDirectory(search_dir);
	RealizeDirectory(json_dir);
	RealizeDirectory(common_dir);
	
	Index<String> skip_list;
	if (FileExists(skip_path)) {
		Vector<String> v = Split(LoadFile(skip_path), "\n");
		for(String s : v)
			skip_list.FindAdd(s);
	}
	
	if (!FileExists(cat_path)) {
		COUT("File doesn't exist: " << cat_path);
		return;
	}
	
	Vector<String> cats = Split(LoadFile(cat_path), "\n");
	for(int i = 0; i < cats.GetCount(); i++) {
		String& c = cats[i];
		if (c.GetCount() <= 1)
			cats.Remove(i--);
	}
	Sort(cats, StdLess<String>());
	//DUMPC(cats);
	
	#define PER_PAGE 12
	#define MAX_PAGES 5
	
	
	for(String cat : cats) {
		String out_file = AppendFileName(search_dir, SimplifyName(cat));
		if (IsAlphaNum(cat))
			cat = "tag=" + cat;
		int count = 1;
		int cur_page = 0;
		bool write_count = true;
		if (FileExists(out_file)) {
			Vector<String> v = Split(LoadFile(out_file), "\n");
			if (v.GetCount()) {
				count = StrInt(v[0]);
				int already = v.GetCount() - 1;
				cur_page = already / PER_PAGE + (already % PER_PAGE ? 1 : 0);
				write_count = false;
			}
		}
		if (!count)
			continue;
		FileAppend append(out_file);
		if (!append.IsOpen()) {
			COUT("Couldn't open file for writing: " << out_file);
			return;
		}
		int pages = std::min<int>(MAX_PAGES, count / PER_PAGE + (count % PER_PAGE ? 1 : 0));
		for(;cur_page < pages; cur_page++) {
			int begin = cur_page * PER_PAGE;
			String url = "https://www.shadertoy.com/results?query=" + UrlEncode(cat) +
				"&sort=popular&from=" + IntStr(begin) + "&num=" + IntStr(PER_PAGE);
			//LOG(url);
			COUT("Category '" << cat << "', page " << cur_page);
			
			HttpRequest h;
			PrepareRequest(h);
			h.GET();
			h.Url(url);
			String content = h.Execute();
			if (content.IsEmpty()) {
				COUT("Didn't receive anything from " << url);
				return;
			}
			
			if (write_count) {
				int res_a = content.Find("Results (");
				if (res_a < 0) {COUT("Couldn't find 'Results ('"); return;}
				res_a += 9;
				int res_b = content.Find(")", res_a);
				if (res_b < 0) {COUT("Couldn't find ')'"); return;}
				String res_str = content.Mid(res_a, res_b - res_a);
				COUT(res_str << " results for category " << cat);
				append << res_str << "\n";
				append.Flush();
				count = StrInt(res_str);
				pages = std::min<int>(MAX_PAGES, count / PER_PAGE + (count % PER_PAGE ? 1 : 0));
				COUT(pages << " pages");
				write_count = false;
				if (!count)
					break;
			}
			
			int shader_a = content.Find("var gShaderIDs=[");
			if (shader_a < 0) {
				COUT("Couldn't find 'var gShaderIDs=['");
				return;
			}
			shader_a += 16;
			int shader_b = content.Find("]", shader_a);
			if (shader_b < 0) {COUT("Couldn't find ']'"); return;}
			
			String list_str = content.Mid(shader_a, shader_b - shader_a);
			Vector<String> list = Split(list_str, ",");
			if (list.IsEmpty()) {COUT("Got empty list"); return;}
			for(String& i : list) {
				i = TrimBoth(i);
				if (i.Left(1) == "\"")
					i = i.Mid(1, i.GetCount()-2);
			}
			
			for(String& i : list) {
				append << i << "\n";
				COUT("\t" << i);
			}
			append.Flush();
			
			Sleep(3000);
		}
		
		append.Close();
	}
	
	VectorMap<String, String> url_cats, dl_cats;
	for(String cat : cats) {
		String simple_cat = SimplifyName(cat);
		String out_file = AppendFileName(search_dir, simple_cat);
		if (FileExists(out_file)) {
			Vector<String> lines = Split(LoadFile(out_file), "\n");
			for(int i = 1; i < lines.GetCount(); i++) {
				String id = lines[i];
				if (skip_list.Find(id) >= 0)
					continue;
				String url = "https://www.shadertoy.com/view/" + id;
				url_cats.GetAdd(url, simple_cat);
			}
		}
	}
	
	
	if (!FileExists(list_path)) {
		COUT("File doesn't exist: " << list_path);
	}
	else {
		Vector<String> single_urls = Split(LoadFile(list_path), "\n");
	
		String cur_cat;
		for(String url : single_urls) {
			if (url.Find("https://www.shadertoy.com/results?") == 0)
				continue;
			
			if (url.Find("https://www.shadertoy.com/") != 0) {
				if (url.Find("http") == 0)
					continue;
				if (verbose) COUT(url);
				cur_cat = SimplifyName(url);
				continue;
			}
			
			if (url.Find("https://www.shadertoy.com/view/") == 0) {
				String id = GetFileName(url);
				if (skip_list.Find(id) >= 0)
					continue;
				url_cats.GetAdd(url, cur_cat);
			}
		}
	}
	
	
	VectorMap<String, String> json_cats;
	for(int i = 0; i < url_cats.GetCount(); i++) {
		String url = url_cats.GetKey(i);
		String id = GetFileName(url);
		String json_path = AppendFileName(json_dir, id + ".json");
		if (!FileExists(json_path))
			dl_cats.GetAdd(url_cats.GetKey(i), url_cats[i]);
		json_cats.GetAdd(json_path, url_cats[i]);
	}
	SortByValue(json_cats, StdLess<String>());
	
	
	SortByKey(dl_cats, StdLess<String>());
	//DUMPM(dl_cats);
	if (dl_cats.GetCount())
		COUT("Download " << dl_cats.GetCount() << " urls");
	
	One<Vector<String> > cur_batch;
	Array<Vector<String> > batches;
	cur_batch.Create();
	for(int i = 0; i < dl_cats.GetCount(); i++) {
		String url = dl_cats.GetKey(i);
		String id = GetFileName(url);
		
		cur_batch->Add(id);
		if (cur_batch->GetCount() == PER_PAGE) {
			batches.Add(cur_batch.Detach());
			cur_batch.Clear();
			cur_batch.Create();
		}
	}
	if (cur_batch->GetCount())
		batches.Add(cur_batch.Detach());
	
	if (batches.GetCount())
		COUT(batches.GetCount() << " batches");
	
	for(int i = 0; i < batches.GetCount(); i++) {
		const Vector<String>& batch = batches[i];
		ASSERT(batch.GetCount() <= PER_PAGE);
		
		String dbg_str;
		ValueArray va;
		for(String url : batch) {
			String id = GetFileName(url);
			va.Add(id);
			if (dbg_str.IsEmpty())
				dbg_str << id;
			else
				dbg_str << ", " << id;
		}
		ASSERT(va.GetCount() <= PER_PAGE);
		
		COUT("\tDownloading batch " << i << " / " << batches.GetCount() << ": " << dbg_str);
		
		HttpRequest h;
		PrepareRequest(h);
		
		ValueMap vm;
		vm.Add("shaders", va);
		String json = AsJSON(vm);
		//COUT("\t" << json);
		
		String enc = "s=" + UrlEncode(json);
		enc << "&nt=0&nl=0";
		
		if (verbose) COUT("\t" + enc);
		h.PostData(enc);
		
		String content = h.Execute();
		if (verbose) COUT("\tReceived: " << content.GetCount());
		if (content.IsEmpty()) {
			COUT("Got empty content... exiting for safety reasons");
			return;
		}
		
		//COUT(content);
		Value v = ParseJSON(content);
		ValueArray res = v;
		
		if (res.GetCount() == 0) {
			COUT("Got no results");
			return;
		}
		
		if (res.GetCount() > batch.GetCount()) {
			COUT("Very unexpected result size: " << res.GetCount() << " != " << batch.GetCount());
			return;
		}
		if (res.GetCount() < batch.GetCount()) {
			COUT("Unexpected result size (some shaders were removed?): " << res.GetCount() << " != " << batch.GetCount());
		}
		
		for(int i = 0; i < res.GetCount(); i++) {
			String url = batch[i];
			String id = GetFileName(url);
			String json_path = AppendFileName(json_dir, id + ".json");
			
			String content = AsJSON(res[i], true);
			//COUT(content);
			
			FileOut fout(json_path);
			fout << content;
		}
		
		Sleep(5000);
	}
	
	struct Rewrite : Moveable<Rewrite> {
		String rem_path, new_path, content;
	};
	Vector<Rewrite> rw;
	
	COUT("Collecting json files");
	FindFile ff;
	if (ff.Search(AppendFileName(json_dir, "*.json"))) do {
		String fname = ff.GetName();
		String file_id = GetFileTitle(fname);
		if (fname == "." || fname == "..") continue;
		
		//COUT(fname);
		
		bool rewrite = false;
		String content = LoadFile(ff.GetPath());
		if (content.GetCount() < 10) {
			if (skip_list.Find(file_id) < 0) {
				COUT("Too small file: " << fname);
				skip_list.Add(file_id);
			}
			continue;
		}
		Value v = ParseJSON(content);
		
		// remove the [] from jsons and pretty print them
		if (v.Is<ValueArray>()) {
			ValueArray va = v;
			if (va.GetCount() == 1) {
				v = va[0];
				rewrite = true;
				COUT("Fixing file: " << file_id);
			}
			else {
				COUT("Unexpected file: " << fname);
				return;
			}
		}
		
		// fix wrong ids
		ValueMap vm = v;
		ValueMap info = vm.GetAdd("info");
		String id = info.GetAdd("id");
		if (id.IsEmpty()) {
			COUT(AsJSON(v, true));
			COUT("Unexpected file: " << fname);
			return;
		}
		if (file_id != id) {
			COUT("File content differs from path: " << file_id << " != " << id);
			rewrite = true;
		}
		
		if (rewrite) {
			Rewrite& r = rw.Add();
			r.rem_path = ff.GetPath();
			r.new_path = AppendFileName(json_dir, id + ".json");
			r.content = AsJSON(v, true);
		}
	}
	while (ff.Next());
	
	
	{
		FileOut fout(skip_path);
		for(String s: skip_list)
			fout << s << "\n";
		fout.Flush();
	}
	
	COUT("Fixing files");
	for (Rewrite& r : rw) {
		COUT("\tRemoving file " << r.rem_path);
		DeleteFile(r.rem_path);
	}
	
	for (Rewrite& r : rw) {
		COUT("\tWriting file " << r.new_path);
		FileOut fout(r.new_path);
		fout << r.content;
		fout.Flush();
	}
	
	
	Index<String> p1_list, pX_list;
	String src_dir = AppendFileName(dir, "src");
	/*if (DirectoryExists(src_dir)) {
		COUT("Remove 'src' directory first!\nAborting...");
		return;
	}*/
	Index<String> written_relpaths;
	ArrayMap<String, FileOut> required_type_files;
	for(int i = 0; i < json_cats.GetCount(); i++) {
		String json_path = json_cats.GetKey(i);
		String cat = json_cats[i];
		
		if (i % 1000 == 0)
			COUT("Writing file " << i << " / " << json_cats.GetCount());
		
		String file_id = GetFileTitle(json_path);
		if (skip_list.Find(file_id) >= 0)
			continue;
		
		if (!FileExists(json_path)) {
			COUT("File doesn't exist: " << json_path);
			continue;
		}
		String json = LoadFile(json_path);
		
		if (json.GetCount() < 10) continue;
		
		Value v = ParseJSON(json);
		if (verbose) COUT(AsJSON(v, true));
		
		ValueMap vm = v;
		ValueMap info = vm.GetAdd("info");
		String name = info.GetAdd("name");
		String description = info.GetAdd("description");
		String date = info.GetAdd("date");
		String username = info.GetAdd("username");
		int likes = info.GetAdd("likes");
		String simple_name = SimplifyName(name);
		if (simple_name.IsEmpty())
			simple_name = "__emptyname__";
		
		
		description.Replace("\"", " \\\"");
		description.Replace("\n", " \\n");
		description.Replace("\r", "");
		
		
		String relpath = AppendFileName(cat, simple_name);
		
		bool renamed_dir = false;
		while (written_relpaths.Find(relpath) >= 0) {
			simple_name << "_";
			relpath = AppendFileName(cat, simple_name);
			renamed_dir = true;
		}
		written_relpaths.Add(relpath);
		if (renamed_dir)
			COUT("\tHad to rename directory: " << relpath);
		
		String out_dir = AppendFileName(src_dir, relpath);
		
		if (verbose) {
			COUT("\t" << name << " (" << simple_name << ")");
			COUT("\t" << description);
			COUT("\t" << likes);
			COUT("\t" << cat);
			COUT("\t" << out_dir);
		}
		
		RealizeDirectory(out_dir);
		
		FileOut fout(AppendFileName(out_dir, simple_name + ".toy"));
		fout << "{\n";
		fout << "\tname: \"" << name << "\",\n";
		if (description.GetCount())
			fout << "\tdescription: \"" << description << "\",\n";
		fout << "\towner: \"" << username << "\",\n";
		fout << "\tlikes: " << likes << ",\n";
		if (date.GetCount()) {
			Time t = TimeFromUTC(StrInt(date));
			fout << "\tdate: " << Format("%04d%02d%02d", (int)t.year, (int)t.month, (int)t.day) << ",\n";
		}
		fout << "\t\n";
		
		fout << "\tstages: [\n";
		
		Index<String> required_types;
		Index<String> id_idx;
		ValueArray rendpass = vm.GetAdd("renderpass");
		if (rendpass.GetCount() == 1)
			p1_list.Add(cat + "/" + simple_name);
		else
			pX_list.Add(cat + "/" + simple_name);
		for(int i = 0; i < rendpass.GetCount(); i++) {
			ValueMap pass = rendpass[i];
			String out_file = AppendFileName(out_dir, "stage" + IntStr(i) + ".glsl");
			String code = pass.GetAdd("code");
			
			FileOut glsl_out(out_file);
			glsl_out << code;
			
			fout << "\t\t{\n";
			
			{
				//String pre = "pass-" + IntStr(i) + "-";
				String name = pass.GetAdd("name");
				String description = pass.GetAdd("description");
				String type = pass.GetAdd("type");
				//String channel = pass.Find("channel") >= 0 ? IntStr(pass.GetAdd("channel")) : "";
				String lname = ToLower(name);
				
				if (lname == "sound")
					type = "sound";
				else if (lname == "image")
					type = "image";
				else if (type == "image" || type == "buffer")
					type = "imagebuf";
				else if (type == "sound")
					type = "soundbuf";
				else if (type == "common")
					type = "library";
				else if (type == "cubemap")
					;
				else
					type += "buf";
				
				if (name.GetCount() && !(
						(lname == "sound" && type == "sound") ||
						(lname == "image" && type == "image")
					))
					fout << "\t\t\tname: \"" << name << "\",\n";
				if (description.GetCount())
					fout << "\t\t\tdescription: \"" << description << "\",\n";
				if (type.GetCount())
					fout << "\t\t\ttype: " << type << ",\n";
				//if (channel.GetCount())
				//	fout << "\t\t\tchannel: \"" << channel << "\",\n";
				fout << "\t\t\t\n";
				
				required_types.FindAdd(type);
			}
			
			ValueArray inputs = pass.GetAdd("inputs");
			if (inputs.GetCount()) {
				int ch_j[4] = {-1,-1,-1,-1};
				int max_ch = -1;
				for(int j = 0; j < inputs.GetCount(); j++) {
					ValueMap input = inputs[j];
					int ch = input.Find("channel") >= 0 ? (int)input.GetAdd("channel") : -1;
					if (ch >= 0) {
						ASSERT(ch < 4);
						ch_j[ch] = j;
						max_ch = max(max_ch, ch);
					}
				}
				
				fout << "\t\t\tinputs: [\n";
				for(int j = 0; j <= max_ch; j++) {
					int k = ch_j[j];
					if (k < 0) {
						fout << "\t\t\t\t{},\n";
						continue;
					}
					
					ValueMap input = inputs[k];
					
					String id = input.GetAdd("id");
					String type = input.GetAdd("type");
					String filepath = input.GetAdd("filepath");
					//String ch = input.Find("channel") >= 0 ? IntStr(input.GetAdd("channel")) : "";
					int id_i = id_idx.FindAdd(id);
					
					//String pre = "pass-" + IntStr(i) + "-input-" + IntStr(ch) + "-";
					fout << "\t\t\t\t{\n";
					fout << "\t\t\t\t\tid: " << id_i << ",\n";
					fout << "\t\t\t\t\ttype: " << type << ",\n";
					//if (ch.GetCount())
					//	fout << "\t\t\t\t\tchannel: " << ch << ",\n";
						
					k = input.Find("sampler");
					if (k >= 0) {
						ValueMap sampler = input.GetValue(k);
						int filter_i = sampler.Find("filter");
						int wrap_i = sampler.Find("wrap");
						int vflip_i = sampler.Find("vflip");
						//String srgb = sampler.GetAdd("srgb");
						//String internal = sampler.GetAdd("internal");
						if (filter_i >= 0)
							fout << "\t\t\t\t\tfilter: " << sampler.GetValue(filter_i) << ",\n";
						if (wrap_i >= 0)
							fout << "\t\t\t\t\twrap: " << sampler.GetValue(wrap_i) << ",\n";
						if (vflip_i >= 0)
							fout << "\t\t\t\t\tvflip: " << sampler.GetValue(vflip_i) << ",\n";
					}
					
					required_types.FindAdd(type);
					
					if (filepath.Find("/media/a/") == 0 && filepath.Find("media/previz/") == -1) {
						String filename = GetFileName(filepath);
						String dest = AppendFileName(common_dir, filename);
						fout << "\t\t\t\t\tfilename: \"" << filename << "\",\n";
						
						if (!FileExists(dest)) {
							String url = "https://www.shadertoy.com" + filepath;
							COUT("\t\tDownloading: " << url);
							HttpRequest h;
							PrepareRequest(h);
							h.Url(url);
							String content = h.Execute();
							if (content.IsEmpty()) {
								COUT("Error: couldn't download " << url);
								return;
							}
							FileOut srcfile_out(dest);
							srcfile_out << content;
						}
					}
					
					fout << "\t\t\t\t},\n";
				}
				
				fout << "\t\t\t],\n";
			}
			
			ValueArray outputs = pass.GetAdd("outputs");
			if (outputs.GetCount()) {
				fout << "\t\t\toutputs: [\n";
				for(int j = 0; j < outputs.GetCount(); j++) {
					fout << "\t\t\t\t{\n";
					
					ValueMap output = outputs[j];
					
					String id = output.GetAdd("id");
					//String ch = output.Find("channel") >= 0 ? IntStr(output.GetAdd("channel")) : "";
					int id_i = id_idx.FindAdd(id);
					
					//String pre = "pass-" + IntStr(i) + "-output-" + IntStr(ch) + "-";
					fout << "\t\t\t\t\tid: " << id_i << ",\n";
					//if (ch.GetCount())
					//	fout << "\t\t\t\t\tchannel: " << ch << ",\n";
					
					fout << "\t\t\t\t},\n";
				}
				fout << "\t\t\t],\n";
			}
			
			fout << "\t\t},\n";
		}
		
		fout << "\t]\n}\n";
		
		for(String type : required_types) {
			FileOut& rout = required_type_files.GetAdd(type);
			if (!rout.IsOpen()) {
				rout.Open(AppendFileName(dir, "requires_" + type + ".txt"));
			}
			rout << relpath << "\n";
		}
		
	}
	
	
	COUT("Writing single-pass file");
	FileOut p1_out(singlepass_path);
	SortIndex(p1_list, StdLess<String>());
	for(String s : p1_list)
		p1_out << s << "\n";
	
	COUT("Writing multi-pass file");
	FileOut pX_out(multipass_path);
	SortIndex(pX_list, StdLess<String>());
	for(String s : pX_list)
		pX_out << s << "\n";
	
	COUT("Success.");
}

#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


void SimpleCascadeClassifier::Jsonize(JsonIO& json) {
	json
		("features", features),
		("threshold", threshold),
		("left_val", left_val),
		("right_val", right_val),
		("tilted", tilted) // haar::detect_single_scale
	;
	if (json.IsLoading()) {
		threshold = json.Get("threshold");
		left_val = json.Get("left_val");
		right_val = json.Get("right_val");
		tilted = json.Get("tilted");
	}
}

void ComplexCascadeClassifier::Jsonize(JsonIO& json) {
	json
		("simple_classifiers", classifiers)
		("threshold", threshold) // haar::detect_single_scale
	;
	if (json.IsLoading()) {
		threshold = json.Get("threshold");
	}
}

void ComplexCascade::Jsonize(JsonIO& json) {
	json
		("size", size)
		("tilted", tilted)
		("complex_classifiers", classifiers)
	;
	if (json.IsLoading()) {
		tilted = json.Get("tilted");
	}
}

String ComplexCascade::GetCppLoader(String name) const {
	String s;
	s	<< "void LoadCascade" + name + "(Cascade& c) {\n"
		<< "	c.classifiers.SetCount(" << classifiers.GetCount() << ");\n"
		<< "	auto sc_iter = c.classifiers.Begin();\n";
	;
	for(const ComplexCascadeClassifier& sc : classifiers) {
		s	<< "	{\n"
			<< "		ComplexCascadeClassifier& sc = *sc_iter++;\n"
			<< "		sc.classifiers.SetCount(" << sc.classifiers.GetCount() << ");\n"
			<< "		auto cf_iter = sc.classifiers.Begin();\n"
		;
		for(const SimpleCascadeClassifier& cf : sc.classifiers) {
			s	<< "		{\n"
				<< "			SimpleCascadeClassifier& cf = *cf_iter++;\n"
				<< "			cf.threshold = " << cf.threshold << ";\n"
				<< "			cf.left_val = " << cf.left_val << ";\n"
				<< "			cf.right_val = " << cf.right_val << ";\n"
				<< "			cf.features.SetCount(" << cf.features.GetCount() << ");\n";
			for(int i = 0; i < cf.features.GetCount(); i++) {
				const Vector<int>& v = cf.features[i];
				s	<< "			Vector<int>& v = cf.features[i];\n"
					<< "			v.Reserve(" << v.GetCount() << ");\n"
					<< "			v ";
				for (int i : v)
					s << " << " << i;
				s << ";\n";
			}
			s	<< "		}\n";
		}
		s	<< "	}\n";
	}
	s	<< "}\n\n";
	return s;
}

void CascadeFeature::Jsonize(JsonIO& json)
{
	json
		("size",	size)
		("px",		px)
		("py",		py)
		("pz",		pz)
		("nx",		nx)
		("ny",		ny)
		("nz",		nz)
	;
}

void CascadeStageClassifier::Jsonize(JsonIO& json)
{
	json
		("count",		count)
		("threshold",	threshold)
		("feature",		features)
		("alpha",		alpha)
	;
};

void Cascade::Jsonize(JsonIO& json)
{
	json
		("count",				count)
		("width",				width)
		("height",				height)
		("stage_classifier",	classifiers)
	;
}



String Cascade::GetCppLoader(String name) const {
	String s;
	s	<< "void LoadCascade" + name + "(Cascade& c) {\n"
		<< "	c.count = " << count << ";\n"
		<< "	c.width = " << width << ";\n"
		<< "	c.height = " << height << ";\n"
		<< "	c.classifiers.SetCount(" << classifiers.GetCount() << ");\n"
		<< "	auto sc_iter = c.classifiers.Begin();\n";
	;
	for(const CascadeStageClassifier& sc : classifiers) {
		
		s	<< "	{\n"
			<< "		CascadeStageClassifier& sc = *sc_iter++;\n"
			<< "		sc.count = " << sc.count << ";\n"
			<< "		sc.threshold = " << sc.threshold << ";\n"
			<< "		sc.features.SetCount(" << sc.features.GetCount() << ");\n"
			<< "		sc.alpha.SetCount(" << sc.alpha.GetCount() << ");\n"
			<< "		auto cf_iter = sc.features.Begin();\n"
			<< "		auto a_iter = sc.alpha.Begin();\n"
		;
		
		for(const CascadeFeature& cf : sc.features) {
			s	<< "		{\n"
				<< "			CascadeFeature& cf = *cf_iter++;\n"
				<< "			cf.size = " << cf.size << ";\n"
				<< "			cf.Reserve(" << cf.size << ");\n";
			s	<< "			cf.px"; for (int i : cf.px) s << " << " << i; s << ";\n";
			s	<< "			cf.py"; for (int i : cf.py) s << " << " << i; s << ";\n";
			s	<< "			cf.pz"; for (int i : cf.pz) s << " << " << i; s << ";\n";
			s	<< "			cf.nx"; for (int i : cf.nx) s << " << " << i; s << ";\n";
			s	<< "			cf.ny"; for (int i : cf.ny) s << " << " << i; s << ";\n";
			s	<< "			cf.nz"; for (int i : cf.nz) s << " << " << i; s << ";\n";
			s	<< "		}\n";
		}
		
		for (double d : sc.alpha) s << "		*a_iter++ = " << d << ";\n";
		
		s	<< "	}\n";
		
	}
	
	s	<< "}\n\n";
	return s;
}



bool LoadCascadeJs(String path, String dst_title, String dst_dir) {
	String dst_path = AppendFileName(dst_dir, "Cascade" + dst_title + ".cpp");
	LOG("\tExporting to " << dst_path);
	
	String content = LoadFile(path);
	Vector<String> lines = Split(content, "\n");
	int line_i = -1;
	for(int i = 0; i < lines.GetCount(); i++)
		if (lines[i].Left(11) == "    global." || lines[i].Left(8) == "	global.")
			{line_i = i; break;}
	if (line_i < 0) {
		LOG("error: did not find right line in content");
		return false;
	}
	
	content = lines[line_i];
	int a = content.Find("{");
	int b = content.ReverseFind("}");
	if (a < 0 || b < 0) {
		LOG("error:could not find json range");
		return false;
	}
	content = content.Mid(a, b-a+1);
	LOG("\tcontent range found with size " << b-a);
	
	if (content.Find("complexClassifiers") >= 0) {
		content.Replace("features", "\"features\"");
		content.Replace("threshold", "\"threshold\"");
		content.Replace("left_val", "\"left_val\"");
		content.Replace("right_val", "\"right_val\"");
		content.Replace("classifiers", "\"classifiers\"");
		content.Replace("simpleClassifiers", "\"simpleClassifiers\"");
		content.Replace("complexClassifiers", "\"complexClassifiers\"");
		content.Replace("size", "\"size\"");
		content.Replace("tilted", "\"tilted\"");
		
		Value root = ParseJSON(content);
		if (root.IsNull() || root.IsError()) {
			LOG("error: parsing json failed");
			LOG(content);
			return false;
		}
		
		//LOG(AsJSON(root, true));
		
		ComplexCascade cascade;
		LoadFromJsonValue(cascade, root);
		
		//LOG(StoreAsJson(cascade, true));
		
		String loader = cascade.GetCppLoader(dst_title);
		//LOG(loader);
		
		FileOut fout(dst_path);
		if (!fout.IsOpen()) {
			LOG("error: could not open file " << dst_path);
			return false;
		}
		
		fout	<< "#include \"ComputerVision.h\"\n\n\n"
				<< "NAMESPACE_TOPSIDE_BEGIN\n\n"
				<< loader
				<< "NAMESPACE_TOPSIDE_END\n\n"
		;
		fout.Close();
		
		LOG("\tsuccess");
	}
	else {
		Value root = ParseJSON(content);
		if (root.IsNull() || root.IsError()) {
			LOG("error: parsing json failed");
			LOG(content);
			return false;
		}
		
		//LOG(AsJSON(root, true));
		
		Cascade cascade;
		LoadFromJsonValue(cascade, root);
		
		//LOG(StoreAsJson(cascade, true));
		
		String loader = cascade.GetCppLoader(dst_title);
		//LOG(loader);
		
		FileOut fout(dst_path);
		if (!fout.IsOpen()) {
			LOG("error: could not open file " << dst_path);
			return false;
		}
		
		fout	<< "#include \"ComputerVision.h\"\n\n\n"
				<< "NAMESPACE_TOPSIDE_BEGIN\n\n"
				<< loader
				<< "NAMESPACE_TOPSIDE_END\n\n"
		;
		fout.Close();
		
		LOG("\tsuccess");
	}
	
	return true;
}

template <class T>
void LoadCascadeJsonFile(T& c, String title) {
	String path = RealizeShareFile("json" DIR_SEPS + title + ".json");
	String json = LoadFile(path);
	if (json.IsEmpty()) {
		LOG("LoadCascadeJsonFile: error: could not load file " + path);
		return;
	}
	
	LoadFromJson(c, json);
}

void LoadCascadeBbfFace(Cascade& c) {LoadCascadeJsonFile(c, "BbfFace");}
void LoadCascadeEye(ComplexCascade& c) {LoadCascadeJsonFile(c, "Eye");}
void LoadCascadeFrontalFace(ComplexCascade& c) {LoadCascadeJsonFile(c, "FrontalFace");}
void LoadCascadeHandFist(ComplexCascade& c) {LoadCascadeJsonFile(c, "HandFist");}
void LoadCascadeHandOpen(ComplexCascade& c) {LoadCascadeJsonFile(c, "HandOpen");}
void LoadCascadeMouth(ComplexCascade& c) {LoadCascadeJsonFile(c, "Mouth");}
void LoadCascadeProfileFace(ComplexCascade& c) {LoadCascadeJsonFile(c, "ProfileFace");}
void LoadCascadeUpperBody(ComplexCascade& c) {LoadCascadeJsonFile(c, "UpperBody");}


NAMESPACE_TOPSIDE_END

#ifndef _TextDatabase_DatabaseClass_h_
#define _TextDatabase_DatabaseClass_h_


BEGIN_TEXTLIB_NAMESPACE



struct Translation : Moveable<Translation> {
	VectorMap<String, String> data;
	
	Translation& Add(String key, String value) {data.GetAdd(key) = value; return *this;}
	void Serialize(Stream& s) {
		s % data;
	}
	void Jsonize(JsonIO& json) {
		if (json.IsStoring())
			SortByKey(data, StdLess<String>());
		json
			("data", data)
			;
		if (json.IsLoading()) {
			VectorMap<String, String> tmp;
			for(int i = 0; i < data.GetCount(); i++)
				tmp.Add(ToLower(data.GetKey(i)), ToLower(data[i]));
			Swap(tmp, data);
		}
	}
};


struct StructuredScript : Moveable<StructuredScript> {
	struct Part : Moveable<Part> {
		String name, person;
		Vector<String> lines;
		void Jsonize(JsonIO& json) {
			json
				("name", name)
				("person", person)
				("lines", lines)
				;
		}
	};
	String entity, title, structure_str;
	Vector<Part> parts;
	
	String AsText() const;
	Part& GetAddPart(String name) {
		for (Part& p : parts) if (p.name == name) return p;
		Part& p = parts.Add();
		p.name = name;
		return p;
	}
	void Jsonize(JsonIO& json) {
		json
			("entity", entity)
			("title", title)
			("structure_str", structure_str)
			("parts", parts)
			;
	}
};



struct SoftRequirement {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftCollaborator {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftMarketingStrategy {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftFeedback {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftProduct {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftUserNeed {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftGenre {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftMarketTrend {
	String name;
	String description;
	Index<int> targets;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("targets", targets)
			;
	}
};

struct SoftMarketTarget {
	struct Trend {
		int idx;
		Vector<int> genres;
		Vector<int> user_needs;
		Vector<int> products;
		Vector<int> feedbacks;
		Vector<int> marketing_strategies;
		Vector<int> collaborators;
		Vector<int> requirements;
		Vector<String> pricing;
		
		void Jsonize(JsonIO& json) {
			json
				("idx",idx)
				("gengres",genres)
				("user_needs",user_needs)
				("products",products)
				("feedbacks",feedbacks)
				("marketing_strategies",marketing_strategies)
				("collaborators",collaborators)
				("requirements",requirements)
				("pricing",pricing)
			;
		}
	};
	String name;
	String description;
	Array<Trend> trends;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("trends", trends)
			;
	}
};

struct SoftProjectManagement {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftCollaborationTool {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftIntegrationApi {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftDeployment {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftDataProcessing {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftAlgorithm {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftDataFormat {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftSecurityFramework {
	String name;
	String description;
	Index<int> langs;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("langs", langs)
			;
	}
};

struct SoftUserInterface {
	String name;
	String description;
	Index<int> langs;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("langs", langs)
			;
	}
};

struct SoftDatabase {
	String name;
	String description;
	Index<int> langs;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("langs", langs)
			;
	}
};

struct SoftTestingFramework {
	String name;
	String description;
	Index<int> langs;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("langs", langs)
			;
	}
};

struct SoftBuildTool {
	String name;
	String description;
	Index<int> langs;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("langs", langs)
			;
	}
};

struct SoftProjectType {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftIDE {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftParadigm {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct SoftLanguage {
	String name;
	String description;
	Vector<int> formats;
	Vector<int> algos;
	Vector<int> data_procs;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("formats",formats)
			("algos",algos)
			("data_procs",data_procs)
			;
	}
};

struct SoftLibrary {
	String name;
	String description;
	Index<int> langs;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("langs", langs)
			;
	}
};

struct SoftPlatform {
	String name;
	String description;
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			;
	}
};

struct HardPlatform {
	struct Lang {
		int lng = -1;
		Vector<int> ides;
		Vector<int> libs;
		Vector<int> project_types;
		Vector<int> build_tools;
		Vector<int> tests;
		Vector<int> dbs;
		Vector<int> uis;
		Vector<int> secs;
		
		void Jsonize(JsonIO& j) {
			j
				("lng",lng)
				("ides",ides)
				("libs",libs)
				("project_types",project_types)
				("build_tools",build_tools)
				("tests",tests)
				("dbs",dbs)
				("uis",uis)
				("secs",secs)
			;
		}
	};
	String name;
	String description;
	Vector<int> os;
	Array<Lang> langs;
	Vector<int> paradigms;
	Vector<int> deployments;
	
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("description", description)
			("os", os)
			("langs", langs)
			("paradigms", paradigms)
			("deployments", deployments)
			;
	}
};

struct TextDatabase {
	// Share
	Array<Entity>					entities;
	VectorMap<String, Translation>	translation;
	Array<Package>					pkgs;
	
	Vector<StructuredScript>		structured_scripts;
	Array<HardPlatform>				platforms;
	Array<SoftPlatform>				os;
	Array<SoftLanguage>				langs;
	Array<SoftParadigm>				paradigms;
	Array<SoftIDE>				ides;
	Array<SoftLibrary>				libs;
	Array<SoftProjectType>			project_types;
	Array<SoftBuildTool>			build_tools;
	Array<SoftTestingFramework>		tests;
	Array<SoftDatabase>				dbs;
	Array<SoftUserInterface>		uis;
	Array<SoftSecurityFramework>	secs;
	Array<SoftDataFormat>			formats;
	Array<SoftAlgorithm>			algos;
	Array<SoftDataProcessing>		data_procs;
	Array<SoftDeployment>			deployments;
	Array<SoftIntegrationApi>		apis;
	Array<SoftCollaborationTool>	collab_tools;
	Array<SoftProjectManagement>	prj_manags;
	Array<SoftMarketTarget>			market_targets;
	Array<SoftMarketTrend>			market_trends;
	Array<SoftGenre>				genres;
	Array<SoftProduct>				products;
	Array<SoftUserNeed>				user_needs;
	Array<SoftMarketingStrategy>	marketing_strategies;
	Array<SoftFeedback>				feedbacks;
	Array<SoftCollaborator>			collaborators;
	Array<SoftRequirement>			requirements;
	
	// Source
	SourceData		src_data;
	
	// Temp
	RWMutex			lock;
	bool			loaded = false;
	
	TextDatabase();
	Array<Entity>& GetSub() {return entities;}
	const Array<Entity>& GetSub() const {return entities;}
	void Clear() {entities.Clear(); }
	void Store();
	void Load();
	void FindOrphaned();
	
	#define GETADD_FN(fn, type, vars) type& fn(const String& name, int* idx=0);
	GETADD_FN(GetAddPlatform, HardPlatform, platforms)
	GETADD_FN(GetAddOS, SoftPlatform, os)
	GETADD_FN(GetAddLanguage, SoftLanguage, langs)
	GETADD_FN(GetAddParadigm, SoftParadigm, paradigms)
	GETADD_FN(GetAddIDE, SoftIDE, ides)
	GETADD_FN(GetAddLibrary, SoftLibrary, libs)
	GETADD_FN(GetAddProjectType, SoftProjectType, project_types)
	GETADD_FN(GetAddBuildTool, SoftBuildTool, build_tools)
	GETADD_FN(GetAddTestingFramework, SoftTestingFramework, tests)
	GETADD_FN(GetAddDatabase, SoftDatabase, dbs)
	GETADD_FN(GetAddUserInterface, SoftUserInterface, uis)
	GETADD_FN(GetAddSecurityFramework, SoftSecurityFramework, secs)
	GETADD_FN(GetAddDataFormat, SoftDataFormat, formats)
	GETADD_FN(GetAddAlgorithm, SoftAlgorithm, algos)
	GETADD_FN(GetAddDataProcessing, SoftDataProcessing, data_procs)
	GETADD_FN(GetAddDeployment, SoftDeployment, deployments)
	GETADD_FN(GetAddMarketTarget, SoftMarketTarget, market_targets)
	GETADD_FN(GetAddMarketTrend, SoftMarketTrend, market_trends)
	GETADD_FN(GetAddGenre, SoftGenre, genres)
	GETADD_FN(GetAddProduct, SoftProduct, products)
	GETADD_FN(GetAddUserNeed, SoftUserNeed, user_needs)
	GETADD_FN(GetAddMarketingStrategy, SoftMarketingStrategy, marketing_strategies)
	GETADD_FN(GetAddFeedback, SoftFeedback, feedbacks)
	GETADD_FN(GetAddCollaborator, SoftCollaborator, collaborators)
	GETADD_FN(GetAddRequirement, SoftRequirement, requirements)
	#undef GETADD_FN
	
	/*void Serialize(Stream& s) {
		s	% entities
			% translation;
	}*/
	void Jsonize(JsonIO& json) {
		json
			("structured_scripts", structured_scripts)
			("platforms", platforms)
			("os", os)
			("langs", langs)
			("paradigms", paradigms)
			("ides", ides)
			("libs", libs)
			("project_types", project_types)
			("build_tools", build_tools)
			("tests", tests)
			("dbs", dbs)
			("uis", uis)
			("secs", secs)
			("formats", formats)
			("algos", algos)
			("data_procs", data_procs)
			("deployments", deployments)
			("apis", apis)
			("collab_tools", collab_tools)
			("prj_manags", prj_manags)
			("market_targets", market_targets)
			("market_trends", market_trends)
			("genres", genres)
			("products", products)
			("user_needs", user_needs)
			("marketing_strategies", marketing_strategies)
			("feedbacks", feedbacks)
			("collaborators", collaborators)
			("requirements", requirements)
			;
	}
	String GetEntitiesDir() const;
	String GetSnapshotsDir() const;
	String GetComponentsDir() const;
	String GetPackageDir() const;
	
	String Translate(const String& s);
	//static int trans_i; // active language translation index
	Entity& GetAddEntity(Profile& p);
	
};


struct Belief {
	struct Attr : Moveable<Attr> {
		String positive, negative;
		void Jsonize(JsonIO& json) {json("positive",positive)("negative",negative);}
	};
	int64 uniq = 0;
	String name, reference;
	Vector<Attr> attrs;
	Vector<String> user;
	
	void Jsonize(JsonIO& json) {
		json("uniq", uniq)("name", name)("reference", reference)("attrs", attrs)("user", user);
		if (json.IsLoading() && uniq == 0) uniq = Random64();
	}
};


struct MetaDatabase {
	TextDatabase db;
	
	//Array<MetaEntity>	meta_entities;
	Array<Owner>				owners;
	Array<Belief>				beliefs;
	
	// Temp
	String						dir, share;
	
public:
	
	MetaDatabase();
	void Store();
	void Load();
	void Jsonize(JsonIO& json);
	static MetaDatabase& Single();
	static String GetDirectory();
	
	
};


TextDatabase& GetAppModeDatabase();
EditorPtrs& GetAppModePointers();
bool HasAnyEditor();
ToolEditor& GetAnyEditor();


END_TEXTLIB_NAMESPACE


#endif

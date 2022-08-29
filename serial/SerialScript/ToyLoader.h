#ifndef _SerialScript_ToyLoader_h_
#define _SerialScript_ToyLoader_h_


#if 0


// ShaderToy file loader (libtopside .toy format == unpacked .js + stage info + separate glsl)


NAMESPACE_SERIAL_BEGIN


struct ToyInput : Moveable<ToyInput> {
	String				stage_name;
	String				id;
	String				type;
	String				filter;
	String				wrap;
	String				vflip;
	String				filename;
	
	void Clear();
	
};

struct ToyStage : Moveable<ToyStage> {
	Vector<ToyInput>	inputs;
	Vector<String>		user_stages;
	String				name;
	String				type;
	String				output_id;
	String				script;
	String				script_path;
	String				stage_name;
	int					loopback_stage = -1;
	
};


class ToyLoader {
	Vector<ToyStage>	stages;
	Vector<String>		libraries;
	String				eon_script;
	
	
	bool FindStageNames();
	bool MakeScript();
	void PruneLibraries();
	bool SolveLoopbacks();
	
public:
	typedef ToyLoader CLASSNAME;
	ToyLoader();
	
	bool Load(Object& o);
	
	String GetResult();
	
	
	static const ObjectMap* GetStageMap(int i, Object& o);
	static String GetStageType(int i, Object& o);
	static String GetStagePath(int i, Object& o);
	/*static String GetSingleBufferVideo(String glsl_path);
	static String GetDoubleBufferVideo(String glsl_path0, String glsl_path1);
	static String GetTripleBufferVideo(String glsl_path0, String glsl_path1, String glsl_path2);*/
	
};


NAMESPACE_SERIAL_END

#endif
#endif

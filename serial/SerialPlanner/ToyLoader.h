#ifndef _SerialPlanner_ToyLoader_h_
#define _SerialPlanner_ToyLoader_h_


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
	
};

struct ToyStage : Moveable<ToyStage> {
	Vector<ToyInput>	inputs;
	Vector<String>		user_stages;
	String				name;
	String				type;
	String				output_id;
	String				script;
	String				script_path;
	
	
};


class ToyLoader {
	Vector<ToyStage>	stages;
	String				eon_script;
	
	
	bool FindStageNames();
	bool MakeScript();
	
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


ArrayMap<String,String>& ToyShaderHashToName();
String RealizeFilepathArgument(String arg_filepath);


NAMESPACE_SERIAL_END

#endif

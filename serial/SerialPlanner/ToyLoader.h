#ifndef _SerialPlanner_ToyLoader_h_
#define _SerialPlanner_ToyLoader_h_


// ShaderToy file loader (libtopside .toy format == unpacked .js + stage info + separate glsl)


NAMESPACE_SERIAL_BEGIN


class ToyLoader {
	String eon_script;
	
public:
	typedef ToyLoader CLASSNAME;
	ToyLoader();
	
	bool Load(Object& o);
	
	String GetResult();
	
	
	static const ObjectMap* GetStageMap(int i, Object& o);
	static String GetStageType(int i, Object& o);
	static String GetStagePath(int i, Object& o);
	static String GetSingleBufferVideo(String glsl_path);
	static String GetDoubleBufferVideo(String glsl_path0, String glsl_path1);
	static String GetTripleBufferVideo(String glsl_path0, String glsl_path1, String glsl_path2);
	
};


NAMESPACE_SERIAL_END

#endif

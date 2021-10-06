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
	
	static String GetSingleBufferVideo(String glsl_path);
	
};


NAMESPACE_SERIAL_END

#endif

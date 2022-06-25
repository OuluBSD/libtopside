#ifndef _Local_Graphics_h_
#define _Local_Graphics_h_


NAMESPACE_TOPSIDE_BEGIN


class RenderingVerifier {
	struct Var : Moveable<Var> {
		bool updated = false;
		bool state_var = false;
		String key;
		
	};
	
	struct Object : Moveable<Object> {
		int id;
		bool updated_view = false;
		bool updated_proj = false;
		bool updated_scale = false;
		bool updated_model = false;
		
	};
	
	VectorMap<String, Var> vars;
	VectorMap<int, Object> objs;
	
public:
	typedef RenderingVerifier CLASSNAME;
	RenderingVerifier();
	
	void OnClearVars();
	void OnRealizeVar(String key, bool state_var);
	void OnUpdateVar(String key);
	void OnRealizeObject(int id);
	void OnUpdateObject(int id, int var);
	void OnProcess();
	
	static RenderingVerifier& Local() {static RenderingVerifier v; return v;}
	
	enum {
		VIEW,
		PROJECT,
		SCALE,
		MODEL
	};
};


#if 0
	#define RendVer(x) RenderingVerifier::Local(). x ()
	#define RendVer1(x, y) RenderingVerifier::Local(). x (y)
	#define RendVer2(x, a0, a1) RenderingVerifier::Local(). x (a0, a1)
#else
	#define RendVer(x)
	#define RendVer1(x, y)
	#define RendVer2(x, a0, a1)
#endif



extern int default_width;
extern int default_height;


NAMESPACE_TOPSIDE_END


#endif

#ifndef _Shadertoy_Loader_h_
#define _Shadertoy_Loader_h_

NAMESPACE_TOPSIDE_BEGIN


class ShadertoyContextLoader :
	public TypeContextLoader
{
	int id_counter = 0;
	
	bool		LoadFileToy(String path, Object& dst);
	void		OnError(TypeCls type, String fn, String msg);
	void		OnError(String fn, String msg);
	void		MakeUniqueIds(Object& v);
	void		Clear();
	int			MakeUniqueId(VectorMap<int,int>& ids, int orig_id);
	
public:
	typedef ShadertoyContextLoader CLASSNAME;
	ShadertoyContextLoader();
	
	bool		Load(String path, Object& o, ContextComponentBase* b) override;
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif

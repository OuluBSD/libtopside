#ifndef _SerialCore_State_h_
#define _SerialCore_State_h_

NAMESPACE_SERIAL_BEGIN


class EnvState :
	public RefScopeEnabler<EnvState, MetaDirectoryBase>
{
	VectorMap<dword, Object> data;
	String name;
	
public:
	
	void SetName(String s) {name = s;}
	const String& GetName() const {return name;}
	
	
	bool&	SetBool(dword key, bool b);
	int&	SetInt(dword key, int i);
	
	bool&	GetBool(dword key);
	int&	GetInt(dword key);
	
	template <class T>
	T& Set(dword key) {
		Object& o = data.GetAdd(key);
		if (o.Is<T>())
			return o.Get<T>();
		else
			return o.Create<T>();
	}
	
};


NAMESPACE_SERIAL_END

#endif

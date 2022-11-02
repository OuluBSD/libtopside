#ifndef _AudioHost_Loader_h_
#define _AudioHost_Loader_h_


NAMESPACE_TOPSIDE_BEGIN


class MidiEonContextLoader
{
	int			id_counter = 0;
	String		last_error;
	String		result;
	
	
	bool		LoadFileMidi(String path, Object& dst);
	void		OnError(TypeCls type, String fn, String msg);
	void		OnError(String fn, String msg);
	void		Clear();
	
public:
	typedef MidiEonContextLoader CLASSNAME;
	MidiEonContextLoader();
	
	bool		Load(String path, Object& o);
	String		GetResult() const {return result;}
	
	
	Callback	WhenError;
	
};


struct SerialMidiEonLoader : SerialLoaderBase {
	
	virtual String LoadFile(String file_path) override;
	
};

NAMESPACE_TOPSIDE_END

#endif

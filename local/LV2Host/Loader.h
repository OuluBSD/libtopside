#ifndef _LV2Host_Loader_h_
#define _LV2Host_Loader_h_

NAMESPACE_TOPSIDE_BEGIN


class MidiLV2ContextLoader
{
	int			id_counter = 0;
	String		last_error;
	
	
	bool		LoadFileMidi(String path, Object& dst);
	void		OnError(TypeCls type, String fn, String msg);
	void		OnError(String fn, String msg);
	void		Clear();
	
public:
	typedef MidiLV2ContextLoader CLASSNAME;
	MidiLV2ContextLoader();
	
	bool		Load(String path, Object& o);
	
	
	Callback	WhenError;
	
};


struct SerialMidiLV2Loader : SerialLoaderBase {
	
	virtual String LoadFile(String file_path) override;
	
};

NAMESPACE_TOPSIDE_END

#endif

#ifndef _AtomMusic_AtomMusic_h_
#define _AtomMusic_AtomMusic_h_

#include <Local/Local.h>
#include <SerialLib/SerialLib.h>


NAMESPACE_SERIAL_BEGIN

#if 0

class MusicDrummerComponent :
	public Component<MusicDrummerComponent>
{
	String last_error;
	
public:
	RTTI_COMP0(MusicDrummerComponent)
	COPY_PANIC(MusicDrummerComponent);
	COMP_DEF_VISIT
	
	MusicDrummerComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicBassistComponent :
	public Component<MusicBassistComponent>
{
	String last_error;
	
public:
	RTTI_COMP0(MusicBassistComponent)
	COPY_PANIC(MusicBassistComponent);
	COMP_DEF_VISIT
	
	MusicBassistComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicGuitaristComponent :
	public Component<MusicGuitaristComponent>
{
	String last_error;
	
public:
	RTTI_COMP0(MusicGuitaristComponent)
	COPY_PANIC(MusicGuitaristComponent);
	COMP_DEF_VISIT
	
	MusicGuitaristComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicVocalistComponent :
	public Component<MusicVocalistComponent>
{
	
	String last_error;
	
public:
	RTTI_COMP0(MusicVocalistComponent)
	COPY_PANIC(MusicVocalistComponent);
	COMP_DEF_VISIT
	
	MusicVocalistComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicConductorComponent :
	public Component<MusicConductorComponent>
{
	String last_error;
	
public:
	RTTI_COMP0(MusicConductorComponent)
	COPY_PANIC(MusicConductorComponent);
	COMP_DEF_VISIT
	
	MusicConductorComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicComposerComponent :
	public Component<MusicComposerComponent>
{
	String last_error;
	
public:
	RTTI_COMP0(MusicComposerComponent)
	COPY_PANIC(MusicComposerComponent);
	COMP_DEF_VISIT
	
	MusicComposerComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


#endif

NAMESPACE_SERIAL_END

#endif

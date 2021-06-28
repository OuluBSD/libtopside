#ifndef _Music_Music_h_
#define _Music_Music_h_

#include <Local/Local.h>
#include <EcsLib/EcsLib.h>


NAMESPACE_TOPSIDE_BEGIN



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







PREFAB_BEGIN(CompleteMusicDrummer)
		MusicDrummerComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMusicBassist)
		MusicBassistComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMusicGuitarist)
		MusicGuitaristComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMusicVocalist)
		MusicVocalistComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMusicConductor)
		MusicConductorComponent
PREFAB_END;

PREFAB_BEGIN(CompleteMusicComposer)
		MusicComposerComponent
PREFAB_END;


NAMESPACE_TOPSIDE_END

#endif

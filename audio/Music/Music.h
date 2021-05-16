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
	VIS_COMP_0_0
	COPY_PANIC(MusicDrummerComponent);
	
	MusicDrummerComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicBassistComponent :
	public Component<MusicBassistComponent>
{
	String last_error;
	
public:
	VIS_COMP_0_0
	COPY_PANIC(MusicBassistComponent);
	
	MusicBassistComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicGuitaristComponent :
	public Component<MusicGuitaristComponent>
{
	String last_error;
	
public:
	VIS_COMP_0_0
	COPY_PANIC(MusicGuitaristComponent);
	
	MusicGuitaristComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicVocalistComponent :
	public Component<MusicVocalistComponent>
{
	
	String last_error;
	
public:
	VIS_COMP_0_0
	COPY_PANIC(MusicVocalistComponent);
	
	MusicVocalistComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicConductorComponent :
	public Component<MusicConductorComponent>
{
	String last_error;
	
public:
	VIS_COMP_0_0
	COPY_PANIC(MusicConductorComponent);
	
	MusicConductorComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void EvaluateRequest(String req_str);
	
	String GetLastError() const {return last_error;}
	
	
	Callback WhenError;
	
};


class MusicComposerComponent :
	public Component<MusicComposerComponent>
{
	String last_error;
	
public:
	VIS_COMP_0_0
	COPY_PANIC(MusicComposerComponent);
	
	MusicComposerComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
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

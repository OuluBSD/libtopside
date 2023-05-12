#ifndef _IGraphics_EcsViewProg_h_
#define _IGraphics_EcsViewProg_h_

NAMESPACE_PARALLEL_BEGIN


struct EcsViewProg :
	public BinderIfaceVideo
{
	RTTI_DECL1(EcsViewProg, BinderIfaceVideo)
	
	EcsViewProg();
	void operator=(const EcsViewProg& t) {Panic("Can't copy EcsViewProgT");}
	void Visit(RuntimeVisitor& vis) override {}
	void Initialize() override;
	void Uninitialize() override;
	bool Render(Draw& draw) override;
	bool Arg(const String& key, const String& value) override;
	
};


NAMESPACE_PARALLEL_END

#endif

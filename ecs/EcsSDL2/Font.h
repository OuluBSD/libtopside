#ifndef _EcsSDL2_Font_h_
#define _EcsSDL2_Font_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2FontComponent :
	public Component<SDL2FontComponent>,
	public StaticSource
{
	Font fnt;
	
public:
	RTTI_COMP1(SDL2FontComponent, StaticSource)
	VIS_COMP_1_0(Static)
	COPY_PANIC(SDL2FontComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
	COMP_DEF_VISIT
	
	SDL2FontComponent() = default;
	
	void Initialize() override;
	void Uninitialize() override;
	StaticStream&		GetStream(StcCtx) override {TODO}
	void				BeginStream(StcCtx) override {TODO}
	void				EndStream(StcCtx) override {TODO}
	
	static bool AllowDuplicates() {return true;}
	
};



NAMESPACE_TOPSIDE_END

#endif

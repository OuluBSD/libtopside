#ifndef _EcsSDL2_Image_h_
#define _EcsSDL2_Image_h_

NAMESPACE_TOPSIDE_BEGIN



class SDL2ImageComponent :
	public Component<SDL2ImageComponent>,
	public StaticSource
{
	struct LocalStatic : public SimpleBufferedStatic {
		RTTI_DECL1(LocalStatic, SimpleBufferedStatic)
		SDL2ImageComponent& par;
		LocalStatic(SDL2ImageComponent* par) : par(*par) {}
		
	};
	struct LocalStaticStream : public SimpleBufferedStaticStream {
		RTTI_DECL1(LocalStaticStream, SimpleBufferedStaticStream)
		SDL2ImageComponent& par;
		LocalStaticStream(SDL2ImageComponent* par) : par(*par), SimpleBufferedStaticStream(par->svalue) {}
		bool			IsOpen() const override {return par.IsOpen();}
		bool			Open(int fmt_idx) override {ASSERT(fmt_idx == 0); return par.Open(fmt_idx);}
		void			Close() override {par.Close();}
		bool			IsEof() override {return !par.IsOpen();}
		bool			ReadFrame() override {return par.ReadFrame();}
		bool			ProcessFrame() override {return par.ProcessFrame();}
		bool			ProcessOtherFrame() override {return false;}
		void			ClearPacketData() override {par.ClearPacketData();}
	};
	
	Vector<Image>				img;
	String						last_error;
	LocalStatic					svalue;
	LocalStaticStream			sstream;
	
public:
	RTTI_COMP1(SDL2ImageComponent, StaticSource)
	VIS_COMP_1_0(Static)
	COPY_PANIC(SDL2ImageComponent);
	IFACE_CB(StaticSource);
	IFACE_GENERIC;
	
	SDL2ImageComponent();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	bool LoadFileAny(String path);
	Size GetResolution() const;
	
	StaticStream&		GetStream(StcCtx) override;
	void				BeginStream(StcCtx) override;
	void				EndStream(StcCtx) override;
	
	bool				IsOpen() const {return !img.IsEmpty();}
	bool				Open(int) {return !img.IsEmpty();}
	void				Close() {img.Clear();}
	bool				ReadFrame() {return true;}
	bool				ProcessFrame() {return true;}
	void				ClearPacketData() {}
	String GetLastError() const {return last_error;}
	
	static bool AllowDuplicates() {return true;}
	
};

using SDL2ImageComponentRef			= Ref<SDL2ImageComponent,			RefParent1<Entity>>;


NAMESPACE_TOPSIDE_END

#endif

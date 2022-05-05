// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IImageFile_TmplClasses_h_
#define _IImageFile_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Img> struct ImageFileImageT;


template <class Img>
struct ImageFileImageT : ImgImage {
	using CLASSNAME = ImageFileImageT<Img>;
	RTTI_DECL1(CLASSNAME, ImgImage)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ImgImage>(this);}
	
	typename Img::NativeImage img;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Img::Image_Initialize(img, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Img::Image_PostInitialize(img, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Img::Image_Start(img, *this);
	}

	void Stop() override {
		Img::Image_Stop(img, *this);
	}

	void Uninitialize() override {
		Img::Image_Uninitialize(img, *this);
	}

	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {
		if (!Img::Image_Send(img, *this, cfg, out, src_ch))
			return false;
		return true;
	}

	bool CreateImage() {
		return Img::Image_CreateImage(this->img);
	}
	
	void ClearImage() {
		Img::Image_ClearImage(this->img);
	}
	
	
};


NAMESPACE_PARALLEL_END



#endif


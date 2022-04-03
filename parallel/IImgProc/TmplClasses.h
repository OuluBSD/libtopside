// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 22:44:00

#ifndef _IImgProc_TmplClasses_h_
#define _IImgProc_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Imp> struct ImgProcImageT;


template <class Imp>
struct ImgProcImageT : ImpImage {
	using CLASSNAME = ImgProcImageT<Imp>;
	RTTI_DECL1(CLASSNAME, ImpImage)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ImpImage>(this);}
	
	typename Imp::NativeImage dev;
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Imp::Image_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Imp::Image_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Imp::Image_Start(dev, *this);
	}

	void Stop() override {
		Imp::Image_Stop(dev, *this);
	}

	void Uninitialize() override {
		Imp::Image_Uninitialize(dev, *this);
	}

	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		if (!Imp::Image_ProcessPacket(dev, *this, in, out))
			return false;
		return true;
	}

	bool CreateImage() {
		return Imp::Image_CreateImage(this->dev);
	}
	
	void ClearImage() {
		Imp::Image_ClearImage(this->dev);
	}
	
	
};


NAMESPACE_PARALLEL_END



#endif


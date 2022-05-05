// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IVolumetric_TmplClasses_h_
#define _IVolumetric_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Vol> struct VolumetricStaticSourceT;


template <class Vol>
struct VolumetricStaticSourceT : VolStaticSource {
	using CLASSNAME = VolumetricStaticSourceT<Vol>;
	RTTI_DECL1(CLASSNAME, VolStaticSource)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<VolStaticSource>(this);}
	
	typename Vol::NativeStaticSource dev;
	
	
	bool Initialize(const Script::WorldState& ws) override {
		if (!Vol::StaticSource_Initialize(dev, *this, ws))
			return false;
		return true;
	}

	bool PostInitialize() override {
		if (!Vol::StaticSource_PostInitialize(dev, *this))
			return false;
		return true;
	}

	bool Start() override {
		return Vol::StaticSource_Start(dev, *this);
	}

	void Stop() override {
		Vol::StaticSource_Stop(dev, *this);
	}

	void Uninitialize() override {
		Vol::StaticSource_Uninitialize(dev, *this);
	}

	bool Send(PacketValue& out, int src_ch) override {
		if (!Vol::StaticSource_Send(dev, *this, out))
			return false;
		return true;
	}

	bool IsReady(PacketIO& io) override {
		return Vol::StaticSource_IsReady(dev, *this, io);
	}

	
};

#if (defined flagLINUX) || (defined flagFREEBSD)
using RawByteStaticSource = VolumetricStaticSourceT<VolRawByte>;
#endif


NAMESPACE_PARALLEL_END



#endif


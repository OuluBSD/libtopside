#ifndef _AtomSDL2_Sensor_h_
#define _AtomSDL2_Sensor_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN



class SDL2SensorBase :
	public SDL2BaseT<SDL2SensorBase>
{
	One<OOSDL2::Sensor> obj;
	
public:
	RTTI_DECL1(SDL2SensorBase, AltBaseT)
	COPY_PANIC(SDL2SensorBase)
	ATOM_DEF_VISIT
	
	SDL2SensorBase() = default;
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::Sensor* GetOOSDL2() {return &*obj;}
	
};



NAMESPACE_SERIAL_END

#endif
#endif

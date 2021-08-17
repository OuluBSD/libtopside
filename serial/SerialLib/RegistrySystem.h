#ifndef _SerialLib_RegistrySystem_h_
#define _SerialLib_RegistrySystem_h_

NAMESPACE_SERIAL_BEGIN

class RegistrySystem : public System<RegistrySystem> {
	
	
public:
	SYS_RTTI(RegistrySystem)
    SYS_CTOR(RegistrySystem)
	SYS_DEF_VISIT
	
};

NAMESPACE_SERIAL_END

#endif

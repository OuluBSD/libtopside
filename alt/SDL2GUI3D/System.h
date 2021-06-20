#ifndef _SDL2GUI3D_System_h_
#define _SDL2GUI3D_System_h_

#include <EcsLib/EcsLib.h>

NAMESPACE_TOPSIDE_BEGIN


class SDL2GUI3DSystem : public System<SDL2GUI3DSystem> {
	SDL2GUI3D gui;
	
	
	
public:
	SYS_RTTI(SDL2GUI3DSystem)
	SYS_CTOR_(SDL2GUI3DSystem), gui(this) {}
	SYS_DEF_VISIT
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
	
};



NAMESPACE_TOPSIDE_END

#endif

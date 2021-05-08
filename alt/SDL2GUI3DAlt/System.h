#ifndef _SDL2GUI3DAlt_System_h_
#define _SDL2GUI3DAlt_System_h_

#include <EcsLib/EcsLib.h>

NAMESPACE_OULU_BEGIN


class SDL2GUI3DAltSystem : public System<SDL2GUI3DAltSystem> {
	SDL2GUI3DAlt gui;
	
	
	void Visit(RuntimeVisitor& vis) override {}
public:
	SDL2GUI3DAltSystem(Machine& m);
	
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
	
};



NAMESPACE_OULU_END

#endif

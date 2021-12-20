#include <EcsComplete/EcsComplete.h>
using namespace TS;
using namespace TS::Ecs;


struct Tutorial0 :
	public Component<Tutorial0>,
	public BinderIfaceVideo
{
	RTTI_DECL2(Tutorial0, ComponentT, BinderIfaceVideo)
	
	void operator=(const Tutorial0& t) {Panic("Can't copy");}
	
	void Initialize() override {
		Serial::EcsVideoBase::Latest().AddBinder(this);
	}
	
	void Render(Draw& draw) override {
		draw.DrawRect(draw.GetPageSize(), Black());
	}
	
};


struct StandaloneTutorial0 : EntityPrefab<Tutorial0>
{
    static Components Make(Entity& e)
    {
        auto components = EntityPrefab::Make(e);
		return components;
    }
};


SIMPLE_ECS_APP_(Tutorial0, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")

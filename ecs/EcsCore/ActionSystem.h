#ifndef _EcsCore_ActionSystem_h_
#define _EcsCore_ActionSystem_h_


NAMESPACE_OULU_BEGIN


class ActionSystem : public System<ActionSystem> {
	LinkedList<ActionSourceRef> srcs;
	
	void Visit(RuntimeVisitor& vis) override {
		vis && srcs;
	}
public:
	SYS_CTOR(ActionSystem)
	
	void Add(ActionSourceRef src);
	void Remove(ActionSourceRef src);
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
	
};


NAMESPACE_OULU_END


#endif

#ifndef _EcsLib_Router_h_
#define _EcsLib_Router_h_

NAMESPACE_TOPSIDE_BEGIN


class PathwayRouter :
	public Connector<PathwayRouter>
{
	
public:
	RTTI_CONN0(PathwayRouter)
	COPY_PANIC(PathwayRouter);
	
	TypeCls GetType() const override {return AsTypeCls<PathwayRouter>();}
	void CopyTo(ConnectorBase* component) const override {}
	void Update(double dt) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	void AddGoalFulfill(EntityRef e);
	
};


NAMESPACE_TOPSIDE_END

#endif

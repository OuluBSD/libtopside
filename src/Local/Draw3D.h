#ifndef _Local_Draw3D_h_
#define _Local_Draw3D_h_

NAMESPACE_TOPSIDE_BEGIN

class Model;


class Draw3D :
	NoCopy,
	RTTIBase
{
	
	
public:
	RTTI_DECL0(Draw3D)
	
	virtual ~Draw3D() {}
	
	
	
	virtual void GuboDrawBegin(hash_t) {}
	virtual void GuboDrawEnd() {}
	
	virtual void SetSize(Volf v) = 0;
	virtual Volf GetPageSize() const = 0;
	
	virtual void DrawCuboid(const Point3f& pos, const Volf& sz, Color c) {DrawCuboid(pos, sz, 0, 0, c);}
	
	virtual void DrawModel(const Point3f& pos, const Model& mdl) = 0;
	virtual void DrawCuboid(const Point3f& pos, const Volf& sz, float yaw, float pitch, Color c) = 0;
	virtual void DrawSphere(const Point3f& pos, float radius, Color c) = 0;
	virtual void DrawLine(const Point3f& a, const Point3f& b, float line_width, Color c) = 0;
	
	virtual bool ClipOp(const Cubf& r) = 0;
	virtual void EndOp() = 0;
	
	
};


NAMESPACE_TOPSIDE_END

#endif

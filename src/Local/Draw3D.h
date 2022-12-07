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
	
	virtual void SetSize(Vol v) = 0;
	virtual Vol GetPageSize() const = 0;
	
	virtual void DrawModel(const Point3& pos, const Model& mdl) = 0;
	virtual void DrawCuboid(const Point3& pos, const Volf& sz, float yaw, float pitch, Color c) = 0;
	virtual void DrawSphere(const Point3& pos, float radius, Color c) = 0;
	virtual void DrawLine(const Point3& a, const Point3& b, float line_width, Color c) = 0;
	
	virtual bool ClipOp(const Cub& r) = 0;
	virtual void EndOp() = 0;
	
	
};


NAMESPACE_TOPSIDE_END

#endif

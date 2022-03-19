#ifndef _HighAnim_Object_h_
#define _HighAnim_Object_h_

NAMESPACE_TOPSIDE_BEGIN

typedef enum {
	TC_LINEAR,
	TC_SINUSOID,
	TC_SINUSOID_LOWER, // starts slow, accelerates
	TC_SINUSOID_HIGHER, // starts fast, decelerates
} TransformCurve;

class AnimKeypoint : Moveable<AnimKeypoint> {
	
public:
	typedef enum {
		E_ANGLE,
		E_POS,
		E_ANCHOR,
		
		E_COUNT
	} ValueType;
	
protected:
	friend class AnimObject;
	friend class AnimObjectPlayer;
	
	int idx;
	TransformCurve curve[E_COUNT];
	double angle;
	Point position, anchor;
	dword enabled_mask;
	
	void Clear();
	void Set(int i) {enabled_mask |= (1 << i);}
	void Unset(int i) {enabled_mask &= ~(1 << i);}
	
public:
	
	AnimKeypoint();
	
	bool Is(int i) const						{return (enabled_mask & (1 << i));}
	TransformCurve GetCurve(ValueType t) const	{ChkVT(t); return curve[t];}
	
	AnimKeypoint& SetAngle(double rad, TransformCurve c=TC_LINEAR)	{angle = rad; SetCurve(E_ANGLE,c); Set(E_ANGLE); return *this;}
	AnimKeypoint& SetPosition(Point p, TransformCurve c=TC_LINEAR)	{position = p; SetCurve(E_POS,c); Set(E_POS); return *this;}
	AnimKeypoint& SetAnchor(Point p, TransformCurve c=TC_LINEAR)	{anchor = p; SetCurve(E_ANCHOR,c); Set(E_ANCHOR); return *this;}
	
	AnimKeypoint& SetCurve(ValueType t, TransformCurve c)	{ChkVT(t); curve[t] = c; return *this;}
	AnimKeypoint& SetCurveLinear(ValueType t)				{SetCurve(t, TC_LINEAR); return *this;}
	AnimKeypoint& SetCurveSinusoid(ValueType t)				{SetCurve(t, TC_SINUSOID); return *this;}
	AnimKeypoint& SetCurveSinusoidLower(ValueType t)		{SetCurve(t, TC_SINUSOID_LOWER); return *this;}
	AnimKeypoint& SetCurveSinusoidHigher(ValueType t)		{SetCurve(t, TC_SINUSOID_HIGHER); return *this;}
	
	static void ChkVT(ValueType t) {ASSERT(t >= E_ANGLE && t < E_COUNT);}
	
};

class AnimObject {
	
public:
	typedef enum {
		V_VOID,
		V_TEXT,
		V_POLYGON,
	} Type;
	
protected:
	friend class AnimObjectPlayer;
	
	Array<AnimObject> objs;
	Array<AnimKeypoint> kps;
	
	Type type = V_VOID;
	int anim_len = 0;
	
	String str;
	int fnt_h = 0;
	Vector<Point> pts;
	Color clr;
	
public:
	typedef AnimObject CLASSNAME;
	AnimObject();
	
	void Clear();
	void RealizeKeypoint();
	void RemoveChild(AnimObject* o);
	
	AnimObject& Add() {return objs.Add();}
	AnimObject& SetText(String s, int fnt_h, Color clr);
	AnimObject& SetPolygon(Color clr);
	AnimObject& SetLength(int l);
	AnimObject& SetAnchorPointAverage();
	AnimObject& SetPosition(Point p);
	
	Vector<Point>& Points() {return pts;}
	AnimKeypoint& GetAddKeypoint(int idx);
	
	void Paint(Draw& d, const AnimFrameHeader& f, const AnimKeypointPlayer& kp);
	
	
};


using AObj = AnimObject;

NAMESPACE_TOPSIDE_END

#endif

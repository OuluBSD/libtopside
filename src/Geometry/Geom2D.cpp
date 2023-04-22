#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


void Circle::SetContainerFromPoints(const Vector<vec2>& pts) {
	ct.Clear();
	if (pts.IsEmpty()) {
		rad = 0;
		return;
	}
	for(const vec2& v : pts)
		ct += v;
	ct /= (float)pts.GetCount();
	
	rad = (ct - pts[0]).GetLengthSquared();
	for(const vec2* it = pts.Begin() + 1, *end = pts.End(); it != end; it++)
		rad = std::max(rad, (ct - *it).GetLengthSquared());
	rad = powf_fast(rad, 0.5f);
}

bool Circle::Contains(const vec2& pt) const {
	// Compare length of line from center to point to radius.
	// Less or equal than radius means that point is contained.
	// (Use squared value for faster calculation, because sqrt is slow)
	//		return line2{pt, pos}.GetLength() <= rad;
	line2 l {pt, ct};
	float len_sq = l.GetLengthSquared();
	float rad_sq = rad * rad;
	return len_sq <= rad_sq;
}

bool Circle::Intersects(const line2& l) const {
	float rad2 = rad * rad;
	vec2 ab = l.GetVector();
	vec2 ct_a = ct - l.a;
	vec2 ct_b = ct - l.b;
	
	if (ct_a.GetLengthSquared() <= rad2 || ct_b.GetLengthSquared() <= rad2)
		return true;
	
	// Get length of difference vector in line's space
	F t = Dot(ct_a, ab) / ab.GetLengthSquared();
	
	// If length/point is less than 0, then point is "behind" line
	// If length/point is more than 1, then it's "in front" of line
	if (t < (F)0 || t > (F)1)
		return false;
	
	// Get line from center of circle to closest point in line
	vec2 closest_pt = l.a + ab * t;
	line2 circle_to_closest {ct, closest_pt};
	
	// If length of line is less than radius, then line intersects.
	// (Use squared value for faster calculation, because sqrt is slow)
	// return circle_to_closest.GetLength() <= rad;
	float len_sq = circle_to_closest.GetLengthSquared();
	return len_sq <= rad2;
}

bool Circle::Intersects(const Circle& c) const {
	line2 l {ct, c.ct};
	F radii_sum = rad + c.rad;
	return l.GetLengthSquared() <= radii_sum * radii_sum;
}



void FixedRectangle::SetContainerFromPoints(const Vector<vec2>& pts) {
	pos.Clear();
	sz.Clear();
	if (pts.IsEmpty())
		return;
	
	const vec2* it = pts.Begin();
	vec2 min = *it;
	vec2 max = *it;
	it++;
	for(const vec2* end = pts.End(); it != end; it++) {
		for(int i = 0; i < 2; i++) {
			min[i] = std::min(min[i], (*it)[i]);
			max[i] = std::max(max[i], (*it)[i]);
		}
	}
	
	pos = min;
	sz = max - min;
}

bool FixedRectangle::Contains(const vec2& pt) const {
	vec2 min = GetMin(), max = GetMax();
	return	(pt[0] >= min[0] && pt[0] <= max[0]) &&
			(pt[1] >= min[1] && pt[1] <= max[1]);
}

bool FixedRectangle::Intersects(const line2& l) const {
	if (Contains(l.a) || Contains(l.b))
		return true;
	
	// Basic version
	if (1) {
		vec2 tl {pos[0], pos[1] + sz[1]};
		line2 left(pos, tl);
		if (left.Intersects(l)) return true;
		
		vec2 tr {pos[0] + sz[0], pos[1] + sz[1]};
		line2 top(tl, tr);
		if (top.Intersects(l)) return true;
		
		vec2 br {pos[0] + sz[0], pos[1]};
		line2 right(tr, br);
		if (right.Intersects(l)) return true;
		
		line2 bottom(br, pos);
		if (bottom.Intersects(l)) return true;
		
		return false;
	}
	// Raycast version
	else {
		// Get unit vector for line
		vec2 norm = l.GetVector().GetNormalized();
	
		// If unit vector is not in single axis, set the multiplicative inverse
		//norm = norm.GetCrossProduct(norm * -1);
		norm[0] = (norm[0] != 0) ? (F)1 / norm[0] : 0;
		norm[1] = (norm[1] != 0) ? (F)1 / norm[1] : 0;
		
		// Take vectors from line to corners of the rectangle, and
		// then transform them to line space.
		vec2 min = (GetMin() - l.a) * norm;
		vec2 max = (GetMax() - l.a) * norm;
	
		// TODO: explain
		F tmin = std::max(std::min(min[0], max[0]), std::min(min[1], max[1]));
		F tmax = std::min(std::max(min[0], max[0]), std::max(min[1], max[1]));
		if (tmax < 0 || tmin > tmax)
			return false;
	
		F t = (tmin < 0) ? tmax : tmin;
		return t > 0 && t * t < l.GetLengthSquared();
	}
}

bool FixedRectangle::Intersects(const Circle& c) const {
	vec2 min = GetMin();
	vec2 max = GetMax();
	vec2 closest_pt = c.ct;
	for(int i = 0; i < 2; i++) {
		closest_pt[i] = std::max(closest_pt[i], min[i]);
		closest_pt[i] = std::min(closest_pt[i], max[i]);
	}
	line2 l {c.ct, closest_pt};
	return l.GetLengthSquared() <= c.rad * c.rad;
}

bool FixedRectangle::Intersects(const FixedRectangle& r) const {
	vec2 min0 = GetMin();
	vec2 max0 = GetMax();
	vec2 min1 = r.GetMin();
	vec2 max1 = r.GetMax();
	bool overlap_x = ((min1[0] <= max0[0]) && (min0[0] <= max1[0]));
	bool overlap_y = ((min1[1] <= max0[1]) && (min0[1] <= max1[1]));
	return overlap_x && overlap_y;
}

ival1 FixedRectangle::GetInterval(const vec2& axis) const {
	ival1 res;
	vec2 min = GetMin();
	vec2 max = GetMax();
	vec2 verts[4] {
		min, vec2 {min[0], max[1]},
		max, vec2 {max[0], min[1]}
	};
	res.min = res.max = Dot(axis, verts[0]);
	for(int i = 1; i < 4; i++) {
		float proj = Dot(axis, verts[i]);
		res.min = Min(res.min, proj);
		res.max = Max(res.max, proj);
	}
	return res;
}

bool FixedRectangle::OverlapsOnAxis(const FixedRectangle& r, const vec2& axis) const {
	ival1 a = GetInterval(axis);
	ival1 b = r.GetInterval(axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool FixedRectangle::IntersectsSAT(const FixedRectangle& r) const {
	vec2 axisToTest[2] = { vec2{1, 0}, vec2{0, 1} };
	
	for(int i = 0; i < 2; i++)
		if (!OverlapsOnAxis(r, axisToTest[i]))
			return false;
	
	return true;
}





bool OrientedRectangle::Contains(const vec2& pt) const {
	vec2 local_pt = pt - ct; // move the point partially to the upcoming local space (without rotation)
	F theta = -rot; // "undo" the rotation
	F c = (F)FastCos(theta);
	F s = (F)FastSin(theta);
	mat2 zrot {	vec2 { c, s}, vec2 {-s, c} }; // rotation vector for local space
	local_pt = zrot * AsMatrix(local_pt); // move the point fully to local space (with rotation)
	FixedRectangle local_rc(hext * -1, hext * (F)2); // Create un-oriented rectangle in local (with [0,0] center)
	return local_rc.Contains(local_pt);
}

bool OrientedRectangle::Intersects(const line2& l) const {
	// Look previous OrientedRectangle::Contains for explanation
	
	line2 local_line;
	vec2 local_pt;
	F theta = (F)-rot;
	F c = (F)FastCos(theta);
	F s = (F)FastSin(theta);
	mat2 zrot {	vec2 { c, s}, vec2 {-s, c} };
	
	local_pt = l.a - ct;
	local_pt = zrot * AsMatrix(local_pt);
	local_line.a = local_pt + hext;
	
	local_pt = l.b - ct;
	local_pt = zrot * AsMatrix(local_pt);
	local_line.b = local_pt + hext;
	
	FixedRectangle local_rc(hext * (F)2);
	return local_rc.Intersects(local_line);
}

bool OrientedRectangle::Intersects(const Circle& c) const {
	// Transform circle to local space of oriented rectangle,
	// then check intersection for non-oriented rectangle.
	vec2 r = c.ct - ct;
	F theta = (F)-rot;
	F cos = FastCos(theta);
	F sin = FastSin(theta);
	mat2 zrot {	vec2 { cos, sin}, vec2 {-sin, cos} };
	r = zrot * AsMatrix(r);
	Circle lc(r + hext, c.rad);
	FixedRectangle lr(hext * (F)2);
	return lr.Intersects(lc);
}

ival1 OrientedRectangle::GetInterval(const vec2& axis) const {
	FixedRectangle r { ct - hext, hext * (F)2};
	vec2 min = r.GetMin();
	vec2 max = r.GetMax();
	vec2 verts[4] {
		min, max,
		vec2 {min[0], max[1]}, vec2 {max[0], min[1]}
	};
	F theta = +rot;
	F c = FastCos(theta), s = FastSin(theta);
	mat2 zrot {	vec2 { c, s}, vec2 {-s, c} };
	for(int i = 0; i < 4; i++) {
		vec2 d = verts[i] - ct;
		d = zrot * AsMatrix(d);
		verts[i] = d + ct;
	}
	ival1 res;
	res.min = res.max = Dot(axis, verts[0]);
	for(int i = 1; i < 4; i++) {
		F proj = Dot(axis, verts[i]);
		res.min = std::min(res.min, proj);
		res.max = std::max(res.max, proj);
	}
	return res;
}

bool OrientedRectangle::OverlapsOnAxis(const FixedRectangle& r, const vec2& axis) const {
	ival1 a = r.GetInterval(axis);
	ival1 b = GetInterval(axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OrientedRectangle::Intersects(const FixedRectangle& r) const {
	vec2 axis;
	vec2 test_axis[4] {
		vec2 { 1, 0 }, vec2 { 0, 1 },
		vec2(), vec2()
	};
	F theta = +rot;
	F cos = FastCos(theta), sin = FastSin(theta);
	mat2 zrot {	vec2 { cos, sin}, vec2 {-sin, cos} };
	
	axis = vec2{ hext[0], 0 }.Normalize();
	test_axis[2] = zrot * AsMatrix(axis);
	
	axis = vec2{ 0, hext[1] }.Normalize();
	test_axis[3] = zrot * AsMatrix(axis);
	
	for(int i = 0; i < 4; i++)
		if (!OverlapsOnAxis(r, test_axis[i]))
			return false;
	
	return true;
}

bool OrientedRectangle::Intersects(const OrientedRectangle& rect) const {
	FixedRectangle local0(hext * (F)2);
	vec2 r = rect.ct - ct;
	OrientedRectangle local1 = rect;
	local1.rot -= rot;
	F theta = -rot;
	F cos = FastCos(theta), sin = FastSin(theta);
	mat2 zrot {	vec2 { cos, sin}, vec2 {-sin, cos} };
	r = zrot * AsMatrix(r);
	local1.ct = r + hext;
	return local1.Intersects(local0);
}







void Shape2DWrapper::ShapeLine::Rotate(float rad) {
	vec2 ct = l.GetCenter();
	float c = FastCos(rad), s = FastSin(rad);
	mat2 zrot {	vec2 { c, s}, vec2 {-s, c} };
	l.a = vec2(zrot * AsMatrix(l.a - ct)) + ct;
	l.b = vec2(zrot * AsMatrix(l.b - ct)) + ct;
}

void Shape2DWrapper::ShapeLine::GetFaces(Vector<tri3>& faces) {
	vec2 v = l.GetVector();
	vec2 n = v.GetCrossProduct(v * -1);
	vec2 unit = n.GetNormalized() * 0.01f;
	vec3 bl = (l.a + unit).Extend();
	vec3 br = (l.a - unit).Extend();
	vec3 tl = (l.b + unit).Extend();
	vec3 tr = (l.b - unit).Extend();
	faces.Add().Set(bl, tl, tr);
	faces.Add().Set(tr, br, bl);
}






void Shape2DWrapper::ShapeCircle::GetFaces(Vector<line2>& faces) {
	int steps = 36;
	float angle_step = M_2PIf / (float)(steps - 1);
	vec2 a, b;
	float angle = 0;
	a[0] = c.ct[0] + c.rad;
	a[1] = c.ct[1] + 0;
	for(int i = 0; i < steps; i++) {
		angle += angle_step;
		b[0] = c.ct[0] + c.rad * FastCos(angle);
		b[1] = c.ct[1] + c.rad * FastSin(angle);
		faces.Add(line2(a, b));
		Swap(a, b);
	}
}

void Shape2DWrapper::ShapeCircle::GetFaces(Vector<tri3>& faces) {
	int steps = 36;
	float angle_step = M_2PIf / (float)(steps - 1);
	vec3 a, b, ct;
	float angle = 0;
	a = ct = c.ct.Extend();
	a[0] += c.rad;
	b[2] = 0;
	for(int i = 0; i < steps; i++) {
		angle += angle_step;
		b[0] = c.ct[0] + c.rad * FastCos(angle);
		b[1] = c.ct[1] + c.rad * FastSin(angle);
		faces.Add().Set(ct, a, b);
		Swap(a, b);
	}
}







void Shape2DWrapper::ShapeRect::GetFaces(Vector<line2>& faces) {
	vec2 a = r.pos, b, c = r.pos + r.sz, d;
	b[0] = r.pos[0] + r.sz[0];
	b[1] = r.pos[1];
	d[0] = r.pos[0];
	d[1] = r.pos[1] + r.sz[1];
	faces.Add().Set(a, b);
	faces.Add().Set(b, c);
	faces.Add().Set(c, d);
	faces.Add().Set(d, a);
}
void Shape2DWrapper::ShapeRect::GetFaces(Vector<tri3>& faces) {
	vec3 a = r.pos.Extend(), b, c = (r.pos + r.sz).Extend(), d;
	b[0] = r.pos[0] + r.sz[0];
	b[1] = r.pos[1];
	b[2] = 0;
	d[0] = r.pos[0];
	d[1] = r.pos[1] + r.sz[1];
	d[2] = 0;
	faces.Add().Set(a, b, c);
	faces.Add().Set(c, d, a);
}






void Shape2DWrapper::ShapeOrientedRect::GetFaces(Vector<line2>& faces) {
	float theta = o.rot;
	float cos = FastCos(theta), sin = FastSin(theta);
	mat2 zrot {	vec2 { cos, sin}, vec2 {-sin, cos} };
	vec2 a, b, c, d;
	a[0] = -o.hext[0]; a[1] = -o.hext[1];
	b[0] = -o.hext[0]; b[1] = +o.hext[1];
	c[0] = +o.hext[0]; c[1] = +o.hext[1];
	d[0] = +o.hext[0]; d[1] = -o.hext[1];
	a = vec2(zrot * AsMatrix(a)) + o.ct;
	b = vec2(zrot * AsMatrix(b)) + o.ct;
	c = vec2(zrot * AsMatrix(c)) + o.ct;
	d = vec2(zrot * AsMatrix(d)) + o.ct;
	faces.Add().Set(a, b);
	faces.Add().Set(b, c);
	faces.Add().Set(c, d);
	faces.Add().Set(d, a);
}

void Shape2DWrapper::ShapeOrientedRect::GetFaces(Vector<tri3>& faces) {
	float theta = o.rot;
	float cos = FastCos(theta), sin = FastSin(theta);
	mat2 zrot {	vec2 { cos, sin}, vec2 {-sin, cos} };
	vec2 a, b, c, d;
	a[0] = -o.hext[0]; a[1] = -o.hext[1];
	b[0] = -o.hext[0]; b[1] = +o.hext[1];
	c[0] = +o.hext[0]; c[1] = +o.hext[1];
	d[0] = +o.hext[0]; d[1] = -o.hext[1];
	a = vec2(zrot * AsMatrix(a)) + o.ct;
	b = vec2(zrot * AsMatrix(b)) + o.ct;
	c = vec2(zrot * AsMatrix(c)) + o.ct;
	d = vec2(zrot * AsMatrix(d)) + o.ct;
	vec3 A = a.Extend();
	vec3 B = b.Extend();
	vec3 C = c.Extend();
	vec3 D = d.Extend();
	faces.Add().Set(A, B, C);
	faces.Add().Set(C, D, A);
}




void Shape2DWrapper::Create(ShapeId type, vec2 a, vec2 b, float f) {
	shape.Clear();
	switch (type) {
		case SHAPE2_LINE:		shape = new ShapeLine( line2(a, b)); break;
		case SHAPE2_CIRCLE:		shape = new ShapeCircle( Circle(a, f)); break;
		case SHAPE2_RECT:		shape = new ShapeRect( FixedRectangle(a, b)); break;
		case SHAPE2_ORIENTRECT:	shape = new ShapeOrientedRect( OrientedRectangle(a, b, f) ); break;
		default: LOG("error: unimplemented shape id" << (int)type);
	}
}

void Shape2DWrapper::Create(ShapeId type, const vec2& ax_vec) {
	if (type == SHAPE2_LINE) {
		vec2 b = ax_vec * 0.5;
		vec2 a = b * -1;
		Create(type, a, b, 0);
	}
	else if (type == SHAPE2_CIRCLE) {
		vec2 pos(0,0);
		float len = ax_vec.GetLength();
		Create(type, pos, vec2(), len);
	}
	else if (type == SHAPE2_RECT) {
		vec2 sz = ax_vec.GetAbsolute();
		vec2 pos = sz * -0.5;
		Create(type, pos, sz, 0);
	}
	else if (type == SHAPE2_ORIENTRECT) {
		vec2 sz = ax_vec.GetAbsolute();
		vec2 pos = sz * -0.5;
		Create(type, pos, sz, 0);
	}
	else {
		LOG("error: unimplemented shape id" << (int)type);
	}
}

bool Shape2DWrapper::ShapeBase::Intersects(const ShapeBase& b) {
	const ShapeLine* l = CastConstPtr<ShapeLine>(&b);
	if (l) return Intersects(l->l);
	
	const ShapeCircle* c = CastConstPtr<ShapeCircle>(&b);
	if (c) return Intersects(c->c);
	
	const ShapeRect* r = CastConstPtr<ShapeRect>(&b);
	if (r) return Intersects(r->r);
	
	const ShapeOrientedRect* o = CastConstPtr<ShapeOrientedRect>(&b);
	if (o) return Intersects(o->o);
	
	return false;
}










bool BoundingShape::Intersects(const line2& l0) const {
	for(const auto& l : lines)
		if (l.Intersects(l0))
			return true;
	for(const auto& c : circles)
		if (c.Intersects(l0))
			return true;
	for(const auto& r : rects)
		if (r.Intersects(l0))
			return true;
	for(const auto& o : orects)
		if (o.Intersects(l0))
			return true;
	return false;
}

bool BoundingShape::Intersects(const Circle& c0) const {
	for(const auto& l : lines)
		if (c0.Intersects(l))
			return true;
	for(const auto& c : circles)
		if (c.Intersects(c0))
			return true;
	for(const auto& r : rects)
		if (r.Intersects(c0))
			return true;
	for(const auto& o : orects)
		if (o.Intersects(c0))
			return true;
	return false;
}

bool BoundingShape::Intersects(const FixedRectangle& r0) const {
	for(const auto& l : lines)
		if (r0.Intersects(l))
			return true;
	for(const auto& c : circles)
		if (r0.Intersects(c))
			return true;
	for(const auto& r : rects)
		if (r.Intersects(r0))
			return true;
	for(const auto& o : orects)
		if (o.Intersects(r0))
			return true;
	return false;
}

bool BoundingShape::Intersects(const OrientedRectangle& o0) const {
	for(const auto& l : lines)
		if (o0.Intersects(l))
			return true;
	for(const auto& c : circles)
		if (o0.Intersects(c))
			return true;
	for(const auto& r : rects)
		if (o0.Intersects(r))
			return true;
	for(const auto& o : orects)
		if (o.Intersects(o0))
			return true;
	return false;
}

















vec2 Intersect(const vec2& a, const vec2& b, const vec2& c, const vec2& d) {
	double a1 = b[1] - a[1];
	double b1 = a[0] - b[0];
	double c1 = a1*(a[0]) + b1*(a[1]);
	
	double a2 = d[1] - c[1];
	double b2 = c[0] - d[0];
	double c2 = a2*(c[0])+ b2*(c[1]);
	
	double determinant = a1*b2 - a2*b1;
	
	if (determinant == 0) {
		return (a + b + c + d) / 4;
	}
	else {
		float x = (float)((b2*c1 - b1*c2)/determinant);
		float y = (float)((a1*c2 - a2*c1)/determinant);
		return vec2(x, y);
	}
}

double Triangulate::Area(const Vector<vec2> &contour) {
	int n = contour.GetCount();
	
	double A=0.0f;
	
	for (int p=n-1,q=0; q<n; p=q++) {
		A+= contour[p][0]*contour[q][1] - contour[q][0]*contour[p][1];
	}
	
	return A*0.5f;
}

/*
  InsideTriangle decides if a point P is Inside of the triangle
  defined by A, B, C.
*/
bool Triangulate::InsideTriangle(double Ax, double Ay,
		double Bx, double By,
		double Cx, double Cy,
		double Px, double Py)
        
{
	double ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
	double cCROSSap, bCROSScp, aCROSSbp;
	
	ax = Cx - Bx;
	ay = Cy - By;
	bx = Ax - Cx;
	by = Ay - Cy;
	cx = Bx - Ax;
	cy = By - Ay;
	apx= Px - Ax;
	apy= Py - Ay;
	bpx= Px - Bx;
	bpy= Py - By;
	cpx= Px - Cx;
	cpy= Py - Cy;
	
	aCROSSbp = ax*bpy - ay*bpx;
	cCROSSap = cx*apy - cy*apx;
	bCROSScp = bx*cpy - by*cpx;
	
	return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
};

bool Triangulate::Snip(const Vector<vec2> &contour,int u,int v,int w,int n,int *V) {
	int p;
	double Ax, Ay, Bx, By, Cx, Cy, Px, Py;
	
	Ax = contour[V[u]][0];
	Ay = contour[V[u]][1];
	
	Bx = contour[V[v]][0];
	By = contour[V[v]][1];
	
	Cx = contour[V[w]][0];
	Cy = contour[V[w]][1];
	
	if (EPSILON > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))))
		return false;
		
	for (p=0;p<n;p++) {
		if ((p == u) || (p == v) || (p == w))
			continue;
			
		Px = contour[V[p]][0];
		
		Py = contour[V[p]][1];
		
		if (InsideTriangle(Ax,Ay,Bx,By,Cx,Cy,Px,Py))
			return false;
	}
	
	return true;
}

bool Triangulate::Process(const Vector<vec2> &contour, Vector<float> &result) {
	/* allocate and initialize list of Vertices in polygon */
	result.SetCount(0);
	
	int n = contour.GetCount();
	
	if (n < 3)
		return false;
		
	Vector<int> V;
	V.SetCount(n);
	
	/* we want a counter-clockwise polygon in V */
	
	if (0.0f < Area(contour))
		for (int v=0; v<n; v++)
			V[v] = v;
	else
		for (int v=0; v<n; v++)
			V[v] = (n-1)-v;
			
	int nv = n;
	
	/*  remove nv-2 Vertices, creating 1 triangle every time */
	int count = 2*nv;   /* error detection */
	
	for (int m=0, v=nv-1; nv>2;) {
		/* if we loop, it is probably a non-simple polygon */
		if (0 >= (count--)) {
			//** Triangulate: ERROR - probable bad polygon!
			return false;
		}
		
		/* three consecutive vertices in current polygon, <u,v,w> */
		int u = v  ;
		
		if (nv <= u)
			u = 0;     /* previous */
			
		v = u+1;
		
		if (nv <= v)
			v = 0;     /* new v    */
			
		int w = v+1;
		
		if (nv <= w)
			w = 0;     /* next     */
			
		if (Snip(contour,u,v,w,nv,V.Begin())) {
			int a,b,c,s,t;
			
			/* true names of the vertices */
			a = V[u];
			b = V[v];
			c = V[w];
			
			/* output Triangle */
			#if 0
			tri2& tri = result.Add();
			tri.a = contour[a];
			tri.b = contour[b];
			tri.c = contour[c];
			#else
			const auto& aa = contour[a];
			const auto& bb = contour[b];
			const auto& cc = contour[c];
			result.Add(aa[0]);
			result.Add(aa[1]);
			result.Add(bb[0]);
			result.Add(bb[1]);
			result.Add(cc[0]);
			result.Add(cc[1]);
			#endif
			
			m++;
			
			/* remove v from remaining polygon */
			
			for (s=v,t=v+1;t<nv;s++,t++)
				V[s] = V[t];
				
			nv--;
			
			/* resest error detection counter */
			count = 2*nv;
		}
	}
	
	
	
	return true;
}


NAMESPACE_TOPSIDE_END

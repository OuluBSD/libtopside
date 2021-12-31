#ifndef _SoftPhys_Geometry2D_
#define _SoftPhys_Geometry2D_


NAMESPACE_SOFTPHYS_BEGIN



float Length(const line2& line);
float LengthSq(const line2& line);
vec2 GetMin(const Rectangle& rect);
vec2 GetMax(const Rectangle& rect);
Rectangle FromMinMax(const vec2& min, const vec2& max);

bool PointOnLine(const vec2& point, const line2& line);
bool PointInCircle(const vec2& point, const Circle& circle);
bool PointInRectangle(const vec2& point, const Rectangle& rectangle);
bool PointInOrientedRectangle(const vec2& point, const OrientedRectangle& rectangle);

#define PointCircle(point, circle) \
	PointInCircle(point, circle)
#define CirclePoint(circle, point) \
	PointInCircle(point, circle)
#define PointRectangle(point, rect) \
	PointInRectangle(point, rect)
#define RectanglePoint(rect, point) \
	PointInRectangle(point, rect)
#define PointOrientedRectangle(point, rect) \
	PointInOrientedRectangle(point, rect)
#define OrientedRectanglePoint(rect, point) \
	PointInOrientedRectangle(point, rect)

bool LineCircle(const line2& line, const Circle& circle);
bool LineRectangle(const line2& line, const Rectangle& rectangle);
bool LineOrientedRectangle(const line2& line, const OrientedRectangle& rectangle);

#define PointLine(point, line) PointOnLine(point, line)
#define LinePoint(line, point) PointOnLine(point, line)
#define CircleLine(circle, line) LineCircle(line, circle)
#define RectangleLine(rectangle, line) \
	LineRectangle(line, rectangle);
#define OrientedRectangleLine(rectangle, line) \
	LineOrientedRectangle(line, rectangle);

Stream& operator<<(Stream& os, const line2& shape);
Stream& operator<<(Stream& os, const Circle& shape);
Stream& operator<<(Stream& os, const Rectangle& shape);
Stream& operator<<(Stream& os, const OrientedRectangle& shape);

bool CircleCircle(const Circle& circle1, const Circle& circle2);
bool CircleRectangle(const Circle& circle, const Rectangle& rect);
#define RectangleCircle(rectangle, circle) \
	CircleRectangle(circle, rectangle)
bool CircleOrientedRectangle(const Circle& circle, const OrientedRectangle& rect);
#define OrientedRectangleCircle(rectangle, circle) \
	CircleOrientedRectangle(circle, rectangle)
bool RectangleRectangle(const Rectangle& rect1, const Rectangle& rect2);

Interval GetInterval(const Rectangle& rect, const vec2& axis);
bool OverlapOnAxis(const Rectangle& rect1, const Rectangle& rect2, const vec2& axis);
bool RectangleRectangleSAT(const Rectangle& rect1, const Rectangle& rect2);

Interval GetInterval(const OrientedRectangle& rect, const vec2& axis);
bool OverlapOnAxis(const Rectangle& rect1, const OrientedRectangle& rect2, const vec2& axis);
bool RectangleOrientedRectangle(const Rectangle& rect1, const OrientedRectangle& rect2);
#define OrientedRectangleRectangle(oriented, regular) \
	RectangleOrientedRectangle(regular, oriented)

bool OverlapOnAxis(const OrientedRectangle& rect1, const OrientedRectangle& rect2, const vec2& axis);
bool OrientedRectangleOrientedRectangleSAT(const OrientedRectangle& rect1, const OrientedRectangle& rect2);
bool OrientedRectangleOrientedRectangle(const OrientedRectangle& rect1, const OrientedRectangle& rect2);

Circle ContainingCircle(vec2* pointArray, int arrayCount);
Circle ContainingCircleAlt(vec2* pointArray, int arrayCount);
Rectangle ContainingRectangle(vec2* pointArray, int arrayCount);


bool PointInShape(const BoundingShape& shape, const vec2& point);
bool LineShape(const line2& line, const BoundingShape& shape);
bool CircleShape(const Circle& circle, const BoundingShape& shape);
bool RectangleShape(const Rectangle& rectangle, const BoundingShape& shape);
bool OrientedRectangleShape(const OrientedRectangle& rect, const BoundingShape& shape);

#define ShapeLine(shape, line) \
	LineShape(line, shape)
#define ShapeCircle(shape, circle) \
	CircleShape(circle, shape)
#define ShapeRectangle(shape, rectangle) \
	RectangleShape(rectangle, shape)
#define ShapeOrientedRectangle(shape, rect) \
	OrientedRectangleShape(rect, shape)


NAMESPACE_SOFTPHYS_END

#endif

#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


#define CLAMP(number, minimum, maximum) \
	number = (number < minimum) ? minimum : \
		((number > maximum) ? maximum : number)

#define OVERLAP(minA, minB, maxA, maxB) \
	((minB <= maxA) && (minA <= maxB))



float Length(const line2& line) {
	return Magnitude(line.end - line.start);
}

float LengthSq(const line2& line) {
	return MagnitudeSq(line.end - line.start);
}

vec2 GetMin(const FixedRectangle& rect) {
	vec2 p1 = rect.origin;
	vec2 p2 = rect.origin + rect.size;

	return vec2(fminf(p1[0], p2[0]), fminf(p1[1], p2[1]));
}

vec2 GetMax(const FixedRectangle& rect) {
	vec2 p1 = rect.origin;
	vec2 p2 = rect.origin + rect.size;

	return vec2(fmaxf(p1[0], p2[0]), fmaxf(p1[1], p2[1]));
}

FixedRectangle FromMinMax(const vec2& min, const vec2& max) {
	return FixedRectangle(min, max - min);
}

bool PointOnLine(const vec2& point, const line2& line) {
	// Find the slope
	float M = (line.end[1] - line.start[1]) / (line.end[0] - line.start[0]);
	// Find the Y-Intercept
	float B = line.start[1] - M * line.start[0];
	// Check line equation
	return CMP(point[1], M * point[0] + B);
}

bool PointInCircle(const vec2& point, const Circle& circle) {
	line2 line(point, circle.position);
	if (LengthSq(line) < circle.radius * circle.radius) {
		return true;
	}
	return false;
}

bool PointInRectangle(const vec2& point, const FixedRectangle& rectangle) {
	vec2 min = GetMin(rectangle);
	vec2 max = GetMax(rectangle);

	return	min[0] <= point[0] && min[1] <= point[1] &&
			point[0] <= max[0] && point[1] <= max[1];
}

bool PointInOrientedRectangle(const vec2& point, const OrientedRectangle& rectangle) {
	FixedRectangle localRectangle(vec2(), rectangle.halfExtents * 2.0f);

	// First, we get a vector from the center of the rectangle
	// pointing to the point we want to test!
	vec2 rotVector = point - rectangle.position;

	// Second, we rotate that vector by the inverse of the rectangles
	// rotation (On the Z axis in 3D). We can either invert a matrix,
	// or construct a matrix from the negative rotation angle
	float theta = -DEG2RADf(rectangle.rotation);
	
	// Construct matrix
	mat2 zRotation2x2 {
		cosf(theta), sinf(theta),
		-sinf(theta), cosf(theta) };
	
	// Rotate vector
	Multiply(rotVector, vec2(rotVector[0], rotVector[1]), zRotation2x2);

	// Now, the rotVector is in the local space of the world oriented rectangle.
	// But remember, it's a vector, not a point. Assume the rectangle is at 0,0
	// this means the center of the rotated rectangle is at 0,0. And rotVector points
	// to a point inside of this oriented box

	// Remember, the regular Rectangle class has 0,0 at bottom left! So, when we 
	// constructed the local space version of the oriented rectangle, we essentially
	// made an oriented rectangle with no orientation that was offset by half it's
	// size, so that bottom left is at origin. We have to apply this same offset
	// to the vector being rotated

	// Third we offset the point pointed to by the local roation vector by
	// half of the oriented bounding boxes extents. We do this because the
	// non oriented bounding box has its origin at bottom left, while the
	// oriented bounding box has its origin at center
	vec2 localPoint = rotVector + rectangle.halfExtents;

	// Finally, perform the local space point rectangle test!
	return PointInRectangle(localPoint, localRectangle);

	/* Alternate second step, Verbose
	vec3 pointToRotate(localPoint[0], localPoint[1], 0.0f);
	mat3 rotation = ZRotation3x3(-rectangle.rotation);
	vec3 result = MultiplyVector(pointToRotate, rotation);
	localPoint = vec2(result[0], result[1]);*/

	// Alternate second step, With extras
	//localPoint = RotateVector(localPoint, -rectangle.rotation);
}

Stream& operator<<(Stream& os, const line2& shape) {
	os << "start: (" << shape.start[0] << ", " << shape.start[1] << "), end: (" << shape.end[0] << ", " << shape.end[1] << ")";
	return os;
}

Stream& operator<<(Stream& os, const Circle& shape) {
	os << "position: (" << shape.position[0] << ", " << shape.position[1] << "), radius: " << shape.radius;
	return os;
}
Stream& operator<<(Stream& os, const FixedRectangle& shape) {
	vec2 min = GetMin(shape);
	vec2 max = GetMax(shape);

	os << "min: (" << min[0] << ", " << min[1] << "), max: (" << max[0] << ", " << max[1] << ")";
	return os;
}
Stream& operator<<(Stream& os, const OrientedRectangle& shape) {
	os << "position: (" << shape.position[0] << ", " << shape.position[1] << "), half size: (";
	os << shape.halfExtents[0] << ", " << shape.halfExtents[1] << "), rotation: " << shape.rotation;
	return os;
}

bool LineCircle(const line2& line, const Circle& circle) {
	// Turn line into vector
	vec2 ab = line.end - line.start;

	// Project point (circle position) onto ab (line segment), computing the 
	// paramaterized position d(t) = a + t * (b - a)
	float t = Dot(circle.position - line.start, ab) / Dot(ab, ab);

	// Clamp T to a 0-1 range. If t was < 0 or > 1
	// then the closest point was outside the segment!
	if (t < 0.0f || t > 1.0f) {
		return false;
	}
	// We do not need to clamp t
	//t = (t < 0.0f) ? 0.0f : ((t > 1.0f)? 1.0f : t);

	// Find the closest point on the line segment
	vec2 closestPoint = line.start + ab * t;

	line2 circleToClosest(circle.position, closestPoint);
	return LengthSq(circleToClosest) < circle.radius * circle.radius;
}

#if 1
bool LineRectangle(const line2& line, const FixedRectangle& rect) {
	if (PointInRectangle(line.start, rect) || PointInRectangle(line.end, rect)) {
		return true;
	}
	
	vec2 norm = (line.end - line.start).GetNormalized();
	norm[0] = (norm[0] != 0) ? 1.0f / norm[0] : 0;
	norm[1] = (norm[1] != 0) ? 1.0f / norm[1] : 0;
	vec2 min = (GetMin(rect) - line.start) * norm;
	vec2 max = (GetMax(rect) - line.start) * norm;

	float tmin = fmaxf(fminf(min[0], max[0]), fminf(min[1], max[1]));
	float tmax = fminf(fmaxf(min[0], max[0]), fmaxf(min[1], max[1]));
	if (tmax < 0 || tmin > tmax) {
		return false;
	}
	float t = (tmin < 0.0f) ? tmax : tmin;
	return t > 0.0f && t * t < LengthSq(line);
}
#else // Same code, just a bit easyer to read!
bool LineRectangle(const line2& line, const FixedRectangle& rect) {
	// If either point of the line is in the rectangle, we have collision!
	if (PointInRectangle(line.start, rect) || PointInRectangle(line.end, rect)) {
		return true;
	}

	// Now we do a raycast
	vec2 min = GetMin(rect);
	vec2 max = GetMax(rect);
	vec2 norm = Normalized(line.end - line.start);

	float t1 = (min[0] - line.start[0]) / norm[0];
	float t2 = (max[0] - line.start[0]) / norm[0];
	float t3 = (min[1] - line.start[1]) / norm[1];
	float t4 = (max[1] - line.start[1]) / norm[1];

	float tmin = fmaxf(fminf(t1, t2), fminf(t3, t4));
	float tmax = fminf(fmaxf(t1, t2), fmaxf(t3, t4));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	// So the line segment is not intersecting
	if (tmax < 0) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return false;
	}

	float t = tmin;

	if (tmin < 0.0f) {
		// Intersection point is:
		// line.start + norm * tmax
		t = tmax;
	}

	// Intersection point is:
	// line.start + norm * tmin
	return t > 0.0f && t * t < LengthSq(line);

	

	/* This tests a line (not segment) against a Rectangle

	// First get the corners of the box
	vec2 c[] = { // corners
		rect.origin,
		rect.origin + rect.size,
		vec2(rect.origin[0] + rect.size[0], rect.origin[1]),
		vec2(rect.origin[0], rect.origin[1] + rect.size[1])
	};

	// These variables are just to keep the determinant caluclations readable
	float xDelta = line.end[0] - line.start[0];
	float yDelta = line.end[1] - line.start[1];
	float sx = line.start[0];
	float sy = line.start[1];

	// Find the determinant of
	// | x2 - x1 |  x3 - x1 |
	// | y2 - y1 |  y3 - y1 |
	// for every corner. The result of the determinant for that matrix
	// will be positive if the point is on one side, negative if its
	// on the other side and 0 if the point is on the line.
	float d1 = (c[0][0] - sx) * (yDelta) - (c[0][1] - sy) * (xDelta);
	float d2 = (c[1][0] - sx) * (yDelta) - (c[1][1] - sy) * (xDelta);
	float d3 = (c[2][0] - sx) * (yDelta) - (c[2][1] - sy) * (xDelta);
	float d4 = (c[3][0] - sx) * (yDelta) - (c[3][1] - sy) * (xDelta);

	// If all points are on the same side of the line, we have a collision
	// We take advantage of the fact that multiplying two positive numbers
	// is always positive and multiplying two negative numbers is always
	// negative. The only way multiplying two determinant results is negative
	// is if two of the numbers where on the same side.
	return (!d1 * d2 <= 0 || d2 * d3 <= 0 || d3 * d4 <= 0); */
}
#endif

bool LineOrientedRectangle(const line2& line, const OrientedRectangle& rectangle) {
	float theta = -DEG2RADf(rectangle.rotation);
	mat2 zRotation2x2 {
		cosf(theta), sinf(theta),
		-sinf(theta), cosf(theta) };
	line2 localLine;

	vec2 rotVector = line.start - rectangle.position;
	Multiply(rotVector, vec2(rotVector[0], rotVector[1]), zRotation2x2);
	localLine.start  = rotVector + rectangle.halfExtents;
	
	rotVector = line.end - rectangle.position;
	Multiply(rotVector, vec2(rotVector[0], rotVector[1]), zRotation2x2);
	localLine.end = rotVector + rectangle.halfExtents;
	
	FixedRectangle localRectangle(vec2(), rectangle.halfExtents * 2.0f);
	return LineRectangle(localLine, localRectangle);
}

bool CircleCircle(const Circle& circle1, const Circle& circle2) {
	line2 line(circle1.position, circle2.position);
	float radiiSum = circle1.radius + circle2.radius;
	return LengthSq(line) <= radiiSum * radiiSum;
}

bool CircleRectangle(const Circle& circle, const FixedRectangle& rect) {
	vec2 closestPoint = circle.position;
	vec2 min = GetMin(rect);
	vec2 max = GetMax(rect);
	closestPoint[0] = (closestPoint[0] < min[0]) ? min[0] :
		(closestPoint[0] > max[0]) ? max[0] : closestPoint[0];
	closestPoint[1] = (closestPoint[1] < min[1]) ? min[1] :
		(closestPoint[1] > max[1]) ? max[1] : closestPoint[1];

	line2 line(circle.position, closestPoint);
	return LengthSq(line) <= circle.radius * circle.radius;
}

bool CircleOrientedRectangle(const Circle& circle, const OrientedRectangle& rect) {
	vec2 rotVector = circle.position - rect.position;
	float theta = -DEG2RADf(rect.rotation);
	mat2 zRotation2x2 {
		cosf(theta), sinf(theta),
		-sinf(theta), cosf(theta) };
	Multiply(rotVector, vec2(rotVector[0], rotVector[1]), zRotation2x2);
	
	Circle localCircle(rotVector + rect.halfExtents, circle.radius);
	FixedRectangle localRectangle(vec2(), rect.halfExtents * 2.0f);

	return CircleRectangle(localCircle, localRectangle);
}

bool RectangleRectangle(const FixedRectangle& rect1, const FixedRectangle& rect2) {
	vec2 aMin = GetMin(rect1);
	vec2 aMax = GetMax(rect1);
	vec2 bMin = GetMin(rect2);
	vec2 bMax = GetMax(rect2);

	bool xOverlap = ((bMin[0] <= aMax[0]) && (aMin[0] <= bMax[0]));
	bool yOverlap = ((bMin[1] <= aMax[1]) && (aMin[1] <= bMax[1]));

	return xOverlap && yOverlap;
}

Interval GetInterval(const FixedRectangle& rect, const vec2& axis) {
	vec2 min = GetMin(rect);
	vec2 max = GetMax(rect);

	vec2 verts[] = { // Get all vertices of rect
		vec2(min[0], min[1]),
		vec2(min[0], max[1]),
		vec2(max[0], max[1]),
		vec2(max[0], min[1])
	};

	// Set interval first projected vertex
	Interval result;
	result.min = Dot(axis, verts[0]);
	result.max = result.min;

	// For all other verts
	for (int i = 1; i < 4; ++i) {
		// Project vertex
		float projection = Dot(axis, verts[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}

	return result;
}

bool OverlapOnAxis(const FixedRectangle& rect1, const FixedRectangle& rect2, const vec2& axis) {
	Interval a = GetInterval(rect1, axis);
	Interval b = GetInterval(rect2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool RectangleRectangleSAT(const FixedRectangle& rect1, const FixedRectangle& rect2) {
	vec2 axisToTest[] = {
		vec2(1, 0),
		vec2(0, 1)
	};

	for (int i = 0; i < 2; ++i) {
		if (!OverlapOnAxis(rect1, rect2, axisToTest[i])) {
			// Intervals don't overlap, seperating axis found
			return false; // No collision has taken place
		}
	}

	// All intervals overlapped, seperating axis not found
	return true; // We have a collision
}

Interval GetInterval(const OrientedRectangle& rect, const vec2& axis) {
	FixedRectangle nonOrientedRect = FixedRectangle(vec2(rect.position - rect.halfExtents), rect.halfExtents * 2.0f);
	vec2 min = GetMin(nonOrientedRect); 
	vec2 max = GetMax(nonOrientedRect);
	vec2 verts[] = { min, max, vec2(min[0], max[1]), vec2(max[0], min[1]) };

	float theta = DEG2RADf(rect.rotation);
	mat2 zRotation2x2 {
		cosf(theta), sinf(theta),
		-sinf(theta), cosf(theta) };

	for (int i = 0; i < 4; ++i) {
		vec2 rotVector = verts[i] - rect.position;
		Multiply(rotVector, vec2(rotVector[0], rotVector[1]), zRotation2x2);
		verts[i] = rotVector + rect.position;
	}

	// Set interval first projected vertex
	Interval result;
	result.min = result.max = Dot(axis, verts[0]);

	// For all other verts
	for (int i = 1; i < 4; ++i) {
		// Project vertex
		float projection = Dot(axis, verts[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}

	return result;
}


bool OverlapOnAxis(const FixedRectangle& rect1, const OrientedRectangle& rect2, const vec2& axis) {
	Interval a = GetInterval(rect1, axis);
	Interval b = GetInterval(rect2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool RectangleOrientedRectangle(const FixedRectangle& rect1, const OrientedRectangle& rect2) {
	vec2 axisToTest[]{
		vec2(1, 0),
		vec2(0, 1),
		vec2(rect2.halfExtents[0], 0).GetNormalized(),
		vec2(0, rect2.halfExtents[1]).GetNormalized()
	};

	float theta = DEG2RADf(rect2.rotation);
	mat2 zRotation2x2 {
		cosf(theta), sinf(theta),
		-sinf(theta), cosf(theta) };
	Multiply(axisToTest[2], vec2(rect2.halfExtents[0], 0).GetNormalized(), zRotation2x2);
	Multiply(axisToTest[3], vec2(0, rect2.halfExtents[1]).GetNormalized(), zRotation2x2);

	for (int i = 0; i < 4; ++i) {
		if (!OverlapOnAxis(rect1, rect2, axisToTest[i])) {
			// Intervals don't overlap, seperating axis found
			return false; // No collision has taken place
		}
	}

	// All intervals overlapped, seperating axis not found
	return true; // We have a collision
}

bool OverlapOnAxis(const OrientedRectangle& rect1, const OrientedRectangle& rect2, const vec2& axis) {
	Interval a = GetInterval(rect1, axis);
	Interval b = GetInterval(rect2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OrientedRectangleOrientedRectangleSAT(const OrientedRectangle& rect1, const OrientedRectangle& rect2) {
	vec2 axisToTest[]{
		vec2(1, 0),
		vec2(0, 1),
		vec2(), // TEMP
		vec2(), // TEMP
		vec2(), // TEMP
		vec2() // TEMP
	};

	// Collision axis of rect 2
	float theta = DEG2RADf(rect2.rotation);
	mat2 zRotation2x2 {
		cosf(theta), sinf(theta),
		-sinf(theta), cosf(theta) };
	Multiply(axisToTest[2], vec2(rect2.halfExtents[0], 0).GetNormalized(), zRotation2x2);
	Multiply(axisToTest[3], vec2(0, rect2.halfExtents[1]).GetNormalized(), zRotation2x2);

	// Collision axis of rect 1
	theta = DEG2RADf(rect1.rotation);
	zRotation2x2[0] = cosf(theta);
	zRotation2x2[1] = sinf(theta);
	zRotation2x2[2] = -sinf(theta);
	zRotation2x2[3] = cosf(theta);
	Multiply(axisToTest[4], vec2(rect1.halfExtents[0], 0).GetNormalized(), zRotation2x2);
	Multiply(axisToTest[5], vec2(0, rect1.halfExtents[1]).GetNormalized(), zRotation2x2);

	for (int i = 0; i < 6; ++i) {
		if (!OverlapOnAxis(rect1, rect2, axisToTest[i])) {
			// Intervals don't overlap, seperating axis found
			return false; // No collision has taken place
		}
	}

	// All intervals overlapped, seperating axis not found
	return true; // We have a collision
}

bool OrientedRectangleOrientedRectangle(const OrientedRectangle& r1, const OrientedRectangle& r2) {
	//return OrientedRectangleOrientedRectangleSAT(rect1, rect2);
	FixedRectangle localRect1(vec2(), r1.halfExtents * 2.0f);
	OrientedRectangle localRect2(r2.position, r2.halfExtents, r2.rotation);

	localRect2.rotation = r2.rotation - r1.rotation;
	vec2 rotVector = r2.position - r1.position;
	float theta = -DEG2RADf(r1.rotation);
	mat2 zRotation2x2 {
		cosf(theta), sinf(theta),
		-sinf(theta), cosf(theta) };
	Multiply(rotVector, vec2(rotVector[0], rotVector[1]), zRotation2x2);
	localRect2.position = rotVector + r1.halfExtents;

	return RectangleOrientedRectangle(localRect1, localRect2);
}

Circle ContainingCircle(vec2* pointArray, int arrayCount) {
	vec2 center; 
	for (int i = 0; i < arrayCount; ++i) {
		center = center + pointArray[i];
	}
	center = center * (1.0f / (float)arrayCount);

	Circle result(center, 1.0f);

	// Find the squared radius
	result.radius = MagnitudeSq(center - pointArray[0]);
	for (int i = 1; i < arrayCount; ++i) {
		float distance = MagnitudeSq(center - pointArray[i]);
		if (distance > result.radius) {
			result.radius = distance;
		}
	}

	// This has been squared until now
	result.radius = sqrtf(result.radius);
	return result;
}

Circle ContainingCircleAlt(vec2* pointArray, int arrayCount) {
	vec2 min = pointArray[0];
	vec2 max = pointArray[0];

	for (int i = 0; i < arrayCount; ++i) {
		min[0] = pointArray[i][0] < min[0] ? pointArray[i][0] : min[0];
		min[1] = pointArray[i][1] < min[1] ? pointArray[i][1] : min[1];
		max[0] = pointArray[i][0] > max[0] ? pointArray[i][0] : max[0];
		max[1] = pointArray[i][1] > max[1] ? pointArray[i][1] : max[1];
	}

	return Circle((min + max) * 0.5f, Magnitude(max - min) * 0.5f);
}

FixedRectangle ContainingRectangle(vec2* pointArray, int arrayCount) {
	vec2 min = pointArray[0];
	vec2 max = pointArray[0];

	for (int i = 0; i < arrayCount; ++i) {
		min[0] = pointArray[i][0] < min[0] ? pointArray[i][0] : min[0];
		min[1] = pointArray[i][1] < min[1] ? pointArray[i][1] : min[1];
		max[0] = pointArray[i][0] > max[0] ? pointArray[i][0] : max[0];
		max[1] = pointArray[i][1] > max[1] ? pointArray[i][1] : max[1];
	}

	return FromMinMax(min, max);
}




bool PointInShape(const BoundingShape& shape, const vec2& point) {
	for (auto& s : shape.circles) {
		if (PointInCircle(point, s)) {
			return true;
		}
	}
	for (auto& s : shape.rects) {
		if (PointInRectangle(point, s)) {
			return true;
		}
	}
	return false;
}

bool LineShape(const line2& line, const BoundingShape& shape) {
	for (auto& s : shape.circles) {
		if (LineCircle(line, s)) {
			return true;
		}
	}
	for (auto& s : shape.rects) {
		if (LineRectangle(line, s)) {
			return true;
		}
	}
	return false;
}

bool CircleShape(const Circle& circle, const BoundingShape& shape) {
	for (auto& s : shape.circles) {
		if (CircleCircle(circle, s)) {
			return true;
		}
	}
	for (auto& s : shape.rects) {
		if (CircleRectangle(circle, s)) {
			return true;
		}
	}
	return false;
}

bool RectangleShape(const FixedRectangle& rectangle, const BoundingShape& shape) {
	for (auto& s : shape.circles) {
		if (RectangleCircle(rectangle, s)) {
			return true;
		}
	}
	for (auto& s : shape.rects) {
		if (RectangleRectangle(rectangle, s)) {
			return true;
		}
	}
	return false;
}

bool OrientedRectangleShape(const OrientedRectangle& rect, const BoundingShape& shape) {
	for (auto& s : shape.circles) {
		if (OrientedRectangleCircle(rect, s)) {
			return true;
		}
	}
	for (auto& s : shape.rects) {
		if (OrientedRectangleRectangle(rect, s)) {
			return true;
		}
	}
	return false;
}


NAMESPACE_SOFTPHYS_END

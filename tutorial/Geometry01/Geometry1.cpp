#include "Geometry1.h"

// Geometry 1: Vectors


Geometry1::Geometry1() {
	
}

Geometry1::~Geometry1() {
	
}

void Geometry1::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void Geometry1::Render(Draw& draw) {
	draw.DrawRect(draw.GetPageSize(), Black());
	
	DrawGeometry fb(draw);
	
	
	Color red {255, 0, 0};
	Color green {0, 255, 0};
	Color blue {0, 0, 255};
	Color orange {255, 128, 0};
	Color yellow {255, 255, 0};
	Color pink {255, 42, 150};
	Color purple {170, 42, 150};
	Color lt_blue {28, 255, 255};
	
	float phase_f = (float)ts.Elapsed() / (float)phase_ms;
	float f = prev_phase_f + phase_f * 0.2;
	float f2 = f * 2.0;
	float f4 = f * 4.0;
	float x = cos(f * M_2PI);
	float y = sin(f * M_2PI);
	float x2 = cos(f2 * M_2PI);
	float y2 = sin(f2 * M_2PI);
	
	enum {X, Y, Z, W};
	
	{
		
		
		// If the W component is 0, the vector is a direction and a magnitude.
		// If the W component is anything else, usually 1, the vector is a point in space.
		vec3 point_in_space3	{1, 1, 0};
		vec4 point_in_space4	{1, 1, 0, 1};
		vec4 dir_and_magnitude	{1, 1, 0, 0};
		
		
		// Have few vectors
		vec2 origo {0, 0};
		vec2 short1 {2, 2};
		vec2 long1 {4, 4};
		
		// Add some motion to them
		short1[X] += x2;
		short1[Y] += y2;
		long1[X] += x;
		long1[Y] += y;
		
		// Draw original vectors as yellow (and scale them)
		float scale = 20;
		if (phase >= 0) {
			fb.DrawLine(origo, short1 * scale, 1, yellow);
			fb.DrawLine(origo, long1 * scale, 1, yellow);
		}
		
		// Add short and long vector, and draw them as orange
		// Also, draw chained vector as blue
		vec2 add = long1 + short1;
		if (phase >= 1) {
			fb.DrawLine(origo, add * scale, 1, orange);
			fb.DrawLine(long1 * scale, add * scale, 1, blue);
		}
		
		// Multiply two vectors to get dot product.
		// Draw the dot product as vector (both x and y are the dot product).
		// Use the green color.
		float dot_product = long1 * short1;
		vec2 mul = dot_product;
		if (phase >= 2) {
			fb.DrawLine(origo, mul * scale, 1, green);
		}
		
		// Have some different space and draw it's unit vectors as pink.
		// Draw them with separate origo to keep the image clean.
		float x_angle = 0.10 * M_2PI;
		float y_angle = 0.22 * M_2PI;
		vec2 x_ax2 {cosf(x_angle), sinf(x_angle)};
		vec2 y_ax2 {cosf(y_angle), sinf(y_angle)};
		vec2 origo2 {20, 10};
		if (phase >= 3) {
			fb.DrawLine(origo2 * scale, (x_ax2 + origo2) * scale, 1, pink);
			fb.DrawLine(origo2 * scale, (y_ax2 + origo2) * scale, 1, pink);
		}
		
		// Multiply the addition vector with the new x axis vector to get the closest
		// point in the new vector.
		// Multiply the x axis with the dot product the get the actual point.
		// Draw it as purple.
		// Also known as Project function.
		// Note: you don't need to divide by GetLengthSquared with unit vector.
		float closest_pt_in_x_ax2 = add * x_ax2;
		vec2 closest_pt_in_default_space_x_ax2 = x_ax2 * closest_pt_in_x_ax2;
		vec2 closest_pt_in_default_space_y_ax2 = y_ax2.GetProjection(add);
		if (phase >= 4) {
			fb.DrawLine(origo, closest_pt_in_default_space_x_ax2 * scale, 1, purple);
			fb.DrawLine(origo, closest_pt_in_default_space_y_ax2 * scale, 1, purple);
		}
		
		// A vector with a magnitude of 1 is a normal vector, sometimes called a unit vector.
		// A vector made from sin and cos has the magnitude of 1.
		// You can normalize a vector to make it's magnitude 1.
		ASSERT(x_ax2.GetLength() == 1.0f);
		ASSERT(y_ax2.GetLength() == 1.0f);
		ASSERT(add.GetLength() != 1.0f);
		float len = add.GetNormalized().GetLength();
		ASSERT(IsClose(len, 1.0f)); // accept rounding errors
		
		// Get perpendicular vector with the cross product.
		// Draw the perpendicular vector to the pink unit vector
		// Also draw a vector in perpendicular to the long green vector as light blue.
		// Draw it from the end of the green vector.
		vec2 ax2_ortho = x_ax2.GetCrossProduct(y_ax2);
		vec2 mul_ortho = mul.GetCrossProduct(mul * -1);
		mul_ortho.Normalize();
		if (phase >= 5) {
			fb.DrawLine(mul * scale, (mul_ortho + mul) * scale, 1, lt_blue);
			fb.DrawLine(origo2 * scale, (ax2_ortho + origo2) * scale, 1, lt_blue);
		}
		
		// Angle between new x-ax & y-ax is...
		float angle = x_ax2.GetAngle(y_ax2);
		float deg = angle / M_2PI * 360;
		
		// Reflect a vector from another vector...
		// The surface is in the direction of the x axis.
		// A another vector comes towards it from top left (-45 degree angle).
		// Your reflected vector should obviously be going top right (+45 degree angle).
		vec2 surface {1, 0};
		vec2 incoming_dir {1,-1};
		vec2 surface_normal = surface.GetCrossProduct(-surface).Normalize();
		ASSERT(surface_normal == vec2(0, -1)); // the normal should be in the direction of neg y-axis
		vec2 reflection = incoming_dir.GetReflection(surface_normal);
		ASSERT(reflection == vec2(1,1));
	}
	
	if (ts.Elapsed() > phase_ms) {
		ts.Reset();
		phase = (phase + 1) % phases;
		prev_phase_f = f;
	}
}

SIMPLE_ECS_APP_(Geometry1, "geom_tutorial_base.eon", "FRAGMENT=;VERTEX=;DRAWMEM=true")


#include "PlayEditor.h"
#include <Geometry/Geometry.h>

NAMESPACE_TOPSIDE_BEGIN



Image LiquidBokeh(Size sz, float time, Color a, Color b)
{
	ImageBuffer ib(sz);
	RGBA* dst = ib.Begin();
	
	vec2 res(sz.cx, sz.cy);
	
	vec3 a_base {0.3, 0.2, 0.0};
	vec3 b_base {0.3, 0.0, 0.4};
	
	if (1) {
		a_base[0] = a.GetR() / 255.0;
		a_base[1] = a.GetG() / 255.0;
		a_base[2] = a.GetB() / 255.0;
		b_base[0] = b.GetR() / 255.0;
		b_base[1] = b.GetG() / 255.0;
		b_base[2] = b.GetB() / 255.0;
	}
	
	for (int y = 0; y < sz.cy; y++) {
		for (int x = 0; x < sz.cx; x++) {
			vec2 coord(x,y);
			
			vec2 uv = coord / res * 2.0 - 1.0;
			uv[0] *=  res[0] / res[1];
			vec3 color = vec3(0.0);
			for (int i = 0; i < 128; i++) {
				float pha =      sin(float(i) * 546.13 + 1.0) * 0.5 + 0.5;
				float siz =  pow(sin(float(i) * 651.74 + 5.0) * 0.5 + 0.5, 4.0);
				float pox =      sin(float(i) * 321.55 + 4.1) * res[0] / res[1];
				float rad = 0.1 + 0.5 * siz + sin(pha + siz) / 4.0;
				vec2  pos = vec2(pox + sin(time / 15. + pha + siz), -1.0 - rad + (2.0 + 2.0 * rad) * fmod(pha + 0.3 * (time / 7.) * (0.2 + 0.8 * siz), 1.0));
				float dis = (uv - pos).GetLength();
				vec3  col =
					mix(
						vec3(
							0.194 * sin(time / 6.0) + a_base[0],
							a_base[1],
							0.3 * pha + a_base[2]),
						vec3(
							1.1 * sin(time / 9.0) + b_base[0],
							0.2 * pha + b_base[1],
							b_base[2]),
						0.5 + 0.5 * sin(float(i)));
				float f = (uv - pos).GetLength() / rad;
				f = sqrt(clamp(1.0 + (sin((time) * siz) * 0.5) * f, 0.0, 1.0));
				color += col * (1.0 - smoothstep(rad * 0.15, rad, dis));
			}
			color *= sqrt(1.5 - 0.5 * uv.GetLength());
			color *= 0.25;
			
			/*ASSERT(color[0] >= 0.0 && color[0] <= 1.0);
			ASSERT(color[1] >= 0.0 && color[1] <= 1.0);
			ASSERT(color[2] >= 0.0 && color[2] <= 1.0);*/
			color[0] = max(0.0f, min(1.0f, color[0]));
			color[1] = max(0.0f, min(1.0f, color[1]));
			color[2] = max(0.0f, min(1.0f, color[2]));
			
			dst->r = color[0] * 255;
			dst->g = color[1] * 255;
			dst->b = color[2] * 255;
			dst->a = 255;
			dst++;
		}
	}
	
	return ib;
}


NAMESPACE_TOPSIDE_END

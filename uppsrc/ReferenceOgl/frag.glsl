#version 120

varying vec3 f_colour;

void main(void) {
	gl_FragColor = vec4(f_colour.x, f_colour.y, f_colour.z, 1.0);
}

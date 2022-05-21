#version 120

attribute vec3 coord2d;
attribute vec3 v_colour;
varying vec3 f_colour;
uniform mat4 mvp;

void main(void) {
	gl_Position = mvp * vec4(coord2d, 1.0);
	f_colour=v_colour;
}
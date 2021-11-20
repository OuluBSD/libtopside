
uniform mat4 view;
uniform mat4 projection;
uniform mat4 scale;
uniform mat4 offset;

void mainVertex() {
	TexCoords = tex_coords;
	
    //gl_Position = projection * view * scale * offset * vec4(pos, 1.0);
    gl_Position = vec4(pos, 1.0);
    
}

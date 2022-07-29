

void mainVertex(out vec4 pos_out)
{
	vec3 pos = iPos.xyz;
	vec4 view_pos = iView * iModel * vec4(pos, 1.0);
	pos_out = normalize(view_pos);
	
	// info: http://gamma.cs.unc.edu/courses/graphics-s09/Zaferakis/hw6/
	#if 0
	vTexCoord[0] = vTexCoord[0]/view_pos[3];
	vTexCoord[1] = vTexCoord[1]/view_pos[3];
	vTexCoord[2] = 1.0/view_pos[3];
	#else
	vTexCoord[0] = vTexCoord[0];
	vTexCoord[1] = vTexCoord[1];
	vTexCoord[2] = 1.0;
	#endif
}

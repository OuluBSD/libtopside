void mainVertex(out vec4 pos_out)
{
	vec3 pos = iPos.xyz;
	pos_out = normalize(iModel * vec4(pos, 1.0));
}

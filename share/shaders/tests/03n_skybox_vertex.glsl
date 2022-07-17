

void mainVertex(out vec4 pos_out)
{
	vTexCoord = iPos.xyz;
	pos_out = iView * vec4(iPos.xyz, 1.0);
}

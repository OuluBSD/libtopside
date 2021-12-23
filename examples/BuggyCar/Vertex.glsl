
void mainVertex(out vec4 pos_out){
	//gl_Position = projection * view * scale * offset * vec4(pos, 1.0);
    //gl_Position = vec4(iPos, 1.0);
    //gl_Position = iProjection * iView * iScale * iTransform * iModel * vec4(iPos, 1.0);
    vec3 pos = iPos.xyz;
	pos.z = -pos.z + 1;
    pos_out = normalize(iView * vec4(pos, 1.0));
    
    //pos_out = iPos;
}

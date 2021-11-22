

void mainVertex() {
	TexCoords = iTexCoords;
	
    //gl_Position = projection * view * scale * offset * vec4(pos, 1.0);
    //gl_Position = vec4(iPos, 1.0);
    gl_Position = iProjection * iView * iScale * iTransform * iModel * vec4(iPos, 1.0);
    
}

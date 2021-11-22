#include "Graphics.h"

#ifdef HAVE_OPENGL

NAMESPACE_TOPSIDE_BEGIN


void Mesh::RefreshOgl(OglFramebufferObject& o) {
	ASSERT_(GetAppFlags().IsOpenGLContextOpen(), "OpenGL context is not open");
	if (!GetAppFlags().IsOpenGLContextOpen())
		return;
	
	auto& VAO = o.VAO;
	auto& VBO = o.VBO;
	auto& EBO = o.EBO;
	
	ASSERT(!VAO && !VBO && !EBO);
	
	// Create objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	// Set vertex array object data
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.GetCount() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
	// Set element buffer object data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.GetCount() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);
	o.element_count = indices.GetCount();
	
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	
	glBindVertexArray(0);
	
}

void Mesh::RefreshOgl(FramebufferObject& o) {
	OglFramebufferObject* ogl = CastPtr<OglFramebufferObject>(&o);
	ASSERT(ogl);
	if (ogl)
		RefreshOgl(*ogl);
}

NAMESPACE_TOPSIDE_END

#endif




#ifdef flagSCREEN

NAMESPACE_TOPSIDE_BEGIN


void OglFramebufferObject::Paint() {
	ASSERT(VBO && EBO && element_count > 0)
	if (!VBO || !EBO || !element_count)
		return;
	
	// bind VBOs for vertex array and index array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);            // for vertex coordinates
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);    // for indices
	
	const int vtx = 0;
	const int nm = 1;
	const int tex = 2;
	glEnableVertexAttribArray(vtx);          // activate vertex position array
	glEnableVertexAttribArray(nm);           // activate vertex normal array
	glEnableVertexAttribArray(tex);            // activate texture coords array
	
	// set vertex arrays with generic API
	const int stride = sizeof(Vertex);
	const void* offset1 = 0; // Vertex::position
	const void* offset2 = (void*)(4*sizeof(float)); // Vertex::normal
	const void* offset3 = (void*)(6*sizeof(float)); // Vertex::tex_coords
	glVertexAttribPointer(vtx, 3, GL_FLOAT, false, stride, offset1);
	glVertexAttribPointer(nm,  3, GL_FLOAT, false, stride, offset2);
	glVertexAttribPointer(tex, 2, GL_FLOAT, false, stride, offset3);
	
	// draw 6 faces using offset of index array
	glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
	
	glDisableVertexAttribArray(vtx);         // deactivate vertex position
	glDisableVertexAttribArray(nm);          // deactivate vertex normal
	glDisableVertexAttribArray(tex);         // deactivate texture coords
	
	// bind with 0, so, switch back to normal pointer operation
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OglFramebufferObject::MakeTexture(int tex_id, int width, int height, int pitch, int stride, const Vector<byte>& data) {
	GLint& gl_tex = this->tex.GetAdd(tex_id, -1);
	
	if (gl_tex < 0 && width > 0 && height > 0 && pitch > 0 && stride > 0 && data.GetCount()) {
		glGenTextures(1, (GLuint*)&gl_tex);
		glBindTexture(GL_TEXTURE_2D, gl_tex);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int channels = pitch / width;
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width, height,
			0,
			channels == 4 ? GL_BGRA : GL_BGR,
			GL_UNSIGNED_BYTE, data.Begin());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void OglFramebufferObject::FreeOgl() {
	if (VBO) {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
		VBO = 0;
		EBO = 0;
		VAO = 0;
	}
	
	for (GLint gl_tex : tex.GetValues())
		glDeleteTextures(1, (GLuint*)&gl_tex);
	tex.Clear();
}

#define PREIDX \
	auto idx = glGetUniformLocation(state.prog, name.Begin()); \
	if (idx >= 0)

#if 0
void OglFramebufferObject::SetBool(const String &name, bool value) const {
	PREIDX glUniform1i(idx, (int)value);
}

void OglFramebufferObject::SetInt(const String &name, int value) const {
	PREIDX glUniform1i(idx, value);
}

void OglFramebufferObject::SetFloat(const String &name, float value) const {
	PREIDX glUniform1f(idx, value);
}

void OglFramebufferObject::SetVec2(const String &name, const vec2 &value) const {
	PREIDX glUniform2f(idx, value.data[0], value.data[1]);
}

void OglFramebufferObject::SetVec3(const String &name, const vec3 &value) const {
	PREIDX glUniform3f(idx, value.data[0], value.data[1], value.data[2]);
}

void OglFramebufferObject::SetVec4(const String &name, const vec4 &value) const {
	PREIDX glUniform4f(idx, value.data[0], value.data[1], value.data[2], value.data[3]);
}

void OglFramebufferObject::SetMat2(const String &name, const mat2 &mat) const {
	PREIDX glUniformMatrix2fv(idx, 1, GL_FALSE, &mat[0][0]);
}

void OglFramebufferObject::SetMat3(const String &name, const mat3 &mat) const {
	PREIDX glUniformMatrix3fv(idx, 1, GL_FALSE, &mat[0][0]);
}

void OglFramebufferObject::SetMat4(const String &name, const mat4 &mat) const {
	PREIDX glUniformMatrix4fv(idx, 1, GL_FALSE, &mat[0][0]);
}

bool OglShader::Load(String vertex_path, String fragment_path, String geometry_path) {
	TODO
	#if 0
	LOG("Shader::Load: " << vertex_path << ", " << fragment_path << ", " << geometry_path);
	ClearError();
	
	// 1. retrieve the vertex/fragment source code from filePath
	String vertex_code;
	String fragment_code;
	String geometry_code;
	FileIn v_shader_file;
	FileIn f_shader_file;
	FileIn g_shader_file;
	
	// open files
	if (!v_shader_file.Open(vertex_path)) {SetError("vertex shader file could not been loaded"); return false;}
	if (!f_shader_file.Open(fragment_path)) {SetError("fragment shader file could not been loaded"); return false;}
	
	// convert stream into string
	int v_size = (int)v_shader_file.GetSize();
	vertex_code = v_shader_file.Get(v_size);
	int f_size = (int)f_shader_file.GetSize();
	fragment_code = f_shader_file.Get(f_size);
	
	// close file handlers
	v_shader_file.Close();
	f_shader_file.Close();
	
	// if geometry shader path is present, also load a geometry shader
	if (geometry_path.GetCount()) {
		if (!g_shader_file.Open(geometry_path))  {SetError("geometry shader file could not been loaded"); return false;}
		geometry_code = g_shader_file.Get((int)g_shader_file.GetSize());
		g_shader_file.Close();
	}
	
	const char* v_shader_code = vertex_code.Begin();
	const char* f_shader_code = fragment_code.Begin();
	
	// 2. compile shaders
	unsigned int vertex, fragment;
	
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &v_shader_code, NULL);
	glCompileShader(vertex);
	if (!CheckCompileErrors(vertex, "VERTEX")) return false;
	
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &f_shader_code, NULL);
	glCompileShader(fragment);
	if (!CheckCompileErrors(fragment, "FRAGMENT")) return false;
	
	// if geometry shader is given, compile geometry shader
	unsigned int geometry;
	
	if (geometry_path.GetCount()) {
		const char * gShaderCode = geometry_code.Begin();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		if (!CheckCompileErrors(geometry, "GEOMETRY")) return false;
	}
	
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	if (geometry_path.GetCount())
		glAttachShader(ID, geometry);
	glLinkProgram(ID);
	
	if (!CheckCompileErrors(ID, "PROGRAM")) return false;
	
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	if (geometry_path.GetCount())
		glDeleteShader(geometry);
	
	is_loaded = true;
	return true;
	#endif
}

void OglShader::Refresh(ModelMesh& model) {
	ASSERT(is_loaded);
	for (Mesh& mesh : model.meshes)
        Refresh(model, mesh);
}

void OglShader::Refresh(ModelMesh& model, Mesh& mesh) {
	
	// TODO glsl shaders etc.
	
	BasicMeshRefresh(model, mesh);
	
}

void OglShader::BasicMeshRefresh(ModelMesh& model, Mesh& mesh) {
	TODO
	#if 0
	if (!mesh.VAO)
		return;
	
	int tex_i = 0;
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		int tex_id = mesh.tex_id[i];
	    if (tex_id >= 0) {
	        Texture& tex = model.textures[tex_id];
	        tex.MakeAccel();
	        
	        glActiveTexture(GL_TEXTURE0 + tex_i); // activate proper texture unit before binding
	        // retrieve texture number (the N in diffuse_textureN)
	        String key;
	        if (i == TEXTYPE_DIFFUSE)
	            key = "material.texture_diffuse" + IntStr(diffuseNr++);
	        else if (i == TEXTYPE_SPECULAR)
	            key = "material.texture_specular" + IntStr(specularNr++);
	        
	        SetInt(key, tex_i);
	        
	        ASSERT(tex.tex_id >= 0);
	        glBindTexture(GL_TEXTURE_2D, tex.tex_id);
	        
	        tex_i++;
	    }
	}
    
    if (!mesh.is_colored_only)
	    SetBool("is_colored_only", false);
    else {
        vec4 v4 = MakeVec4(mesh.material.ambient, 1);
        SetBool("is_colored_only", true);
        SetVec4("in_color", v4);
    }

	//Dump();
	
    // draw mesh
    glBindVertexArray(mesh.VAO);
    glDrawElements(mesh.is_lines ? GL_LINES : GL_TRIANGLES, mesh.indices.GetCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
	
    
    // always good practice to set everything back to defaults once configured
    glActiveTexture(GL_TEXTURE0);
    #endif
}



void OglShader::Use() {
	TODO // glUseProgram(ID);
}
#endif

FramebufferObject* OglShader::CreateObject() {
	OglFramebufferObject& o = state.objects.Add(new OglFramebufferObject(state));
	o.id = state.objects.GetCount() - 1;
	RendVer1(OnRealizeObject, o.id);
	return &o;
}

#if 0
void OglShader::SetBool(const String &name, bool value) const {
	TODO // glUniform1i(glGetUniformLocation(ID, name.Begin()), (int)value);
}

void OglShader::SetInt(const String &name, int value) const {
	TODO // glUniform1i(glGetUniformLocation(ID, name.Begin()), value);
}

void OglShader::SetFloat(const String &name, float value) const {
	TODO // glUniform1f(glGetUniformLocation(ID, name.Begin()), value);
}

void OglShader::SetVec2(const String &name, const vec2 &value) const {
	TODO // glUniform2fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
}

void OglShader::SetVec2(const String &name, float x, float y) const {
	TODO // glUniform2f(glGetUniformLocation(ID, name.Begin()), x, y);
}

void OglShader::SetVec3(const String &name, const vec3 &value) const {
	TODO // glUniform3fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
}

void OglShader::SetVec3(const String &name, float x, float y, float z) const {
	TODO // glUniform3f(glGetUniformLocation(ID, name.Begin()), x, y, z);
}

void OglShader::SetVec4(const String &name, const vec4 &value) const {
	TODO // glUniform4fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
}

void OglShader::SetVec4(const String &name, float x, float y, float z, float w) const {
	TODO // glUniform4f(glGetUniformLocation(ID, name.Begin()), x, y, z, w);
}

void OglShader::SetMat2(const String &name, const mat2 &mat) const {
	TODO // glUniformMatrix2fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
}

void OglShader::SetMat3(const String &name, const mat3 &mat) const {
	TODO // glUniformMatrix3fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
}

void OglShader::SetMat4(const String &name, const mat4 &mat) const {
	TODO // glUniformMatrix4fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
}

bool OglShader::CheckCompileErrors(GLuint shader, String type) {
	TODO
	#if 0
	GLint success;
	GLchar infoLog[1024];
	
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			LOG("ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- ");
		}
	}
	
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			LOG("ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- ");
		}
	}
	
	return success;
	#endif
}
#endif





GLint OglFramebufferState::GetGlType() const {
	using namespace ShaderVar;
	switch (sample) {
		case SAMPLE_FLOAT:	return GL_FLOAT;
		case SAMPLE_U8:		return GL_UNSIGNED_BYTE;
		case SAMPLE_U16:	return GL_UNSIGNED_SHORT;
		case SAMPLE_U32:	return GL_UNSIGNED_INT;
		case SAMPLE_S32:	return GL_INT;
	}
	return -1;
}

GLint OglFramebufferState::GetGlFormat() const {
	using namespace ShaderVar;
	ASSERT(channels >= 1 && channels <= 4);
	if (sample != SAMPLE_FLOAT) {
		switch (channels) {
			case 1: return GL_RED;
			case 2: return GL_RG;
			case 3: return GL_RGB;
			case 4: return GL_RGBA;
			default: return -1;
		}
	}
	else {
		switch (channels) {
			case 1: return GL_R32F;
			case 2: return GL_RG32F;
			case 3: return GL_RGB32F;
			case 4: return GL_RGBA32F;
			default: return -1;
		}
	}
	return -1;
}

int OglFramebufferState::GetGlSize() const {
	return size.cx * size.cy * GetGlSampleSize() * channels;
}

int OglFramebufferState::GetGlSampleSize() const {
	using namespace ShaderVar;
	switch (sample) {
		case SAMPLE_FLOAT:	return 4;
		case SAMPLE_U8:		return 1;
		case SAMPLE_U16:	return 2;
		case SAMPLE_U32:	return 4;
		case SAMPLE_S32:	return 4;
	}
	ASSERT(0);
	return 0;
}


NAMESPACE_TOPSIDE_END

#endif

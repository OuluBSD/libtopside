#include "Graphics.h"

#ifdef flagGUI

NAMESPACE_TOPSIDE_BEGIN


bool OpenGLShader::Load(String vertex_path, String fragment_path, String geometry_path) {
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
	int v_size = v_shader_file.GetSize();
	vertex_code = v_shader_file.Get(v_size);
	int f_size = f_shader_file.GetSize();
	fragment_code = f_shader_file.Get(f_size);
	
	// close file handlers
	v_shader_file.Close();
	f_shader_file.Close();
	
	// if geometry shader path is present, also load a geometry shader
	if (geometry_path.GetCount()) {
		if (!g_shader_file.Open(geometry_path))  {SetError("geometry shader file could not been loaded"); return false;}
		geometry_code = g_shader_file.Get(g_shader_file.GetSize());
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
}

void OpenGLShader::Paint(ModelMesh& model) {
	ASSERT(is_loaded);
	for (Mesh& mesh : model.meshes)
        Paint(model, mesh);
}

void OpenGLShader::Paint(ModelMesh& model, Mesh& mesh) {
	
	// TODO glsl shaders etc.
	
	BasicMeshPaint(model, mesh);
	
}

void OpenGLShader::BasicMeshPaint(ModelMesh& model, Mesh& mesh) {
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
	
    
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
    
}



void OpenGLShader::Use() {
	glUseProgram(ID);
}
void OpenGLShader::SetBool(const String &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.Begin()), (int)value);
}

void OpenGLShader::SetInt(const String &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.Begin()), value);
}

void OpenGLShader::SetFloat(const String &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.Begin()), value);
}

void OpenGLShader::SetVec2(const String &name, const vec2 &value) const {
	glUniform2fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
}

void OpenGLShader::SetVec2(const String &name, float x, float y) const {
	glUniform2f(glGetUniformLocation(ID, name.Begin()), x, y);
}

void OpenGLShader::SetVec3(const String &name, const vec3 &value) const {
	glUniform3fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
}

void OpenGLShader::SetVec3(const String &name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.Begin()), x, y, z);
}

void OpenGLShader::SetVec4(const String &name, const vec4 &value) const {
	glUniform4fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
}

void OpenGLShader::SetVec4(const String &name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(ID, name.Begin()), x, y, z, w);
}

void OpenGLShader::SetMat2(const String &name, const mat2 &mat) const {
	glUniformMatrix2fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
}

void OpenGLShader::SetMat3(const String &name, const mat3 &mat) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
}

void OpenGLShader::SetMat4(const String &name, const mat4 &mat) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
}

bool OpenGLShader::CheckCompileErrors(GLuint shader, String type) {
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
}


NAMESPACE_TOPSIDE_END

#endif

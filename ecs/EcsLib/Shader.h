#ifndef _System_Shader_h_
#define _System_Shader_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN

class Shader {
	bool is_loaded = false;
	
public:
	Shader() {}
	
	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	bool Load(String vertex_path, String fragment_path, String geometry_path = "") {
		LOG("Shader::Load: " << vertex_path << ", " << fragment_path << ", " << geometry_path);
		
		// 1. retrieve the vertex/fragment source code from file_path
		String vertex_code;
		String fragment_code;
		String geometry_code;
		FileIn v_shader_file;
		FileIn f_shader_file;
		FileIn g_shader_file;
		
		try {
			// open files
			if (!v_shader_file.Open(vertex_path)) throw Exc();
			if (!f_shader_file.Open(fragment_path)) throw Exc();
			
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
				if (!g_shader_file.Open(geometry_path)) throw Exc();
				geometry_code = g_shader_file.Get(g_shader_file.GetSize());
				g_shader_file.Close();
			}
		}
		
		catch (Exc e) {
			LOG("ERROR: shaders not successfully read: " << vertex_path);
			return false;
		}
		
		const char* v_shader_code = vertex_code.Begin();
		const char * f_shader_code = fragment_code.Begin();
		
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
			const char * g_shader_code = geometry_code.Begin();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &g_shader_code, NULL);
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
	
	bool IsLoaded() const {return is_loaded;}
	
	
	// activate the shader
	// ------------------------------------------------------------------------
	void Use() {
		glUseProgram(ID);
	}
	
	// utility uniform functions
	// ------------------------------------------------------------------------
	void SetBool(const String &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.Begin()), (int)value);
	}
	
	// ------------------------------------------------------------------------
	void SetInt(const String &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.Begin()), value);
	}
	
	// ------------------------------------------------------------------------
	void SetFloat(const String &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.Begin()), value);
	}
	
	// ------------------------------------------------------------------------
	void SetVec2(const String &name, const vec2 &value) const {
		glUniform2fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
	}
	
	void SetVec2(const String &name, float x, float y) const {
		glUniform2f(glGetUniformLocation(ID, name.Begin()), x, y);
	}
	
	// ------------------------------------------------------------------------
	void SetVec3(const String &name, const vec3 &value) const {
		glUniform3fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
	}
	
	void SetVec3(const String &name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(ID, name.Begin()), x, y, z);
	}
	
	// ------------------------------------------------------------------------
	void SetVec4(const String &name, const vec4 &value) const {
		glUniform4fv(glGetUniformLocation(ID, name.Begin()), 1, &value[0]);
	}
	
	void SetVec4(const String &name, float x, float y, float z, float w) {
		glUniform4f(glGetUniformLocation(ID, name.Begin()), x, y, z, w);
	}
	
	// ------------------------------------------------------------------------
	void SetMat2(const String &name, const mat2 &mat) const {
		glUniformMatrix2fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
	}
	
	// ------------------------------------------------------------------------
	void SetMat3(const String &name, const mat3 &mat) const {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
	}
	
	// ------------------------------------------------------------------------
	void SetMat4(const String &name, const mat4 &mat) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.Begin()), 1, GL_FALSE, &mat[0][0]);
	}
	
	
	void PushMultiplyMat4(String key, const mat4& mat) {
		mat4& next = stack.Add();
		mat4& prev = stack[stack.GetCount()-2];
		next = prev * mat;
	}
	
	void PopMat4() {
		stack.SetCount(stack.GetCount()-1);
	}
	
	void SetStackMat4(const mat4& mat) {
		stack.SetCount(1);
		stack[0] = mat;
	}
	
private:
	
	Vector<mat4> stack;
	
	
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	bool CheckCompileErrors(GLuint shader, String type) {
		GLint success;
		GLchar info_log[1024];
		
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				LOG("ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- ");
			}
		}
		
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, info_log);
				LOG("ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << "\n -- --------------------------------------------------- -- ");
			}
		}
		
		return success;
	}
};

NAMESPACE_TOPSIDE_END

#endif
#endif


#pragma once

#include <Object.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <common/shader.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program {
public:
	typedef std::shared_ptr<Program> Ptr;
	typedef std::shared_ptr<const Program> PtrConst;

	static Ptr Create(char* vertexFile, char* fragmentFile);
	static Ptr Create(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* fragmentFile);
	static Ptr Create(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* geometryFile, char* fragmentFile);

	void Use();

	void Set1i(GLint value, const GLchar* name);
	void Set1f(GLfloat value, const GLchar* name);
	void SetVec2(vec2 value, const GLchar* name);
	void SetVec3(vec3 value, const GLchar* name);
	void SetVec4(vec4 value, const GLchar* name);
	void SetMat3(mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void SetMat4(mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);

	Program(char* vertexFile, char* fragmentFile);
	Program(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* fragmentFile);
	Program(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* geometryFile, char* fragmentFile);
	~Program();

	void SetName(const string& _name) {
		name = _name;
	}

	const string& GetName() {
		return name;
	}

	GLuint GetID() {
		return id;
	}

private:
	string name;
	GLuint id;
	int versionMajor = 3; //const
	int versionMinor = 3; //const

};
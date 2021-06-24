#include "Program.h"

Program::Ptr Program::Create(char* vertexFile, char* fragmentFile)
{
	auto ptr = Program::Ptr(new Program(vertexFile, fragmentFile));
	ptr->SetName("<program>");
	return ptr;
}

Program::Ptr Program::Create(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* fragmentFile)
{
	auto ptr = Program::Ptr(new Program(vertexFile, tesscontrolFile, tessevaluationFile, fragmentFile));
	ptr->SetName("<program>");
	return ptr;
}

Program::Ptr Program::Create(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* geometryFile, char* fragmentFile)
{
	auto ptr = Program::Ptr(new Program(vertexFile, tesscontrolFile, tessevaluationFile, geometryFile, fragmentFile));
	ptr->SetName("<program>");
	return ptr;
}

Program::Program(char* vertexFile, char* fragmentFile) {
	id = LoadShaders(vertexFile, fragmentFile);
}

Program::Program(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* fragmentFile) {
	id = LoadShaders(vertexFile, tesscontrolFile, tessevaluationFile, fragmentFile);
}

Program::Program(char* vertexFile, char* tesscontrolFile, char* tessevaluationFile, char* geometryFile, char* fragmentFile) {
	id = LoadShaders(vertexFile, tesscontrolFile, tessevaluationFile, geometryFile, fragmentFile);
}

Program::~Program() {
	glDeleteProgram(id);
}

void Program::Use() {
	glUseProgram(id);
}

void Program::Set1i(GLint value, const GLchar* name) {
	Use();
	glUniform1i(glGetUniformLocation(id, name), value);
	glUseProgram(0);
}

void Program::Set1f(GLfloat value, const GLchar* name) {
	Use();
	glUniform1f(glGetUniformLocation(id, name), value);
	glUseProgram(0);
}

void Program::SetVec2(vec2 value, const GLchar* name) {
	Use();
	glUniform2fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	glUseProgram(0);
}

void Program::SetVec3(vec3 value, const GLchar* name) {
	Use();
	glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	glUseProgram(0);
}

void Program::SetVec4(vec4 value, const GLchar* name) {
	Use();
	glUniform4fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
	glUseProgram(0);
}

void Program::SetMat3(mat3 value, const GLchar* name, GLboolean transpose) {
	Use();
	glUniformMatrix3fv(glGetUniformLocation(id, name), 1, transpose, glm::value_ptr(value));
	glUseProgram(0);
}

void Program::SetMat4(mat4 value, const GLchar* name, GLboolean transpose) {
	Use();
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, transpose, glm::value_ptr(value));
	glUseProgram(0);
}

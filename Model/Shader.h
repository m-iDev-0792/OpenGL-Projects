//
// Created by 何振邦 on 2017/9/10.
//
#include <OpenGL/gl3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef MODEL_SHADER_H
#define MODEL_SHADER_H

class Shader {
public:

	Shader(const char *vertexPath, const char *fragmentPath);

	void use() { glUseProgram(id); };

	void setFloat(const std::string &name, float value) { glUniform1f(glGetUniformLocation(id, name.c_str()), value); };

	void setBool(const std::string &name, bool value) {
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
	};

	void setInt(const std::string &name, int value) { glUniform1i(glGetUniformLocation(id, name.c_str()), value); };

	void set3fv(const std::string &name, glm::vec3 value) {
		glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
	};

	void set2fv(const std::string &name, glm::vec2 value) {
		glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
	};

	void set4fm(const std::string &name, glm::mat4 value) {
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	};

	GLuint getID() { return id; };

private:
	GLuint id;

	void checkCompileError(GLuint shader, std::string type);

	char *readShader(const char *filename);
};


char *Shader::readShader(const char *filename) {
	using namespace std;
	ifstream file(filename, ios::in);
	if (!file.is_open()) {
		cout << "ERROR WHEN LOAD SHADER FILE！ CAN'T OPEN FILE:" << filename << endl;
		return nullptr;
	} else {
		string text;
		file.seekg(0, ios::end);
		text.resize(file.tellg());
		file.seekg(0, ios::beg);
		file.read(&text[0], text.size());
		file.close();
		char *p = new char[text.size() + 1];
		strcpy(p, text.c_str());
		return p;
	}
}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
	char *vertexCode = readShader(vertexPath);
	char *fragmentCode = readShader(fragmentPath);
	GLuint vertexID, fragmentID;

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexCode, NULL);
	glCompileShader(vertexID);
	checkCompileError(vertexID, "VERTEX");

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentCode, NULL);
	glCompileShader(fragmentID);
	checkCompileError(fragmentID, "FRAGMENT");

	id = glCreateProgram();
	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);
	glLinkProgram(id);
	checkCompileError(id, "PROGRAM");

	//clean
	if (vertexCode != nullptr)delete vertexCode;
	if (fragmentCode != nullptr)delete fragmentCode;
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void Shader::checkCompileError(GLuint shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
			          << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
			          << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

#endif //MODEL_SHADER_H

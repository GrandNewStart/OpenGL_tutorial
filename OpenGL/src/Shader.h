#pragma once
#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp> 

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	unsigned int m_RendererID;

	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniformi(const std::string& name, int i);
};
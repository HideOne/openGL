#ifndef SHADERMANAGER
#define SHADERMANAGER

 // !SHADERMANAGER
#include<glad/glad.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class ShaderManager
{
public:
	//��ȡ��������ɫ��
	ShaderManager();
	ShaderManager(const GLchar* vertexPath, const GLchar* fragmentPath);
	~ShaderManager();

	//ʹ�ü������
	void use();

	//uniform ���ߺ���ŭ
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void CompileShader(const char* vertexCode, const  char* fragmentCode);

	//����ID
	unsigned int ID;

private:
	GLint CreateShader(char const *code, GLenum ShderType); 
	void CreateShaderProgram(GLint vertexShade, GLint fragmentShaderr);
};

#endif
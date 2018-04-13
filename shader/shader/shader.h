#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

extern enum object;

#define LOG(info) \
{\
  std::cout<<"====="<<info<<"====="<<std::endl; \
}

GLFWwindow* createGLFWWindow();


//���ڴ�С�ı�Ļص����� ���ڴ�С�ı�ʱ��Ӧ�ı��ӿڴ�С
void Frame_Size_CallBack(GLFWwindow* window, int width, int heigt);


void mainLoop(GLFWwindow* window);

//��������
void processInput(GLFWwindow* window);

void CreateShader(int* vertexShader, char const *string, GLenum type);

void CreateShaderProgram(unsigned int *shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);
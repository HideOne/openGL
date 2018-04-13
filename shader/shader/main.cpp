#include "shader.h"
#include "DrawPic.h"
#include "ShaderManager.h"

float vertices[] = {
	//λ��               ��ɫ
	-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
};

float points[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
};

unsigned int indices[] = { // ע��������0��ʼ! 
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"//out vec4 vertexColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"//vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"ourColor = aColor;\n"
"}\n\0";

char* fragmentShaderSource = {
	"\
		#version 330 core\n\
			out vec4 FragColor;\n\
			in vec4 vertexColor;\n\
			in vec3 ourColor;\n\
			void main()\n\
			{\n\
			FragColor = vec4(ourColor, 1.0);\n\
			}\n\
	"
};


char* uniform = {
	"\
		#version 330 core\
		out vec4 FragColor;\
		uniform vec4 ourColor;//��opengl����������趨�������\
		void main()\
		{\
		FragColor = ourColor;\
		}\
	"
};


extern float vertices[];

extern enum object;

int main()
{
	GLFWwindow* window = createGLFWWindow();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG("Failed to initialize GLAD");
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//ע�ᴰ�ڳߴ�ı�ص�����
	glfwSetFramebufferSizeCallback(window, Frame_Size_CallBack);

	//���� ��ʼ��VBO���� 
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#if 0
	//������ɫ��
	int vertexShader;
	CreateShader(&vertexShader, vertexShaderSource, GL_VERTEX_SHADER);

	//Ƭ����ɫ��
	int fragmentShader;
	CreateShader(&fragmentShader, fragmentShaderSource, GL_FRAGMENT_SHADER);

	//������ɫ������
	unsigned int shaderProgram = 0;
	CreateShaderProgram(&shaderProgram, vertexShader, fragmentShader);

#endif
	
	ShaderManager shader("shader/shader.vs", "shader/shader.fs");


	int vertexPosLocation = glGetUniformLocation(shader.ID, "offset");
	glUseProgram(shader.ID);
	glUniform4f(vertexPosLocation, 0.3f, 0.0f, 0.0f, 1.0f);

	//����VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//�Ѷ��㸴�Ƶ�������
#if 0
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//���ö�������ָ��
	//����OpenGL����ν�����������
	//λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//����EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	

	while (!glfwWindowShouldClose(window))
	{
		//���� 
		processInput(window);

		//��Ⱦ
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		shader.use();

		//����uniform��ɫ
		//����uniform
		//float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
		//glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, greenValue, greenValue, 0.0f, 1.0f);


#if 1
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
#else
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}






	//�ͷ���Դ
	glfwTerminate();
	LOG("hello");
	return 0;
}
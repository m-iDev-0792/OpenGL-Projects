//程序作用，绘制一个平面并对其进行3D视角变换
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

//全局变量

//窗口设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const float ambientStrength = 0.1;
const float specularStength = 0.5;
float fov = 45.0f;
const float mouseSensitivity = 0.05;
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;

//For joystick
float lastJoyX=0.0f;
float lastJoyY=0.0f;
bool hasJoyStick=false;
bool firstMouse = true;
bool mouseDown = false;
float yaw = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 8.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightPos=glm::vec3(1.0f,1.0f,-2.0f);
float moveSpeed = 0.25;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void processInput(GLFWwindow *window);

void mouse_button_callback(GLFWwindow *window,int,int,int);
void joystick_handle();

char *readShader(const char *filename);

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

	// glfw window creation
	// --------------------
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Light", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window,mouse_button_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
	if (present == GLFW_TRUE){
		std::cout << "检测到手柄" <<name<< std::endl;
		hasJoyStick = true;
	}



	//配置盒子
	//配置盒子
	//配置盒子
	//配置盒子
	// ------------------------------------
	const char *vertexShaderSource = readShader("boxVertex.glsl");
	const char *fragmentShaderSource = readShader("boxFragment.glsl");
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	float vertices[] = {
			// positions          //normal
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
			29, 30, 31, 32, 33, 34, 35
	};



	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//配置盒子结束
	//配置盒子结束
	//配置盒子结束
	//配置盒子结束

	//光源设置开始
	//光源设置开始
	//光源设置开始
	const char *lightVertexShaderSource = readShader("lightVertex.glsl");
	const char *lightFragmentShaderSource = readShader("lightFragment.glsl");
	// vertex shader
	int lightVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(lightVertexShader, 1, &lightVertexShaderSource, NULL);
	glCompileShader(lightVertexShader);
	// check for shader compile errors

	glGetShaderiv(lightVertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(lightVertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// fragment shader
	int lightFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(lightFragmentShader, 1, &lightFragmentShaderSource, NULL);
	glCompileShader(lightFragmentShader);
	// check for shader compile errors
	glGetShaderiv(lightFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(lightFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// link shaders
	int lightShaderProgram = glCreateProgram();
	glAttachShader(lightShaderProgram, lightVertexShader);
	glAttachShader(lightShaderProgram, lightFragmentShader);
	glLinkProgram(lightShaderProgram);
	// check for linking errors
	glGetProgramiv(lightShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(lightShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(lightVertexShader);
	glDeleteShader(lightFragmentShader);


	float lightVertices[] = {
			// positions                     // texture coords
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
	};
	unsigned int lightIndices[] = {  // note that we start from 0!
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
			29, 30, 31, 32, 33, 34, 35
	};



	unsigned int lightVBO, lightVAO, lightEBO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightEBO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//光源设置结束
	//光源设置结束
	//光源设置结束
//////////////////////////////////////////////////////////////////////////////////////////////
							//本次程序新增的重要代码部分
//////////////////////////////////////////////////////////////////////////////////////////////




	//generate framebuffer
	GLuint framebuffer;
	glGenFramebuffers(1,&framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
	//color tex
	GLuint colorTex;
	glGenTextures(1,&colorTex);
	glBindTexture(GL_TEXTURE_2D,colorTex);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,SCR_WIDTH,SCR_HEIGHT,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D,0);
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,colorTex,0);




	GLuint rbo;
	glGenRenderbuffers(1,&rbo);
	glBindRenderbuffer(GL_RENDERBUFFER,rbo);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,SCR_WIDTH,SCR_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER)==GL_FRAMEBUFFER_COMPLETE)
		std::cout<<"framebuffer is complete now"<<std::endl;
	else std::cout<<"framebuffer is not complete,so sad"<<std::endl;

////////////////////////////////下面设置绘制长方形的工作////////////////////////////////
	float frameVertex[]={
			// positions   // texCoords
			-0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  1.0f, 0.0f,

			-0.5f,  0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  1.0f, 1.0f
	};
	GLuint scrVAO;
	glGenVertexArrays(1,&scrVAO);
	glBindVertexArray(scrVAO);

	GLuint scrVBO;
	glGenBuffers(1,&scrVBO);
	glBindBuffer(GL_ARRAY_BUFFER,scrVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(frameVertex),frameVertex,GL_STATIC_DRAW);

	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)(2* sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	const char* frameVertexSource=readShader("frameVertex.glsl");
	const char* frameFragmentSource=readShader("frameFragment.glsl");
	GLuint frameVertexShader,frameFragmentShader;
	frameVertexShader=glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(frameVertexShader,1,&frameVertexSource,NULL);
	glCompileShader(frameVertexShader);

	glGetShaderiv(frameVertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(frameVertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	frameFragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frameFragmentShader,1,&frameFragmentSource,NULL);
	glCompileShader(frameFragmentShader);
	glGetShaderiv(frameFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(frameFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint frameProgram;
	frameProgram=glCreateProgram();
	glAttachShader(frameProgram,frameVertexShader);
	glAttachShader(frameProgram,frameFragmentShader);
	glLinkProgram(frameProgram);
	glGetProgramiv(frameProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(frameProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(frameVertexShader);
	glDeleteShader(frameFragmentShader);
	glUseProgram(frameProgram);
	glUniform1i(glGetUniformLocation(frameProgram,"colorTex"),0);


///////////////////////////////////////////////////////////////////////////////////////////
							//主要增加代码结束
///////////////////////////////////////////////////////////////////////////////////////////

	// 渲染循环
	// -------渲染前的一些初始化


	double lasttime = glfwGetTime();
	double currenttime = lasttime;
	while (!glfwWindowShouldClose(window)) {
		currenttime = glfwGetTime();
		if (currenttime - lasttime > 0.05) {
			lasttime = currenttime;
			processInput(window);

			joystick_handle();

		}



		glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//绘制盒子
		//matrix transformations:
		glm::mat4 model;
		//model=glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
		model = glm::rotate(model, 0.5f*(float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 view;
		//如果是一个典型的fps摄像机，lookat的第二个参数应该是摄像机的前面的一个点，而不是一个固定的点
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection;
		projection = glm::perspective<float>(glm::radians(fov), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glUniform1f(glGetUniformLocation(shaderProgram,"ambientStrength"),ambientStrength);
		glUniform1f(glGetUniformLocation(shaderProgram,"specularStrength"),specularStength);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glm::vec3 lightColor(1.0f,1.0f,1.0f);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightColor"),lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"),lightPos.x,lightPos.y,lightPos.z);
		glUniform3f(glGetUniformLocation(shaderProgram,"cameraPos"),cameraPos.x,cameraPos.y,cameraPos.z);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//绘制光源
		glUseProgram(lightShaderProgram);
		glm::mat4 lightModel;
		lightModel = glm::translate(lightModel, lightPos);
		glUniformMatrix4fv(glGetUniformLocation(lightShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniformMatrix4fv(glGetUniformLocation(lightShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightShaderProgram, "projection"), 1, GL_FALSE,
		                   glm::value_ptr(projection));
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		////////////////////////////画框了//////////////////////////////
		glBindFramebuffer(GL_FRAMEBUFFER,0);
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(frameProgram);
		glUniform1i(glGetUniformLocation(frameProgram,"colorTex"),0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,colorTex);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(scrVAO);

		glDrawArrays(GL_TRIANGLES,0,6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraFront * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraFront * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * moveSpeed;
	}


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

char *readShader(const char *filename) {
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

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	if (fov >= 1 && fov <= 45)fov -= yoffset;
	if (fov <= 1)fov = 1.0f;
	else if (fov >= 45)fov = 45.0f;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	if(!mouseDown)return;
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void joystick_handle(){
	if(!hasJoyStick)return;
	int axeCount;
	const float *joyStickAxes=glfwGetJoystickAxes(GLFW_JOYSTICK_1,&axeCount);

	float xpos=joyStickAxes[2];
	float ypos=joyStickAxes[3];
	float xoffset = xpos - lastJoyX;
	float yoffset = lastJoyY - ypos;
	lastJoyX = xpos;
	lastJoyY = ypos;
	int Sensitivity=10;
	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		mouseDown = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mouseDown = false;
		firstMouse = true;
	}
}


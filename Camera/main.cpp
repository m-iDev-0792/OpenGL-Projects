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
float factor=0.2;
float fov=45.0f;
const float mouseSensitivity=0.05;
float lastX=SCR_WIDTH/2;float lastY=SCR_HEIGHT/2;
bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp=glm::vec3(0.0f,1.0f,0.0f);
float moveSpeed=0.25;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);
void mouse_callback(GLFWwindow* window,double xpos,double ypos);
void processInput(GLFWwindow *window);
char * readShader(const char * filename);



int main()
{

	const char *vertexShaderSource =readShader("vertex.glsl");
	const char *fragmentShaderSource = readShader("fragment.glsl");

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window,scroll_callback);
	glfwSetCursorPosCallback(window,mouse_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//载入第一个纹理
	int texWidth,texHeight,texChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char * texData=stbi_load("128.jpg",&texWidth,&texHeight,&texChannel,0);
	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if(texData){
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texWidth,texHeight,0,GL_RGB,GL_UNSIGNED_BYTE,texData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else{
		std::cout<<"failed to load image"<<std::endl;
		return -1;
	}
	stbi_image_free(texData);
	//载入第二个纹理

	unsigned char * texData2=stbi_load("floor.jpg",&texWidth,&texHeight,&texChannel,0);
	unsigned int texture2;
	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D,texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if(texData2){
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texWidth,texHeight,0,GL_RGB,GL_UNSIGNED_BYTE,texData2);
		glGenerateMipmap(GL_TEXTURE_2D);

	}else{
		std::cout<<"failed to load image2"<<std::endl;
		return -1;
	}
	stbi_image_free(texData2);



	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
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

	glUseProgram(shaderProgram);//切记在指定纹理之前一定要使用着色器程序 否则第二个纹理将无法显示
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
			// positions                     // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
			//0, 1, 3,  // first Triangle
			//1, 2, 3   // second Triangle
			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	double lasttime=glfwGetTime();
	double currenttime=lasttime;
	//准备好变换矩阵





	while (!glfwWindowShouldClose(window))
	{
		currenttime=glfwGetTime();
		if(currenttime-lasttime>0.05){
			lasttime=currenttime;
			processInput(window);
		}
		//matrix transformations:
		glm::mat4 model;
		//model=glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
		model=glm::rotate(model,(float)glfwGetTime(),glm::vec3(0.0f,1.0f,0.0f));
		glm::mat4 view;
		//如果是一个典型的fps摄像机，lookat的第二个参数应该是摄像机的前面的一个点，而不是一个固定的点
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection;
		projection=glm::perspective<float>(glm::radians(fov),SCR_WIDTH/SCR_HEIGHT,0.1f,100.0f);
		// render
		// ------
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glUniform1f(glGetUniformLocation(shaderProgram,"factor"),factor);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));


		//真正进行绘图
		glDrawArrays(GL_TRIANGLES, 0, 36);//注意：使用了gldrawarray  似乎EBO便没有使用
		//glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);//效果和gldrawelements一样，不过这一句使用了EBO


		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS){
		factor+=0.05;
		if(factor>=1.0)factor=1.0;
	}
	if(glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS){
		factor-=0.05;
		if(factor<=0)factor=0.0;
	}
	if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS) {
		cameraPos+=cameraFront*moveSpeed;
	}
	if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS){
		cameraPos-=cameraFront*moveSpeed;
	}
	if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS){
		cameraPos-=glm::normalize(glm::cross(cameraFront, cameraUp))*moveSpeed;
	}
	if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS){
		cameraPos+=glm::normalize(glm::cross(cameraFront, cameraUp))*moveSpeed;
	}


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0,0,width, height);
}

char * readShader(const char * filename){
	using namespace std;
	ifstream file(filename,ios::in);
	if(!file.is_open()){
		cout<<"ERROR WHEN LOAD SHADER FILE！ CAN'T OPEN FILE:"<<filename<<endl;
		return nullptr;
	}else{
		string text;
		file.seekg(0,ios::end);
		text.resize(file.tellg());
		file.seekg(0,ios::beg);
		file.read(&text[0],text.size());
		file.close();
		char *p=new char[text.size()+1];
		strcpy(p,text.c_str());
		return p;
	}
}
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
	if(fov>=1&&fov<=45)fov-=yoffset;
	if(fov<=1)fov=1.0f;
	else if(fov>=45)fov=45.0f;
}
void mouse_callback(GLFWwindow* window,double xpos,double ypos){
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset=xpos-lastX;
	float yoffset=lastY-ypos;
	lastX=xpos;
	lastY=ypos;
	xoffset*=mouseSensitivity;
	yoffset*=mouseSensitivity;

	//std::cout<<xoffset<<std::endl;
	yaw+=xoffset;
	pitch+=yoffset;
	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x=cos(glm::radians(pitch))*cos(glm::radians(yaw));
	front.y=sin(glm::radians(pitch));
	front.z=cos(glm::radians(pitch))*sin(glm::radians(yaw));
	cameraFront=glm::normalize(front);
}
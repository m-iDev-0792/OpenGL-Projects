#include "Model.h"
#include "Shader.h"
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);
void mouse_callback(GLFWwindow* window,double xpos,double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float fov=45.0f;
bool firstMouse=true;
bool mouseDown=false;
const float mouseSensitivity=0.5;
float lastX=SCR_WIDTH/2;float lastY=SCR_HEIGHT/2;
float yaw   =  0.0f;
float pitch =  0.0f;
glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Model", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window,mouse_callback);
	glfwSetScrollCallback(window,scroll_callback);
	glfwSetMouseButtonCallback(window,mouse_button_callback);



	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);*/
	Shader shader("vertex.glsl","fragment.glsl");
//	Model model("SWAT officer/swat.obj");
//	Model model("nanosuit/nanosuit.obj");
	Model model("earth/earth.obj");
	Shader outlineShader("vertex.glsl","outlineFrag.glsl");



	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.5f,0.5f,0.5f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

//		glStencilMask(0x00);
		shader.use();

		glm::mat4 modelMat;
		modelMat=glm::rotate(modelMat,glm::radians(pitch),glm::vec3(-1.0f,0.0f,0.0f));
		modelMat=glm::rotate(modelMat,glm::radians(yaw),glm::vec3(0.0f,1.0f,0.0f));
//		modelMat = glm::translate(modelMat, glm::vec3(0.0f, -1.75f, 0.0f));
		modelMat = glm::scale(modelMat, glm::vec3(0.005f, 0.005f, 0.005f));
		glm::mat4 view;
		//如果是一个典型的fps摄像机，lookat的第二个参数应该是摄像机的前面的一个点，而不是一个固定的点
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection;
		projection=glm::perspective<float>(glm::radians(fov),SCR_WIDTH/SCR_HEIGHT,0.1f,100.0f);



		shader.set4fm("model",modelMat);
		shader.set4fm("view",view);
		shader.set4fm("projection",projection);
		shader.setFloat("shininess",6.0f);
		shader.set3fv("lightStrength.ambient",glm::vec3(0.2f));
		shader.set3fv("lightStrength.diffuse",glm::vec3(1.0f));
		shader.set3fv("lightStrength.specular",glm::vec3(0.4f));
		shader.setFloat("lightStrength.linear",0.0014f);
		shader.setFloat("lightStrength.quadratic",0.00007f);

		/*glStencilFunc(GL_ALWAYS,1,0xFF);
		glStencilMask(0xFF);*/

		model.draw(shader);

		/*//绘制边框
		glStencilFunc(GL_NOTEQUAL,1,0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		glm::mat4 outlineModel;
		outlineModel=glm::rotate(outlineModel,glm::radians(pitch),glm::vec3(-1.0f,0.0f,0.0f));
		outlineModel=glm::rotate(outlineModel,glm::radians(yaw),glm::vec3(0.0f,1.0f,0.0f));
		outlineModel = glm::translate(outlineModel, glm::vec3(0.0f, -1.75f*(0.21f/0.2f), 0.0f));
		outlineModel = glm::scale(outlineModel, glm::vec3(0.21f, 0.21f, 0.21f));

		outlineShader.use();
		outlineShader.set4fm("model",outlineModel);
		outlineShader.set4fm("view",view);
		outlineShader.set4fm("projection",projection);
		glStencilMask(0xFF);
		model.draw(outlineShader);
		glEnable(GL_DEPTH_TEST);*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

	glViewport(0, 0, width, height);
}
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset){
	if(fov>=1&&fov<=45)fov-=yoffset;
	if(fov<=1)fov=1.0f;
	else if(fov>=45)fov=45.0f;
}
void mouse_callback(GLFWwindow* window,double xpos,double ypos){

	if(!mouseDown)return;
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

	/*if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;*/


}
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		mouseDown = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mouseDown = false;
		firstMouse = true;
	}
}
#include "Model.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow* window,double xoffset,double yoffset);
void mouse_callback(GLFWwindow* window,double xpos,double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
unsigned int TextureFromCurrentDir(const char *path);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float fov=45.0f;
bool firstMouse=true;
bool mouseDown=false;
const float mouseSensitivity=0.5;
float lastX=SCR_WIDTH/2;float lastY=SCR_HEIGHT/2;
float yaw   =  0.0f;
float pitch =  0.0f;
glm::vec3 cameraPos=glm::vec3(0.0f,0.5f,2.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Blend", NULL, NULL);
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	Shader shader("common.vert","common.frag");

	//配置盒子
	std::vector<Vertex> boxVertex;
	boxVertex.push_back(Vertex(-0.1f, -0.1f, -0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, -0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, -0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, -0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, -0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, 0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, 0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, 0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, 0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, 0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, -0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, 0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, -0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, 0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, -0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, -0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, 0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, -0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, -0.1f, 0.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, -0.1f, 1.0f, 1.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(0.1f, 0.1f, 0.1f, 1.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, 0.1f, 0.0f, 0.0f));
	boxVertex.push_back(Vertex(-0.1f, 0.1f, -0.1f, 0.0f, 1.0f));
	std::vector<unsigned int> boxIndices;
	for(unsigned int i=0;i<36;++i)boxIndices.push_back(i);
	std::vector<Texture> boxTexture;
	GLuint boxTexID=TextureFromCurrentDir("boxTex.jpg");
	boxTexture.push_back(Texture(boxTexID,"diffuse"));
	Mesh box(boxVertex,boxIndices,boxTexture);

	//配置地面
	std::vector<Vertex> floorVertex;
	floorVertex.push_back(Vertex(0.5f,  0.0f, -0.5f,   1.0f, 1.0f));
	floorVertex.push_back(Vertex(0.5f, 0.0f, 0.5f,    1.0f, 0.0f));
	floorVertex.push_back(Vertex(-0.5f, 0.0f, 0.5f,   0.0f, 0.0f));
	floorVertex.push_back(Vertex(-0.5f,  0.0f, -0.5f,   0.0f, 1.0f));
	std::vector<unsigned int> floorIndices={0, 1, 3, 1, 2, 3};
	GLuint floorTexID=TextureFromCurrentDir("floor.jpg");
	std::vector<Texture> floorTexture;
	floorTexture.push_back(Texture(floorTexID,"diffuse"));
	Mesh floor(floorVertex,floorIndices,floorTexture);

	//配置窗户
	std::vector<Vertex> windowVertex;
	windowVertex.push_back(Vertex(0.1f,  0.1f, 0.0f,   1.0f, 1.0f));
	windowVertex.push_back(Vertex(0.1f, -0.1f, 0.0f,    1.0f, 0.0f));
	windowVertex.push_back(Vertex(-0.1f, -0.1f, 0.0f,   0.0f, 0.0f));
	windowVertex.push_back(Vertex(-0.1f,  0.1f, 0.0f,   0.0f, 1.0f));

	std::vector<unsigned int> windowIndices={0,1,3,1,2,3};
	GLuint windowTexID=TextureFromCurrentDir("windows.png");
	std::vector<Texture> windowTexture;
	windowTexture.push_back(Texture(windowTexID,"diffuse"));
	Mesh windows(windowVertex,windowIndices,windowTexture);

	std::vector<glm::vec3> windowPosition;
	windowPosition.push_back(glm::vec3(-0.4f,0.2f,-0.3f));
	windowPosition.push_back(glm::vec3(-0.3f,0.2f,0.3f));
	windowPosition.push_back(glm::vec3(0.2f,0.2f,1.0f));


	std::vector<glm::vec3> boxPositions;
	boxPositions.push_back(glm::vec3(0.5f,0.1f,-0.5f));
	boxPositions.push_back(glm::vec3(-0.5f,0.3f,-0.2f));
	boxPositions.push_back(glm::vec3(-0.5f,0.1f,0.0f));
	boxPositions.push_back(glm::vec3(0.0f,0.1f,0.0f));
	boxPositions.push_back(glm::vec3(0.2f,0.1f,0.2f));
	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.5f,0.5f,0.5f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		shader.use();


		glm::mat4 view;
		glm::mat4 projection;
		//modelMat=glm::rotate(modelMat,glm::radians(pitch),glm::vec3(-1.0f,0.0f,0.0f));
		//modelMat=glm::rotate(modelMat,glm::radians(yaw),glm::vec3(0.0f,1.0f,0.0f));
		//如果是一个典型的fps摄像机，lookat的第二个参数应该是摄像机的前面的一个点，而不是一个固定的点
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
		projection=glm::perspective<float>(glm::radians(fov),SCR_WIDTH/SCR_HEIGHT,0.1f,100.0f);
		shader.set4fm("view",view);
		shader.set4fm("projection",projection);

		for (int i=0;i<boxPositions.size();i++) {
			glm::mat4 boxModel;
			boxModel = glm::translate(boxModel, boxPositions[i]);

			shader.set4fm("model",boxModel);
			box.draw(shader);
		}

		glm::mat4 floorModel;
		floorModel=glm::translate(floorModel,glm::vec3(0.0f,0.0f,0.0f));
		floorModel=glm::scale(floorModel,glm::vec3(2.0f,2.0f,2.0f));
		shader.set4fm("model",floorModel);
		floor.draw(shader);

		for (int i=0;i<windowPosition.size();i++) {
			glm::mat4 windowModel;
			windowModel=glm::translate(windowModel,windowPosition[i]);
			shader.set4fm("model",windowModel);
			windows.draw(shader);
		}
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
unsigned int TextureFromCurrentDir(const char *path)
{
	std::string filename = std::string(path);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

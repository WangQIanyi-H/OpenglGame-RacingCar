//GLAD����������OPENGL�ĺ���ָ��ģ������ڵ����κ�OPENGL����֮ǰ������Ҫ��ʼ��GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/filesystem.h>
#include <learnopengl/model.h>

#include"FixedCamera.h"
#include"Car.h"


#include <iostream>

/*--------------���ڳ�ʼ��---------------*/
//���ڳ�ʼ��
GLFWwindow* windowInit();
//����OPENGL����ָ�룬����ȫ��OPENGL״̬
bool init();
//�ı䴰�ڴ�С�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


/*--------------������ʼ��--------------*/
//���ͼ����
void depthMapFBOInit();
//��պ�������
void skyboxInit();
//��պ��ӣ��������������Ϊһ��cubemap����
unsigned int loadCubemap(vector<std::string> faces);

/*-------------ʱ������-------------------*/
//����һ֡��ʱ�䳤��
void setDeltaTime();


/*-------------�������------------------*/
void updateFixedCamera();

/*---------------��Ⱦ����----------------*/
// ���ù����������
void renderLight(Shader& shader);

void renderCarAndCamera(Model& carModel, Model& cameraModel, Shader& shader);

void renderCar(Model& model, glm::mat4 modelMatrix, Shader& shader);

void renderCamera(Model& model, glm::mat4 modelMatrix, Shader& shader);

void renderRaceTrack(Model& model, Shader& shader);

void renderSkyBox(Shader& shader);

/*------------------����/�������--------------------*/
//��������
void handleKeyInput(GLFWwindow* window);
//ģʽ����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//�������
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// ����������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



/*-------------------��ʼ����---------------------*/
//���ڷֱ���
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
// ��Ⱦ��Ӱʱ�Ĵ��ڷֱ��ʣ���Ӱ����Ӱ�ľ�ݱ������
const unsigned int SHADOW_WIDTH = 1024 * 10;
const unsigned int SHADOW_HEIGHT = 1024 * 10;
// �Ƿ�Ϊ�߿�ͼģʽ
bool isPolygonMode = false;
// ��������ϵY�ᵥλ����
glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);
// ����
Car car(glm::vec3(0.0f, 0.05f, 0.0f));
// ���
glm::vec3 cameraPos(0.0f, 2.0f, 5.0f);
Camera camera(cameraPos);
FixedCamera fixedCamera(cameraPos);
bool isCameraFixed = false;
// �����������
glm::vec3 lightPos(-1.0f, 1.0f, -1.0f);
glm::vec3 lightDirection = glm::normalize(lightPos);
glm::mat4 lightSpaceMatrix;
// ���Map��ID
unsigned int depthMap;
unsigned int depthMapFBO;
// �������������Ļ����
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing ����ƽ�ⲻͬ������Ⱦˮƽ���������ٶȱ仯
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// ��պ�
unsigned int cubemapTexture;
unsigned int skyboxVAO, skyboxVBO;
// ��պж�������
const float skyboxVertices[] = {
	// positions
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};
// ��պе�������
const vector<std::string> faces{
	"asset/textures/skybox2/right.jpg",
	"asset/textures/skybox2/left.jpg",
	"asset/textures/skybox2/top.jpg",
	"asset/textures/skybox2/bottom.jpg",
	"asset/textures/skybox2/front.jpg",
	"asset/textures/skybox2/back.jpg"
};



int main()
{
	//���ڳ�ʼ��
	GLFWwindow* window = windowInit();
	//��ʼ��GLAD
	bool isInit = init();

	if (window == NULL || !isInit) {
		std::cout << "��ʼ��ʧ��" << std::endl;
		return -1;
	}

	//���������ͼ
	depthMapFBOInit();
	// ������պ���
	skyboxInit();

	/*------------------Shader-----------------*/
	// Ϊ����������ӹ��պ���Ӱ��shader
	Shader shader("shader/light_and_shadow.vs", "shader/light_and_shadow.fs");
	// ��̫��ƽ�й�Ƕ����������Ϣ��shader
	Shader depthShader("shader/shadow_mapping_depth.vs", "shader/shadow_mapping_depth.fs");
	// ��պ�shader
	Shader skyboxShader("shader/skybox.vs", "shader/skybox.fs");

	/*------------------ģ�ͼ���----------------*/
	// ����ģ��
	Model carModel(FileSystem::getPath("asset/models/obj/car/car.obj"));
	// ���ģ��
	Model cameraModel(FileSystem::getPath("asset/models/obj/camera-cube/camera-cube.obj"));
	// ����ģ��
	Model raceTrackModel(FileSystem::getPath("asset/models/obj/race-track/race-track.obj"));

	/*-----------------shader��������--------------*/
	shader.use();
	shader.setInt("diffuseTexture", 0);
	shader.setInt("shadowMap", 15); // �����15��ָ"GL_TEXTURE15"����Ҫ�����Ķ�Ӧ

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	/*-------------------��Ⱦѭ��------------------*/
	while (!glfwWindowShouldClose(window))
	{
		// ����һ֡��ʱ�䳤���Ա���ʹ֡�����ٶȾ���
		setDeltaTime();
		// ��������
		handleKeyInput(window);

		//���������Ļ���õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//�����ɫ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//������Ӱ
		//�����Դ�Ӽ��壬����Ӱ���ɷ�Χ������ͶӰ����
		glm::mat4 lightProjection = glm::ortho(
			-200.0f, 200.0f,
			-200.0f, 200.0f,
			-200.0f, 200.0f);
		// TODO lightPos�������λ�ý����ƶ���ʹ�����Χ�ĵط��ܻ�����Ӱ��
		glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), WORLD_UP);
		lightSpaceMatrix = lightProjection * lightView;

		// �ӹ�Դ�Ƕ���Ⱦ��������
		depthShader.use();
		depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		// �ı��ӿڴ�С�Ա��ڽ�����ȵ���Ⱦ
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

		/*------------���ɳ���ģ��-------------*/
		glClear(GL_DEPTH_BUFFER_BIT);
		renderCarAndCamera(carModel, cameraModel, depthShader);
		renderRaceTrack(raceTrackModel, depthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// ��ԭ�ӿ�
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*---------------��Ⱦģ��---------------*/
		shader.use();
		// ���ù����������
		renderLight(shader);

		car.UpdateDelayYaw();
		car.UpdateDelayPosition();

		// �л�Ϊ����̶�ʱ����Ҫÿ��֡�޸����״̬
		if (isCameraFixed) {
			updateFixedCamera();
		}
		// ʹ��shader��Ⱦcar��Camera���㼶ģ�ͣ�
		renderCarAndCamera(carModel, cameraModel, shader);
		// ��Ⱦ����
		renderRaceTrack(raceTrackModel, shader);

		// ��Ⱦ��պ�
		// �ı���Ȳ��ԣ�ʹ��ȵ���1.0ʱΪ����Զ
		glDepthFunc(GL_LEQUAL);
		skyboxShader.use();
		renderSkyBox(skyboxShader);
		// ��ԭ��Ȳ���
		glDepthFunc(GL_LESS);

		//������ɫ����
		glfwSwapBuffers(window);

		//�����û�г���ʲô�¼��������������ȣ������´���״̬�������ö�Ӧ�Ļص�����
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

GLFWwindow* windowInit()
{
	//��ʼ��glfw
	glfwInit();

	//����glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//���ô��� �� �� ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "��������ʧ��" << std::endl;
		//��ֹ
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	// ע��֡�����С����, ����GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// ��GLFW��׽�û������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return window;
}

bool init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "��ʼ��GLADʧ��" << std::endl;
		return false;
	}

	// ����ȫ��openGL״̬
	glEnable(GL_DEPTH_TEST);

	return true;
}

// ���ͼ����
void depthMapFBOInit()
{
	glGenFramebuffers(1, &depthMapFBO);
	// �����������
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// �����ɵ����������Ϊ֡�������Ȼ���
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
// ��պ�����
void skyboxInit()
{
	// skybox VAO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// �������
	cubemapTexture = loadCubemap(faces);
}

// ����һ֡��ʱ�䳤��
void setDeltaTime()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void updateFixedCamera()
{
	// �Զ��𽥸�ԭZoomΪĬ��ֵ
	camera.ZoomRecover();

	// �����������ڳ�����ϵ�µ���������ת��Ϊ��������ϵ�µ�����
	float angle = glm::radians(-car.getMidValYaw());
	glm::mat4 rotateMatrix(
		cos(angle), 0.0, sin(angle), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sin(angle), 0.0, cos(angle), 0.0,
		0.0, 0.0, 0.0, 1.0);
	glm::vec3 rotatedPosition = glm::vec3(rotateMatrix * glm::vec4(fixedCamera.getPosition(), 1.0));

	camera.FixView(rotatedPosition + car.getMidValPosition(), fixedCamera.getYaw() + car.getMidValYaw());
}

// ���ù����������
void renderLight(Shader& shader)
{
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("lightDirection", lightDirection);
	shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_2D, depthMap);
}

void renderCarAndCamera(Model& carModel, Model& cameraModel, Shader& shader)
{
	// ��ͼת��
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	shader.setMat4("view", viewMatrix);
	// ͶӰת��
	glm::mat4 projMatrix = camera.GetProjMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);
	shader.setMat4("projection", projMatrix);

	// -------
	// �㼶��ģ

	// ģ��ת��
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, car.getMidValPosition());
	modelMatrix = glm::rotate(modelMatrix, glm::radians(car.getDelayYaw() / 2), WORLD_UP);

	// ��Ⱦ����
	renderCar(carModel, modelMatrix, shader);

	// ����mat4����������ʱΪֵ���ݣ��ʲ���Ҫ����modelMatrix

	// ��Ⱦ���
	renderCamera(cameraModel, modelMatrix, shader);
}

// ��Ⱦ����
void renderCar(Model& model, glm::mat4 modelMatrix, Shader& shader)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(car.getYaw() - car.getDelayYaw() / 2), WORLD_UP);
	// ����ģ��ԭ���Դ�����ת
	modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f), WORLD_UP);
	// ����ģ�ʹ�С
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.004f, 0.004f, 0.004f));

	// Ӧ�ñ任����
	shader.setMat4("model", modelMatrix);

	model.Draw(shader);
}

void renderCamera(Model& model, glm::mat4 modelMatrix, Shader& shader)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(fixedCamera.getYaw() + car.getYaw() / 2), WORLD_UP);
	modelMatrix = glm::translate(modelMatrix, cameraPos);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));

	// Ӧ�ñ任����
	shader.setMat4("model", modelMatrix);

	model.Draw(shader);
}

void renderRaceTrack(Model& model, Shader& shader)
{
	// ��ͼת��
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	shader.setMat4("view", viewMatrix);
	// ģ��ת��
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	shader.setMat4("model", modelMatrix);
	// ͶӰת��
	glm::mat4 projMatrix = camera.GetProjMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);
	shader.setMat4("projection", projMatrix);

	model.Draw(shader);
}

void renderSkyBox(Shader& shader)
{
	// viewMatrix ͨ�����죬�Ƴ�������ƶ�
	glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));
	// ͶӰ
	glm::mat4 projMatrix = camera.GetProjMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);

	shader.setMat4("view", viewMatrix);
	shader.setMat4("projection", projMatrix);

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void handleKeyInput(GLFWwindow* window)
{
	// esc�˳�
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (!isCameraFixed) {
		// ��� WSAD ǰ������ Space�� ��Ctrl��
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera.ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			camera.ProcessKeyboard(DOWN, deltaTime);
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			fixedCamera.ProcessKeyboard(CAMERA_LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			fixedCamera.ProcessKeyboard(CAMERA_RIGHT, deltaTime);
	}

	// �����ƶ�
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		car.ProcessKeyboard(CAR_FORWARD, deltaTime);

		// ֻ�г�����������ʱ��ſ���������ת
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			car.ProcessKeyboard(CAR_LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			car.ProcessKeyboard(CAR_RIGHT, deltaTime);

		if (isCameraFixed)
			camera.ZoomOut();
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		car.ProcessKeyboard(CAR_BACKWARD, deltaTime);

		// ͬ��
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			car.ProcessKeyboard(CAR_LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			car.ProcessKeyboard(CAR_RIGHT, deltaTime);

		if (isCameraFixed)
			camera.ZoomIn();
	}

	// �ص�����������һ������ֻ�ᴥ��һ���¼���
	glfwSetKeyCallback(window, key_callback);
}

// �����ص�������ʹ��һ�ΰ���ֻ����һ���¼�
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		isCameraFixed = !isCameraFixed;
		string info = isCameraFixed ? "�л�Ϊ�̶��ӽ�" : "�л�Ϊ�����ӽ�";
		std::cout << "[CAMERA]" << info << std::endl;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		isPolygonMode = !isPolygonMode;
		if (isPolygonMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		string info = isPolygonMode ? "�л�Ϊ�߿�ͼ��Ⱦģʽ" : "�л�Ϊ������Ⱦģʽ";
		std::cout << "[POLYGON_MODE]" << info << std::endl;
	}
}

// ����ƶ�
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!isCameraFixed) {
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // ���귭ת�Զ�Ӧ����ϵ

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

// ������
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// �������������Ϊһ��cubemap����
unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

//֡�����С������ÿ�����ڸı��С��GLFW�������������������Ӧ�Ĳ���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

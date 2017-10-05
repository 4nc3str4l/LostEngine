#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../Engine/Gfx/Utils/Shader.h"
#include "../Engine/Gfx/Utils/Camera.h"
#include "../Engine/Gfx/Models/Model.h"

#include "../Engine/Gfx/Lights/DirectionalLight.h"
#include "../Engine/Gfx/Lights/SpotLight.h"
#include "../Engine/Gfx/Lights/PointLight.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

LostEngine::Gfx::Camera camera(glm::vec3(0.0f, 0.0f, 80.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lost Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	LostEngine::Gfx::Shader ourShader("./resources/shaders/lights.vs", "./shaders/lights.fs");
	LostEngine::Gfx::Model ourModel("./resources/models/earth/earth.obj");

	LostEngine::Gfx::DirectionalLight dirLight(
		new glm::vec3(-0.2f, -1.0f, -0.3f),
		new glm::vec3(0.05f, 0.05f, 0.05f),
		new glm::vec3(0.4f, 0.4f, 0.4f),
		new glm::vec3(0.5f, 0.5f, 0.5f));

	LostEngine::Gfx::SpotLight spotLight(
		new glm::vec3(0.1f, 0.1f, 0.1f),
		new glm::vec3(1.0f, 1.0f, 1.0f),
		new glm::vec3(1.0f, 1.0f, 1.0f),
		new glm::vec3(0.0f, 0.0f, 0.0f),
		1.0f,
		0.09f,
		0.032f,
		new glm::vec3(0.0f, 0.0f, 0.0f),
		glm::cos(glm::radians(12.5f)),
		glm::cos(glm::radians(15.0f)));

	LostEngine::Gfx::PointLight pointLight(
		new glm::vec3(0.1f, 0.1f, 0.1f),
		new glm::vec3(1.0f, 1.0f, 1.0f),
		new glm::vec3(1.0f, 1.0f, 1.0f),
		new glm::vec3(0.0f, 0.0f, 0.0f),
		1.0f,
		0.09f,
		0.032f
	);

	ourShader.Use();
	ourShader.SetFloat("material.shininess", 32.0f);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		ourShader.Use();

		ourShader.SetMat4("projection", projection);
		ourShader.SetMat4("view", view);

		ourShader.SetVec3("viewPos", camera.Position);

		ourShader.SetVec3("spotLight.position", camera.Position);
		ourShader.SetVec3("spotLight.direction", camera.Front);

		ourShader.SetVec3("dirLight.direction", *dirLight.Direction);
		ourShader.SetVec3("dirLight.ambient", *dirLight.Ambient);
		ourShader.SetVec3("dirLight.diffuse", *dirLight.Diffuse);
		ourShader.SetVec3("dirLight.specular", *dirLight.Specular);

		ourShader.SetVec3("spotLight.position", camera.Position);
		ourShader.SetVec3("spotLight.direction", camera.Front);
		ourShader.SetVec3("spotLight.ambient", *spotLight.Ambient);
		ourShader.SetVec3("spotLight.diffuse", *spotLight.Diffuse);
		ourShader.SetVec3("spotLight.specular", *spotLight.Specular);
		ourShader.SetFloat("spotLight.constant", spotLight.Constant);
		ourShader.SetFloat("spotLight.linear", spotLight.Linear);
		ourShader.SetFloat("spotLight.quadratic", spotLight.Quadratic);
		ourShader.SetFloat("spotLight.cutOff", spotLight.Cutoff);
		ourShader.SetFloat("spotLight.outerCutOff", spotLight.OuterCutoff);

		ourShader.SetVec3("pointLights[0].position", *pointLight.Position);
		ourShader.SetVec3("pointLights[0].ambient", *pointLight.Ambient);
		ourShader.SetVec3("pointLights[0].diffuse", *pointLight.Diffuse);
		ourShader.SetVec3("pointLights[0].specular", *pointLight.Specular);
		ourShader.SetFloat("pointLights[0].constant", pointLight.Constant);
		ourShader.SetFloat("pointLights[0].linear", pointLight.Linear);
		ourShader.SetFloat("pointLights[0].quadratic", pointLight.Quadratic);

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.SetMat4("model", model);
		ourModel.Draw(ourShader);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(LostEngine::Gfx::FORWARD, deltaTime * 2);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(LostEngine::Gfx::BACKWARD, deltaTime * 2);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LostEngine::Gfx::LEFT, deltaTime * 2);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(LostEngine::Gfx::RIGHT, deltaTime * 2);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
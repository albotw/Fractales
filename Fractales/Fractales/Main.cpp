#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "FPSCounter.h"
#include "Shader.hpp"
#include "Point.h"

#include "Dragon.h"
#include "Sierpinsky.h"
#include "Mandelbrot.h"

using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 800;

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "impossible d'initialiser l'application");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3 window", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "impossible de cr�er la fen�tre glfw");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "impossible d'initialiser GLEW");
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	std::vector<Point> vertices{ 0 };

	int algorithm = 0;
	std::cout << "Entrez le type de fractale a afficher" << std::endl;
	std::cout << "1: Dragon" << std::endl;
	std::cout << "2: Sierpinsky" << std::endl;
	std::cout << "3: mandelbrot" << std::endl;
	std::cin >> algorithm;

	if (algorithm == 1)
	{
		Point A{
		-0.55f, 0.0f, 0.0f,
		0.1f, 0.2f, 0.3f
		};

		Point B{
			0.55f, 0.0f, 0.0f,
			0.3f, 0.1f, 0.2f
		};

		generateDragon(20, A, B, vertices);
	}
	else if (algorithm == 2)
	{
		Point B{
		-1.0f, -1.0f, 0.0f,
		0.01f, 0.5f, 0.01f
		};

		Point A{
			0.0f, 1.0f, 0.0f,
			0.5f, 0.01f, 0.01f
		};

		Point C{
			1.0f, -1.0f, 0.0f,
			0.01f, 0.01f, 0.5f
		};

		generateSierpinsky(8, A, B, C, vertices);
	}
	else if (algorithm == 3)
	{
		vertices = generateMandelbrot(-2.1, 0.6, -1.2, 1.2, 1.0, 800, 600, 50);
		Point origine{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
		};

		vertices.push_back(origine);
	}
	else
	{
		exit(0);
	}

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Point), &vertices[0], GL_STATIC_DRAW);

	//positions XYZ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
	glEnableVertexAttribArray(0);

	//couleur RGB
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader shader = Shader("shaders/vertexShader.generic.glsl", "shaders/fragmentShader.generic.glsl");

	glEnable(GL_DEPTH_TEST);

	initFPSCounter();
	do {
		displayFPS(window);
		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

}

//adapte le framebuffer � la fen�tre en cas de redimensionnement
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

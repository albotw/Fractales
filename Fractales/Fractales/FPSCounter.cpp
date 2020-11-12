#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "FPSCounter.h"
double lastTime;
int nbFrames;
void initFPSCounter() {
	lastTime = glfwGetTime();
	nbFrames = 0;
}

void displayFPS(GLFWwindow *window) {
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		// printf and reset timer
		char title[256];
		title[255] = '\0';

		snprintf(title, 255,
			"%s %s - [MPF: %3.2f] - [FPS: %i]",
			"OpenGL app", "1.0", 1000.0f / (float)nbFrames, nbFrames);

		glfwSetWindowTitle(window, title);

		nbFrames = 0;
		lastTime += 1.0;
	}
}
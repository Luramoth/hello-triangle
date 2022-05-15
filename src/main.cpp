#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

//constants
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {// class that holds the actual application
public:
	void run() { //essentally the "main" function for the vulkan app
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	VkInstance instance;// create Vulkan instance
	GLFWwindow* window;// make a window class for glfw

	void initWindow(){
		glfwInit(); //initialise glfw

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);// tell glfw NOT to use openGL
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);// tell glfw to not make the window resisable

		window = glfwCreateWindow(WIDTH,HEIGHT,"Vulkan",nullptr,nullptr); // have glfw create the window
	}
	
	void initVulkan() {
		
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)){ // wait till the window errors or the user tell it to close
			glfwPollEvents();
		}
	}

	void cleanup() {
		glfwDestroyWindow(window);

		glfwTerminate();
	}
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
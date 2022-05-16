#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

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
		createInstance(); // make vulkan instance
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)){ // wait till the window errors or the user tell it to close
			glfwPollEvents();
		}
	}

	void cleanup() {
		vkDestroyInstance(instance,nullptr);

		glfwDestroyWindow(window);//get rid of the window class and free up the allocated memory

		glfwTerminate();//stop glfw from running
	}

	void createInstance(){
		VkApplicationInfo appInfo{};//start up thing to get all the parameters for vulkan
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Hello Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};// use all that to make some info
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);// some stuff about glfw extensions that i cant be bothered to learn about yet

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);// finally make all the info needed

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {// if vk dident fuck up then continue
			throw std::runtime_error("failed to create instance!");
		}

		// after creating instance grab what extensions are available
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> extensions(extensionCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		std::cout << "available extentions:\n";

		for (const auto& extension : extensions) {
			std::cout << '\t' << extension.extensionName << '\n';
		}
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
#include "headers/common.hpp"

int main() {
	if (enableValidationLayers){
		std::cout<<"running in debug mode\n";
	}

	HelloTriangleApplication app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
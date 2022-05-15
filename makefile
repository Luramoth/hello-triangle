CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

HelloTriangle: src/main.cpp
	g++ $(CFLAGS) -o build/HelloTriangle src/main.cpp $(LDFLAGS)

.PHONY: test clean

test: HelloTriangle
	./build/HelloTriangle

clean:
	rm -f build/HelloTriangle

build:
	g++ -Wall -std=c++17 -I"./libs" src/*.cpp src/Engine/*.cpp src/Engine/Logger/*.cpp -lglfw -lGLEW -framework OpenGL -o 3Drenderer

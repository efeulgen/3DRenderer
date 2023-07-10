build:
	g++ -Wall -std=c++17 -I"./libs" src/*.cpp src/Engine/*.cpp -lglfw -lGLEW -framework OpenGL -o 3Drenderer

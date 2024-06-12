
SRC = src/*.cpp src/Engine/*.cpp src/Engine/Logger/*.cpp src/Engine/Managers/*.cpp src/Engine/PrimitiveMeshes/*.cpp src/Engine/Shaders/*.cpp
OBJ_NAME = 3Drenderer

########################################################################################################################################

build:
	g++ -Wall -std=c++17 -I"./libs" $(SRC) -lglfw -lGLEW -lassimp -framework OpenGL -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

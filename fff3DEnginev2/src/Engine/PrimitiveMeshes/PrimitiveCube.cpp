
#include "PrimitiveCube.h"

PrimitiveCube::PrimitiveCube(int id, const char *t) : Mesh(id, t)
{
    Logger::Log("PrimitiveCube Consructor");

    unsigned int i[] = {
        0, 1, 2,
        2, 3, 1,
        4, 5, 6,
        6, 7, 5,
        8, 9, 10,
        10, 11, 9,
        12, 13, 14,
        14, 15, 13,
        16, 17, 18,
        18, 19, 17,
        20, 21, 22,
        22, 23, 21

        /*0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2*/
    };
    indices = i;
    numOfIndices = 36;

    GLfloat v[] = {
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, -0.5, -0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, 0.5,
        0.5, -0.5, -0.5};
    vertices = v;
    numOfVertices = 72;
}

PrimitiveCube::~PrimitiveCube()
{
    Logger::Log("PrimitiveCube Destructor");
}

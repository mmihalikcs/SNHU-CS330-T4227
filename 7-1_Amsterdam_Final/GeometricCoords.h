#pragma once
#include <vector>
#include <GL/glew.h>        // GLEW library

class GeometricCoords
{
public:
	static std::vector<GLfloat>* GenerateTreeCoords();
	static std::vector<GLfloat>* GenerateCanalWallCoords();
	static std::vector<GLfloat>* GenerateBuildingCoords();
	static std::pair<std::vector<GLfloat>*, std::vector<GLushort>*>  GenerateStreetLampCoords();
	static std::vector<GLfloat>* GeneratePlaneCoords();
private:
	static void BuildSphere(float radius, unsigned int rings, unsigned int sectors, std::vector<GLfloat>& sphereCoords, std::vector<GLushort>& sphereIndices);
};

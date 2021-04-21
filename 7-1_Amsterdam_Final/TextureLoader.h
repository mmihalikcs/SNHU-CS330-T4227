#pragma once
// Built-In
#include <iostream>
#include <map>
#include <vector>

// Customs
#include "Enums.h"

// OpenGL
#include <GL/glew.h>        // GLEW library
#include "stb_image.h"      // Image loading Utility functions

class TextureLoader
{
	// Variables
	static std::map<Enums::MeshType, std::vector<GLuint>> MeshTextureMap;
public:
	// Methods
	static void LoadTextures();
	static GLuint RetrieveTextureProgramId(Enums::MeshType key);
	static void UDestroyTexture(GLuint textureId);
	static void UDestroyAllTextures();
private:
	static bool UCreateTexture(const char* filename, GLuint& textureId);
	static void IterateTextureVector(Enums::MeshType key, GLuint textureId);
	static void FlipImageVertically(unsigned char* image, int width, int height, int channels);
};

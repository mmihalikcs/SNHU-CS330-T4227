#include "TextureLoader.h"

std::map<Enums::MeshType, std::vector<GLuint>> TextureLoader::MeshTextureMap = {
    { Enums::MeshType::None, std::vector<GLuint>{ 0 } }
};

// Load Textures and add them to the map
void TextureLoader::LoadTextures()
{
    // Init
    GLuint textureId = 0;

    // Load texture for Plane
    const char* planeTexFilename = "../resources/textures/canal_water.jpg";
    if (!UCreateTexture(planeTexFilename, textureId))
    {
        std::cout << "Failed to load texture " << planeTexFilename << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
        perror(planeTexFilename);
    }
    // LoadTexture into map
    IterateTextureVector(Enums::MeshType::Plane, textureId);

    // Load texture for Canal Wall
    textureId = 0;
    const char* canalTexFilename = "../resources/textures/canal_wall.jpg";
    if (!UCreateTexture(canalTexFilename, textureId))
    {
        std::cout << "Failed to load texture " << canalTexFilename << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
        perror(canalTexFilename);
    }
    IterateTextureVector(Enums::MeshType::CanalWall, textureId);

    // Load texture for StreetLamp
    textureId = 0;
    const char* sLampTexFilename = "../resources/textures/smiley.png";
    if (!UCreateTexture(sLampTexFilename, textureId))
    {
        std::cout << "Failed to load texture " << sLampTexFilename << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
        perror(sLampTexFilename);
    }
    IterateTextureVector(Enums::MeshType::StreetLamp, textureId);

    /**************
    ** Buildings **
    ***************/

    // Load texture for Building #1
    textureId = 0;
    const char* buildingTexFilename1 = "../resources/textures/AmsterBuilding1.jpg";
    if (!UCreateTexture(buildingTexFilename1, textureId))
    {
        std::cout << "Failed to load texture " << buildingTexFilename1 << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
        perror(buildingTexFilename1);
    }
    IterateTextureVector(Enums::MeshType::Building, textureId);

    // Load texture for Building #2
    textureId = 0;
    const char* buildingTexFilename2 = "../resources/textures/AmsterBuilding2.jpg";
    if (!UCreateTexture(buildingTexFilename2, textureId))
    {
        std::cout << "Failed to load texture " << buildingTexFilename2 << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
        perror(buildingTexFilename2);
    }
    IterateTextureVector(Enums::MeshType::Building, textureId);

    // Load texture for Building #3
    textureId = 0;
    const char* buildingTexFilename3 = "../resources/textures/AmsterBuilding3.jpg";
    if (!UCreateTexture(buildingTexFilename3, textureId))
    {
        std::cout << "Failed to load texture " << buildingTexFilename3 << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
        perror(buildingTexFilename3);
    }
    IterateTextureVector(Enums::MeshType::Building, textureId);

    /***************
    ***** Tree *****
    ****************/

    // Load texture for Tree
    textureId = 0;
    const char* treeTexFilename = "../resources/textures/smiley.png";
    if (!UCreateTexture(treeTexFilename, textureId))
    {
        std::cout << "Failed to load texture " << treeTexFilename << std::endl;
        std::cout << "Reason: " << stbi_failure_reason() << std::endl;
        perror(treeTexFilename);
    }
    IterateTextureVector(Enums::MeshType::Tree, textureId);
}

// To support randomness, allow retrieve of random texture to apply to buildings/trees
GLuint TextureLoader::RetrieveTextureProgramId(Enums::MeshType key)
{
    // Init
    std::map<Enums::MeshType, std::vector<GLuint>>::iterator it;
    // Logic
    it = MeshTextureMap.find(key);
    if (it != MeshTextureMap.end())
    {
        std::vector<GLuint> vec = it->second;
        // Generate a random number between 0 and vec.size
        int randIndex = rand() % vec.size();
        return vec.at(randIndex);
    }
    else
    {
        throw std::exception("Unable to find texture program");
    }
}

// Destroys Texture based off given Id
void TextureLoader::UDestroyTexture(GLuint textureId)
{
    glGenTextures(1, &textureId);
}

// Destroys all Textures in the map file
void TextureLoader::UDestroyAllTextures()
{
    // Iterate through each pair to correctly delete textures
    for (std::pair<Enums::MeshType, std::vector<GLuint>> pair : MeshTextureMap)
    {
        // Walk down vector
        for (int i = 0; i < pair.second.size(); i++)
        {
            GLuint textureId = pair.second.at(i);
            UDestroyTexture(textureId);
        }
    }
    // Finally, clear the entire list
    MeshTextureMap.clear();
}


/*********************
****** PRIVATES ******
**********************/

/*Generate and load the texture*/
bool TextureLoader::UCreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        FlipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            std::cout << "Not implemented to handle image with " << channels << " channels" << std::endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return true;
    }

    // Error loading the image
    return false;
}

// Used to contain repeated logic in LoadTextures
void TextureLoader::IterateTextureVector(Enums::MeshType key, GLuint textureId)
{
    // Init
    std::map<Enums::MeshType, std::vector<GLuint>>::iterator it;
    // Logic
    it = MeshTextureMap.find(key);
    // If we found something - add to the vector
    if (it != MeshTextureMap.end())
    {
        // Add the item to the vector
        it->second.push_back(textureId);
    }
    else // Otherwise normal insertion
    {
        MeshTextureMap.insert(std::pair<Enums::MeshType, std::vector<GLuint>>(key, std::vector<GLuint>{ textureId }));
    }
}

// Images are loaded with Y axis going down, but OpenGL's Y axis goes up, so let's flip it
void TextureLoader::FlipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}
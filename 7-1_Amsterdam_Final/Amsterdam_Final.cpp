#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <string>
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library
#define STB_IMAGE_IMPLEMENTATION

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"  // Camera class
#include <map>

// Custom Files
#include "Enums.h"
#include "GeometricCoords.h"
#include "TextureLoader.h"

using namespace std; // Standard namespace

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

// Unnamed namespace
namespace
{
    const char* const WINDOW_TITLE = "Michael Mihalik - Final Project"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // Stores the GL data relative to a given mesh
    class GLMesh
    {
    public:
        GLuint vao;                 // Handle for the vertex array object
        GLuint vbo;                 // Handle for the vertex buffer object
        GLuint nVertices;           // Number of vertex of the mesh
        GLuint textureId;           // TexutureId we have been assigned
        Enums::MeshType type;         // Type of object being drawn
        glm::vec3 objectPosition;   // Translation of the object in space
        glm::vec3 objectScale;      // Scale of object in space
        glm::vec2 uvScale;          // Scale of texture in space
    };

    class GLLight
    {
    public:
        GLuint shaderProgramId;     // Shader Program Id
        glm::vec3 objectPosition;   // Translation of the object in space
        glm::vec3 objectScale;      // Scale of the object in space
        glm::vec3 color;            // Color of the lamp
        float strength;             // Strength of the lamp
    };
    
    // Main GLFW window
    GLFWwindow* gWindow = nullptr;
    
    // Data Mesh Object
    vector<GLMesh> gMeshCollection{ 
        { 0, 0, 0, 0, Enums::MeshType::Plane, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), glm::vec2(5.0f, 5.0f) },
        { 0, 0, 0, 0, Enums::MeshType::CanalWall, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), glm::vec2(5.0f, 5.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Building, glm::vec3(-1.60f, 0.50f, -0.80f), glm::vec3(2.0f, 2.0f, 2.0f), glm::vec2(1.0f, 1.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Building, glm::vec3(-0.96f, 0.50f, -0.80f), glm::vec3(2.0f, 1.7f, 2.0f), glm::vec2(1.0f, 1.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Building, glm::vec3(-0.32f, 0.50f, -0.80f), glm::vec3(2.0f, 1.9f, 2.0f), glm::vec2(1.0f, 1.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Building, glm::vec3(0.32f, 0.50f, -0.80f), glm::vec3(2.0f, 2.1f, 2.0f), glm::vec2(1.0f, 1.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Building, glm::vec3(0.96f, 0.50f, -0.80f), glm::vec3(2.0f, 1.5f, 2.0f), glm::vec2(1.0f, 1.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Building, glm::vec3(1.60f, 0.50f, -0.80f), glm::vec3(2.0f, 1.7f, 2.0f), glm::vec2(1.0f, 1.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Tree, glm::vec3(-1.80f, 0.5f, 0.75f), glm::vec3(0.40f), glm::vec2(5.0f, 5.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Tree, glm::vec3(0.0f, 0.5f, 0.75f), glm::vec3(0.40f), glm::vec2(5.0f, 5.0f) },
        { 0, 0, 0, 0, Enums::MeshType::Tree, glm::vec3(1.80f, 0.5f, 0.75f), glm::vec3(0.40f), glm::vec2(5.0f, 5.0f) },
        { 0, 0, 0, 0, Enums::MeshType::StreetLamp, glm::vec3(-1.0f, 1.0f, 0.25f), glm::vec3(0.40f), glm::vec2(5.0f, 5.0f) }
    };

    // Light Controls
    vector<GLLight> gLightCollection{
        { 0, glm::vec3(1.5f, 0.5f, 3.0f), glm::vec3(0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f},
        { 0, glm::vec3(2.5f, 1.5f, 4.0f), glm::vec3(0.3f), glm::vec3(1.0f, 1.0f, 0.0f), 0.6f},
        { 0, glm::vec3(-1.5f, 0.5f, -3.0f), glm::vec3(0.3f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f}
    };

    // Shader programs
    GLuint SceneProgramId;

    // camera
    Camera gCamera(glm::vec3(0.0f, 3.0f, 6.0f));
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    glm::mat4 _Projection;
    bool gFirstMouse = true;

    // timing
    float gDeltaTime = 0.0f; // time between current frame and last frame
    float gLastFrame = 0.0f;

    // Perspective flag
    bool perspectiveMode = true;
}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void UCreateMesh(GLMesh& mesh);
void UDestroyMesh(GLMesh& mesh);
void URender();
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);
void SwitchPerspective();

/********************************************
**************** SHADERS ********************
********************************************/

/* Cube Vertex Shader Source Code*/
const GLchar* cubeVertexShaderSource = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
layout(location = 1) in vec3 normal; // VAP position 1 for normals
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal; // For outgoing normals to fragment shader
out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
out vec2 vertexTextureCoordinate;

//Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

    vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

    vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
    vertexTextureCoordinate = textureCoordinate;
}
);


/* Cube Fragment Shader Source Code*/
const GLchar* cubeFragmentShaderSource = GLSL(440,

    in vec3 vertexNormal; // For incoming normals
in vec3 vertexFragmentPos; // For incoming fragment position
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor; // For outgoing cube color to the GPU

// Uniform / Global variables for object color, light color, light position, and camera/view position
// Light 1
uniform vec3 lightColor1;
uniform vec3 lightPos1;
uniform float lightStrength1;
// Light 2
uniform vec3 lightColor2;
uniform vec3 lightPos2;
uniform float lightStrength2;
// Light 3
uniform vec3 lightColor3;
uniform vec3 lightPos3;
uniform float lightStrength3;

// Camera and Texture
uniform vec3 viewPosition;
uniform sampler2D uTexture; // Useful when working with multiple textures
uniform vec2 uvScale;

vec3 CalcPointLight(vec3 lightPos, vec3 lightColor, float lightStrength, vec3 vertexFragmentPos, vec3 viewPosition)
{
    /*Phong lighting model calculations to generate ambient, diffuse, and specular components*/

    //Calculate Ambient lighting*/
    vec3 ambient = lightStrength * lightColor; // Generate ambient light color

    //Calculate Diffuse lighting*/
    vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
    vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on cube
    float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
    vec3 diffuse = impact * lightColor; // Generate diffuse light color

    //Calculate Specular lighting*/
    float specularIntensity = 0.8f; // Set specular light strength
    float highlightSize = 16.0f; // Set specular highlight size
    vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
    vec3 reflectDir = reflect(-lightDirection, norm);// Calculate reflection vector
    //Calculate specular component
    float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
    vec3 specular = specularIntensity * specularComponent * lightColor;
    // Return
    return (ambient + diffuse + specular);
}
void main()
{
    // define an output color value
    vec3 result = vec3(0.0);

    // Texture holds the color to be used for all three components
    vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

    // Calculate phong result for both lamps
    result += CalcPointLight(lightPos1, lightColor1, lightStrength1, vertexFragmentPos, viewPosition) * textureColor.xyz;
    result += CalcPointLight(lightPos2, lightColor2, lightStrength2, vertexFragmentPos, viewPosition) * textureColor.xyz;
    result += CalcPointLight(lightPos3, lightColor3, lightStrength3, vertexFragmentPos, viewPosition) * textureColor.xyz;

    // Send results to GPU
    fragmentColor = vec4(result, 1.0); // Send lighting results to GPU
}
);


/* Lamp Shader Source Code*/
const GLchar* lampVertexShaderSource = GLSL(440,

    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data

        //Uniform / Global variables for the  transform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates
}
);


/* Fragment Shader Source Code*/
const GLchar* lampFragmentShaderSource = GLSL(440,

    out vec4 fragmentColor; // For outgoing lamp color (smaller cube) to the GPU

void main()
{
    fragmentColor = vec4(1.0f); // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
}
);


/********************************************
*************** FUNCTIONS *******************
********************************************/
int main(int argc, char* argv[])
{
    // Initialize Time
    srand(time(0));

    // Program start
    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create the mesh
    for (int i = 0; i < gMeshCollection.size(); i++)
    {
        // Calls the function to create the Vertex Buffer Object
        UCreateMesh(gMeshCollection[i]);
    }

    // Create the shader program
    if (!UCreateShaderProgram(cubeVertexShaderSource, cubeFragmentShaderSource, SceneProgramId))
        return EXIT_FAILURE;

    for (int i = 0; i < gLightCollection.size(); i++)
    {
        if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLightCollection[i].shaderProgramId))
            return EXIT_FAILURE;


    }

    // Load texture
    TextureLoader::LoadTextures();

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(SceneProgramId);
    // We set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(SceneProgramId, "uTexture"), 0);

    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // per-frame timing
        // --------------------
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // input
        // -----
        UProcessInput(gWindow);

        // Render this frame
        URender();

        glfwPollEvents();
    }

    // Release mesh data
    for (int i = 0; i < gMeshCollection.size(); i++)
    {
        // Calls the function to create the Vertex Buffer Object
        UDestroyMesh(gMeshCollection[i]);
    }

    // Release textures
    TextureLoader::UDestroyAllTextures();
    // Release shader programs
    UDestroyShaderProgram(SceneProgramId);
    // Destroy Lamps
    for (const GLLight light : gLightCollection) {
        UDestroyShaderProgram(light.shaderProgramId);
    }

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    static const float cameraSpeed = 2.5f;

    // Escape to close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Add stubs for W/A/S/D Left, Right, Forward, Backward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);

    // Add stubs for Q/E Upward/Downward movement
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.ProcessKeyboard(UP, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.ProcessKeyboard(DOWN, gDeltaTime);

    // Add stubs to change view
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        // Reset the flag
        if (perspectiveMode)
            perspectiveMode = false;
        else
            perspectiveMode = true;
    }
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Add 1/Remove 1 depending on direction
    float newMovementSpeed = yoffset > 0 ? gCamera.MovementSpeed + 1 : gCamera.MovementSpeed - 1;
    // Set the movement speed. Check if its attempting to go negative, which reverses the control scheme
    gCamera.MovementSpeed = newMovementSpeed > 0 ? newMovementSpeed : 0.5;
}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        if (action == GLFW_PRESS)
            cout << "Left mouse button pressed" << endl;
        else
            cout << "Left mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
    {
        if (action == GLFW_PRESS)
            cout << "Middle mouse button pressed" << endl;
        else
            cout << "Middle mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_RIGHT:
    {
        if (action == GLFW_PRESS)
            cout << "Right mouse button pressed" << endl;
        else
            cout << "Right mouse button released" << endl;
    }
    break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}

// Function called to render a frame
// --------------------------------
void SwitchPerspective()
{
    // Return the correct perspective
    if (perspectiveMode)
    {
        // Perspective
        _Projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    }
    else
    {
        // Org
        _Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
    }
}

// Functioned called to render a frame
void URender()
{
    // Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // Clear the frame and z buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Init common variables
    glm::mat4 model, view = glm::mat4(0.0f);
    GLint modelLoc, viewLoc, projLoc;

    // Activate the cube VAO (used by cube and lamp)
    for (int i = 0; i < gMeshCollection.size(); i++)
    {
        glBindVertexArray(gMeshCollection[i].vao);

        // CUBE: draw cube
        //----------------
        // Set the shader to be used
        glUseProgram(SceneProgramId);

        // Model matrix: transformations are applied right-to-left order
        model = glm::translate(gMeshCollection[i].objectPosition) * glm::scale(gMeshCollection[i].objectScale);

        // camera/view transformation
        view = gCamera.GetViewMatrix();

        // Set camera initial mode
        SwitchPerspective();

        // Retrieves and passes transform matrices to the Shader program
        modelLoc = glGetUniformLocation(SceneProgramId, "model");
        viewLoc = glGetUniformLocation(SceneProgramId, "view");
        projLoc = glGetUniformLocation(SceneProgramId, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_Projection));

        // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
        GLint lightColorLoc, lightPositionLoc, lightStrengthLoc;
        // Draw the lights
        for (int i = 0; i < gLightCollection.size(); i++)
        {
            // Light
            lightColorLoc = glGetUniformLocation(SceneProgramId, ("lightColor" + std::to_string(i + 1)).c_str());
            lightPositionLoc = glGetUniformLocation(SceneProgramId, ("lightPos" + std::to_string(i + 1)).c_str());
            lightStrengthLoc = glGetUniformLocation(SceneProgramId, ("lightStrength" + std::to_string(i + 1)).c_str());

            // Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
            glUniform3f(lightColorLoc, gLightCollection[i].color[0], gLightCollection[i].color[1], gLightCollection[i].color[2]);
            glUniform3f(lightPositionLoc, gLightCollection[i].objectPosition[0], gLightCollection[i].objectPosition[1], gLightCollection[i].objectPosition[2]);
            glUniform1f(lightStrengthLoc, gLightCollection[i].strength);
        }

        // View Position
        GLint viewPositionLoc = glGetUniformLocation(SceneProgramId, "viewPosition");

        // Camera
        const glm::vec3 cameraPosition = gCamera.Position;
        glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

        GLint UVScaleLoc = glGetUniformLocation(SceneProgramId, "uvScale");
        glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gMeshCollection[i].uvScale));

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);

        // Retrieve the loaded textureId from the map
        // Assigns it to the mesh to ensure the same one is used.
        if (gMeshCollection[i].textureId == 0) {
            gMeshCollection[i].textureId = TextureLoader::RetrieveTextureProgramId(gMeshCollection[i].type);
        }

        // Finish Binding the texture
        glBindTexture(GL_TEXTURE_2D, gMeshCollection[i].textureId);

        // Draws the triangles
        glDrawArrays(GL_TRIANGLES, 0, gMeshCollection[i].nVertices);
    }

    // Draw lamps
    for (int i = 0; i < gLightCollection.size(); i++) 
    {
        // LAMP: draw lamp
        //----------------
        glUseProgram(gLightCollection[i].shaderProgramId);

        //Transform the smaller cube used as a visual que for the light source
        model = glm::translate(gLightCollection[i].objectPosition) * glm::scale(gLightCollection[i].objectScale);

        // Reference matrix uniforms from the Lamp Shader program
        modelLoc = glGetUniformLocation(gLightCollection[i].shaderProgramId, "model");
        viewLoc = glGetUniformLocation(gLightCollection[i].shaderProgramId, "view");
        projLoc = glGetUniformLocation(gLightCollection[i].shaderProgramId, "projection");

        // Pass matrix data to the Lamp Shader program's matrix uniforms
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(_Projection));

        // DRAW - DEBUG
        //glDrawArrays(GL_TRIANGLES, 0, gMeshCollection[i].nVertices);
    }

    // Deactivate the Vertex Array Object and shader program
    glBindVertexArray(0);
    glUseProgram(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(gWindow);    // Flips the the back buffer with the front buffer every frame.
}


// Implements the UCreateMesh function
void UCreateMesh(GLMesh& mesh)
{
    // Init
    GLfloat verts[5000];
    GLushort indi[5000];

    // Switch for geometry
    switch (mesh.type)
    {
    case Enums::MeshType::Tree:
    {
        // Capture Output
        std::vector<GLfloat>* treeCoordsVec = GeometricCoords::GenerateTreeCoords();
        for (int i = 0; i < treeCoordsVec->size(); i++)
        {
            verts[i] = treeCoordsVec->at(i);
        }
        // Free
        delete(treeCoordsVec);
        break;
    }
    case Enums::MeshType::CanalWall:
    {
        // Capture Output
        std::vector<GLfloat>* canalCoordsVec = GeometricCoords::GenerateCanalWallCoords();
        for (int i = 0; i < canalCoordsVec->size(); i++)
        {
            verts[i] = canalCoordsVec->at(i);
        }
        // Free
        delete(canalCoordsVec);
        break;
    }
    case Enums::MeshType::Building:
    {
        // Capture Output
        std::vector<GLfloat>* buildingCoordsVec = GeometricCoords::GenerateBuildingCoords();
        for (int i = 0; i < buildingCoordsVec->size(); i++)
        {
            verts[i] = buildingCoordsVec->at(i);
        }
        // Free
        delete(buildingCoordsVec);
        break;
    }
    case Enums::MeshType::StreetLamp:
    {
        // Capture Output
        std::pair<std::vector<GLfloat>*, std::vector<GLushort>*> trashCanVec = GeometricCoords::GenerateStreetLampCoords();
        // Verts
        for (int i = 0; i < trashCanVec.first->size(); i++)
        {
            verts[i] = trashCanVec.first->at(i);
        }

        // Indexes
        for (int i = 0; i < trashCanVec.second->size(); i++)
        {
            indi[i] = trashCanVec.second->at(i);
        }

        // Free
        delete(trashCanVec.first);
        delete(trashCanVec.second);
        break;
    }
    case Enums::MeshType::Plane:
    {
        // Capture Output
        std::vector<GLfloat>* planeCoordsVec = GeometricCoords::GeneratePlaneCoords();
        for (int i = 0; i < planeCoordsVec->size(); i++)
        {
            verts[i] = planeCoordsVec->at(i);
        }
        // Free
        delete(planeCoordsVec);
        break;
    }
    case Enums::MeshType::None:
        default:
            break;
    };


    // Common Items?
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    // Calculate Verts
    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vbo);
}

// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}


void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}
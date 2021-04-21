#define _USE_MATH_DEFINES // for C++
#include <cmath>

#include "GeometricCoords.h"

std::vector<GLfloat>* GeometricCoords::GenerateTreeCoords()
{
    std::vector<GLfloat>* vec = new std::vector<GLfloat>{

        // Top of Tree
        //Positions          //Normals              //Texture Coords
        // ------------------------------------------------------
        //Bottom Face        //Negative Y Normal
        -0.5f, 1.40f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, 1.40f, -0.5f,     0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        0.5f, 1.40f, 0.5f,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        0.5f, 1.40f, 0.5f,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 1.40f, 0.5f,     0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, 1.40f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        //Front Face         //Positive Z Normal
        -0.5f, 1.40f, 0.5f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, 1.40f, 0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        0.0f, 2.40f, 0.0f,       0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        //Left Face          //Negative X Normal
        -0.5f, 1.40f, 0.5f,     -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 2.40f, 0.0f,       -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 1.40f, -0.5f,    -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        //Right Face         //Positive X Normal
        0.5f, 1.40f, -0.5f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.5f, 1.40f, 0.5f,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        0.0f, 2.40f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        //Back Face          //Negative Z Normal 
        -0.5f, 1.40f, -0.5f,    0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, 1.40f, -0.5f,     0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        0.0f, 2.40f, 0.0f,       0.0f, 0.0f, -1.0f,  1.0f, 1.0f,

        // Middle of Tree
        //Positions          //Normals              //Texture Coords
        // ------------------------------------------------------
        //Bottom Face        //Negative Y Normal
        -0.5f, 0.70f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, 0.70f, -0.5f,     0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        0.5f, 0.70f, 0.5f,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        0.5f, 0.70f, 0.5f,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 0.70f, 0.5f,     0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, 0.70f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        //Front Face         //Positive Z Normal
        -0.5f, 0.70f, 0.5f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, 0.70f, 0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        0.0f, 1.70f, 0.0f,       0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        //Left Face          //Negative X Normal
        -0.5f, 0.70f, 0.5f,     -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 1.70f, 0.0f,       -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 0.70f, -0.5f,    -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        //Right Face         //Positive X Normal
        0.5f, 0.70f, -0.5f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.5f, 0.70f, 0.5f,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        0.0f, 1.70f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        //Back Face          //Negative Z Normal 
        -0.5f, 0.70f, -0.5f,    0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, 0.70f, -0.5f,     0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        0.0f, 1.70f, 0.0f,       0.0f, 0.0f, -1.0f,  1.0f, 1.0f,

        // Trunk of the tree
        // Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
        -0.15f, 0.0f, -0.15f,   0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        0.15f, 0.0f, -0.15f,    0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        0.15f, 0.75f, -0.15f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
        0.15f, 0.75f, -0.15f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
        -0.15f, 0.75f, -0.15f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
        -0.15f, 0.0f, -0.15f,   0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        //Front Face         //Positive Z Normal
        -0.15f, 0.0f,  0.15f,   0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
        0.15f, 0.0f,  0.15f,    0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
        0.15f, 0.75f,  0.15f,   0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
        0.15f, 0.75f,  0.15f,   0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
        -0.15f, 0.75f,  0.15f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
        -0.15f, 0.0f,  0.15f,   0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
        //Left Face          //Negative X Normal
        -0.15f, 0.75f,  0.15f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.15f, 0.75f, -0.15f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.15f, 0.0f, -0.15f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.15f, 0.0f, -0.15f,   -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.15f, 0.0f,  0.15f,   -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.15f, 0.75f,  0.15f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        //Right Face         //Positive X Normal
        0.15f, 0.75f, 0.15f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        0.15f, 0.75f, -0.15f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.15f, 0.0f, -0.15f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        0.15f, 0.0f, -0.15f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        0.15f, 0.0f,  0.15f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        0.15f, 0.75f, 0.15f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        //Bottom Face        //Negative Y Normal
        -0.15f, 0.0f, -0.15f,   0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.15f, 0.0f, -0.15f,    0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        0.15f, 0.0f, 0.15f,     0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        0.15f, 0.0f, 0.15f,     0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -0.15f, 0.0f, 0.15f,    0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -0.15f, 0.0f, -0.15f,   0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        //Top Face           //Positive Y Normal
        -0.15f, 0.75f, -0.15f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        0.15f, 0.75f, -0.15f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        0.15f, 0.75f, 0.15f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        0.15f, 0.75f, 0.15f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.15f, 0.75f, 0.15f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -0.15f, 0.75f, -0.15f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f

    };
    return vec;
}

std::vector<GLfloat>* GeometricCoords::GenerateCanalWallCoords()
{
    std::vector<GLfloat>* vec = new std::vector<GLfloat>{
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal    //Texture Coords.
        -1.0f, 0.0f, -1.0f,     0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
        1.0f, 0.0f, -1.0f,      0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
        1.0f, 0.25f, -1.0f,     0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
        1.0f, 0.25f, -1.0f,     0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
        -1.0f, 0.25f, -1.0f,    0.0f, 0.0f, -1.0f,   0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,     0.0f, 0.0f, -1.0f,   0.0f, 0.0f,

        //Front Face         //Positive Z Normal
        -1.0f, 0.0f, 0.5f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        1.0f, 0.0f,  0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        1.0f, 0.25f, 0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        1.0f, 0.25f, 0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, 0.25f, 0.5f,     0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, 0.0f, 0.5f,      0.0f, 0.0f, 1.0f,   0.0f, 0.0f,

        //Left Face          //Negative X Normal
        -1.0f, 0.25f, 0.5f,    -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -1.0f, 0.25f, -1.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,    -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,    -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -1.0f, 0.0f,  0.5f,    -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -1.0f, 0.25f, 0.5f,    -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,

        //Right Face         //Positive X Normal
        1.0f, 0.25f, 0.5f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        1.0f, 0.25f, -1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        1.0f, 0.0f, -1.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        1.0f, 0.0f,  0.5f,     1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
        1.0f, 0.25f, 0.5f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f,

        //Bottom Face        //Negative Y Normal
        -1.0f, 0.0f, -1.0f,    0.0f, -1.0f, 0.0f,   0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,     0.0f, -1.0f, 0.0f,   1.0f, 1.0f,
        1.0f, 0.0f, 0.5f,      0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
        1.0f, 0.0f, 0.5f,      0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
        -1.0f, 0.0f, 0.5f,     0.0f, -1.0f, 0.0f,   0.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,    0.0f, -1.0f, 0.0f,   0.0f, 1.0f,

        //Top Face           //Positive Y Normal
        -1.0f, 0.25f, -1.0f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
        1.0f, 0.25f, -1.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
        1.0f, 0.25f,  0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        1.0f, 0.25f,  0.5f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -1.0f, 0.25f,  0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
        -1.0f, 0.25f, -1.0f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f
    };
    return vec;
}


std::vector<GLfloat>* GeometricCoords::GenerateBuildingCoords()
{
    std::vector<GLfloat>* vec = new std::vector<GLfloat>{
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
        -0.15f, 0.0f, -0.15f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.15f, 0.0f, -0.15f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.15f,  1.1f, -0.15f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.15f,  1.1f, -0.15f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.15f,  1.1f, -0.15f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.15f, 0.0f, -0.15f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        //Front Face         //Positive Z Normal
        -0.15f, 0.0f,  0.15f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        0.15f, 0.0f,  0.15f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
        0.15f,  1.1f,  0.15f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        0.15f,  1.1f,  0.15f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.15f,  1.1f,  0.15f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.15f, 0.0f,  0.15f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        //Left Face          //Negative X Normal
        -0.15f,  1.1f,  0.15f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.15f,  1.1f, -0.15f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.15f, 0.0f, -0.15f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.15f, 0.0f, -0.15f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.15f, 0.0f,  0.15f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.15f,  1.1f,  0.15f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

        //Right Face         //Positive X Normal
        0.15f,  1.1f,  0.15f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.15f,  1.1f, -0.15f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.15f, 0.0f, -0.15f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.15f, 0.0f, -0.15f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.15f, 0.0f,  0.15f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.15f,  1.1f,  0.15f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

        //Bottom Face        //Negative Y Normal
        -0.15f, 0.0f, -0.15f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        0.15f, 0.0f, -0.15f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        0.15f, 0.0f,  0.15f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        0.15f, 0.0f,  0.15f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.15f, 0.0f,  0.15f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.15f, 0.0f, -0.15f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,

        //Top Face           //Positive Y Normal
        -0.15f,  1.1f, -0.15f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        0.15f,  1.1f, -0.15f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        0.15f,  1.1f,  0.15f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        0.15f,  1.1f,  0.15f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.15f,  1.1f,  0.15f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.15f,  1.1f, -0.15f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
    };
    return vec;
}

std::pair<std::vector<GLfloat>*, std::vector<GLushort>*> GeometricCoords::GenerateStreetLampCoords()
{

    /*
    std::vector<GLfloat>* vec = new std::vector<GLfloat>{
        // Base
        //Positions          //Normals              //Texture Coords
        // ------------------------------------------------------
        //Bottom Face        //Negative Y Normal
        -0.5f, 0.0f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        0.5f, 0.0f, -0.5f,     0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
        0.5f, 0.0f, 0.5f,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        0.5f, 0.0f, 0.5f,      0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 0.0f, 0.5f,     0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
        //Front Face         //Positive Z Normal
        -0.5f, 0.0f, 0.5f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, 0.0f, 0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        //Left Face          //Negative X Normal
        -0.5f, 0.0f, 0.5f,     -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,       -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,    -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        //Right Face         //Positive X Normal
        0.5f, 0.0f, -0.5f,     1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.5f, 0.0f, 0.5f,      1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        //Back Face          //Negative Z Normal 
        -0.5f, 0.0f, -0.5f,    0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, 0.0f, -0.5f,     0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.0f, 0.0f, -1.0f,  1.0f, 1.0f

        // Pole
        //Positions          //Normals              //Texture Coords
        // ------------------------------------------------------


    };
    */
    // Init
    std::vector<GLushort>* sphereIndicies = new std::vector<GLushort>();
    // Add the post
    std::vector<GLfloat>* sphereVertex = new std::vector<GLfloat>{
        // Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
        -0.05f, -0.95f, -0.05f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.05f, -0.95f, -0.05f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.05f, -0.10f, -0.05f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.05f, -0.10f, -0.05f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.05f, -0.10f, -0.05f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.05f, -0.95f, -0.05f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        //Front Face         //Positive Z Normal
        -0.05f, -0.95f, 0.05f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.05f, -0.95f, 0.05f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.05f, -0.10f, 0.05f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.05f, -0.10f, 0.05f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.05f, -0.10f, 0.05f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.05f, -0.95f, 0.05f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        //Left Face          //Negative X Normal
        -0.05f, -0.10f, 0.05f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.05f, -0.10f, -0.05f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.05f, -0.95f, -0.05f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.05f, -0.95f, -0.05f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.05f, -0.95f, 0.05f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.05f, -0.10f, 0.05f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        //Right Face         //Positive X Normal
        0.05f, -0.10f, 0.05f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.05f, -0.10f, -0.05f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.05f, -0.95f, -0.05f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.05f, -0.95f, -0.05f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.05f, -0.95f, 0.05f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.05f, -0.10f, 0.05f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        //Bottom Face        //Negative Y Normal
        -0.05f, -0.95f, -0.05f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.05f, -0.95f, -0.05f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.05f, -0.95f, 0.05f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.05f, -0.95f, 0.05f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.05f, -0.95f, 0.05f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.05f, -0.95f, -0.05f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        //Top Face           //Positive Y Normal
        -0.05f, -0.10f, -0.05f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.05f, -0.10f, -0.05f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.05f, -0.10f, 0.05f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.05f, -0.10f, 0.05f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.05f, -0.10f, 0.05f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.05f, -0.10f, -0.05f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    BuildSphere(0.25f, 12, 24, *sphereVertex, *sphereIndicies);
    return std::pair<std::vector<GLfloat>*, std::vector<GLushort>*>(sphereVertex, sphereIndicies);
}

std::vector<GLfloat>* GeometricCoords::GeneratePlaneCoords()
{
    std::vector<GLfloat>* vec = new std::vector<GLfloat>{
        //Positions          //Normals                  //Texture Coords
        // ------------------------------------------------------
        //Bottom Face        //Negative Y Normal
        -1.0f, 0.0f, -1.0f,    0.0f, -1.0f, 0.0f,      0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,     0.0f, -1.0f, 0.0f,      1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,      0.0f, -1.0f, 0.0f,      1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,      0.0f, -1.0f, 0.0f,      1.0f, 0.0f,
        -1.0f, 0.0f, 1.0f,     0.0f, -1.0f, 0.0f,      0.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,    0.0f, -1.0f, 0.0f,      0.0f, 1.0f,
    };
    return vec;
}

void GeometricCoords::BuildSphere(float radius, unsigned int rings, unsigned int sectors, std::vector<GLfloat>& sphereCoords, std::vector<GLushort>& sphereIndices)
{
    float const R = 1. / (float)(rings - 1);
    float const S = 1. / (float)(sectors - 1);
    int r, s;

    for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) 
    {
        float const y = sin(-M_PI_2 + M_PI * r * R);
        float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
        float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

        // Compute
        // Vertex
        sphereCoords.push_back(x * radius);
        sphereCoords.push_back(y * radius);
        sphereCoords.push_back(z * radius);

        // Normal
        sphereCoords.push_back(x);
        sphereCoords.push_back(y);
        sphereCoords.push_back(z );

        // Texture
        sphereCoords.push_back(s * S);
        sphereCoords.push_back(r * R);
    }

    sphereIndices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = sphereIndices.begin();
    for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
        *i++ = r * sectors + s;
        *i++ = r * sectors + (s + 1);
        *i++ = (r + 1) * sectors + (s + 1);
        *i++ = (r + 1) * sectors + s;
    }
}
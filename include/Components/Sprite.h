#ifndef _ROC_SPRITE_COMPONENT_H_
#define _ROC_SPRITE_COMPONENT_H_

#include <string>

#include "Coordinator.h"

#include <glad/gl.h>

#include "Roc_GL/Shader.hpp"
#include "Roc_GL/Texture.hpp"
#include "Roc_GL/CoordinateSystem.hpp"

// class Sprite : public Component {
// public:
//     static std::string name() { return "Sprite"; }
//     friend class RenderSpriteSystem;

//     std::string texture_key = "";
//     std::string shader_key = "";

//     double offsetX = 0, offsetY = 0;
//     double width = 0.0, height = 0.0;

//     void SetOutputData(double thisx, double thisy);

//     void DestroyComponent() override;

// private:
//     GLuint VBO;
//     GLdouble vertices[30] = {
//             /// positions   /// texture positions
//             0, 0, 0.0f,     1.0f, 0.0f, // top right
//             0, 0, 0.0f,     0.0f, 0.0f, // top left
//             0, 0, 0.0f,     0.0f, 1.0f, // bottom left
//             0, 0, 0.0f,     1.0f, 0.0f, // top right
//             0, 0, 0.0f,     0.0f, 1.0f, // bottom left
//             0, 0, 0.0f,     1.0f, 1.0f  // bottom right
//         };

// };

ROCKET_COMPONENT(Sprite,
    ROCKET_RAW(friend class RenderSpriteSystem;)

    ROCKET_PROPERTY_DEFVAL(public, std::string, texture_key, "")
    ROCKET_PROPERTY_DEFVAL(public, std::string, shader_key, "")

    ROCKET_PROPERTY_DEFVAL(public, double, offsetX, 0.0)
    ROCKET_PROPERTY_DEFVAL(public, double, offsetY, 0.0)
    ROCKET_PROPERTY_DEFVAL(public, double, width, 0.0)
    ROCKET_PROPERTY_DEFVAL(public, double, height, 0.0)

    ROCKET_RAW(public: void SetOutputData(double thisx, double thisy);)
    ROCKET_RAW(public: void DestroyComponent() override;)

    ROCKET_PROPERTY_DEFVAL(private, unsigned int, VBO, 0)
    
    ROCKET_RAW(private: double vertices[30] = {
        /// positions   /// texture positions
        0, 0, 0.0f,     1.0f, 0.0f, // top right
        0, 0, 0.0f,     0.0f, 0.0f, // top left
        0, 0, 0.0f,     0.0f, 1.0f, // bottom left
        0, 0, 0.0f,     1.0f, 0.0f, // top right
        0, 0, 0.0f,     0.0f, 1.0f, // bottom left
        0, 0, 0.0f,     1.0f, 1.0f  // bottom right
    };)
);

#endif
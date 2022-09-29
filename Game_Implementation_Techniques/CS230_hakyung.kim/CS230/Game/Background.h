/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.h
Purpose: Background header file
Project: CS230
Author: Kevin Wright
Creation date: 3/25/2020
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include <vector>

#include "../Engine/BasicDataTypes.h" //Rect
#include "../Engine/Component.h" //Rect

struct Vector2D;
class Texture;

class Background : public Component {
public:
    Background();
    void Add(const std::string &texturePath, int level);
    void Draw(Vector2D cameraPos);
private:
    struct ParallaxInfo {
        Texture *texturePtr;
        int level;
    };
    std::vector<ParallaxInfo> backgrounds;
};
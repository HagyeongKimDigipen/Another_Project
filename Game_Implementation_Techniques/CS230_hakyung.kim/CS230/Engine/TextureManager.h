/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Purpose: Header file for Teexture Manager
Project: CS230
Author: Kevin Wright
Creation date: 5/18/2020
-----------------------------------------------------------------*/

#pragma once
#include <string>
#include <map>

class Texture;

class TextureManager {
public:
	Texture* Load(const std::string& filePath);
	void Unload();

private:
	std::map<std::string, Texture*> pathToTexture;
};


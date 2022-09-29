/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Purpose: Source file for Texture Manager
Project: CS230
Author: Kevin Wright
Creation date: 5/18/2020
-----------------------------------------------------------------*/
#include "Engine.h"
#include "Texture.h"
#include "TextureManager.h"


Texture* TextureManager::Load(const std::string& filePath) {
	if (pathToTexture.find(filePath) == pathToTexture.end()) {
		pathToTexture[filePath] = new Texture(filePath);
	}
	return pathToTexture[filePath];
}

void TextureManager::Unload() {
	Engine::GetLogger().LogEvent("Clear Textures");
	for (std::pair<std::string, Texture*> texturePtr : pathToTexture) {
		delete texturePtr.second;
	}
	pathToTexture.clear();
}

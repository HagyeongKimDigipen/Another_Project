/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Purpose: Background source file
Project: CS230
Author: Kevin Wright
Creation date: 3/25/2020
-----------------------------------------------------------------*/
#include "Background.h"

#include "../Engine/Engine.h"			//Engine::GetWindow
#include "../Engine/TransformMatrix.h"	//TranslateMatrix
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"

Background::Background() {}

void Background::Add(const std::string& texturePath, int level) {
	backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath), level });
	if (level == 1) {
		RectInt cameraRange;
		cameraRange.bottomLeft = { 0, 0 };
		cameraRange.topRight = backgrounds.back().texturePtr->GetSize() - Engine::GetWindow().GetSize();

		Camera* ptr = Engine::GetGameStateManager().GetComponent<Camera>();
		ptr->SetCameraRange(cameraRange);
	}
}

void Background::Draw(Vector2D camera) {
	for (ParallaxInfo& levelInfo : backgrounds) {
		levelInfo.texturePtr->Draw(TranslateMatrix(-Vector2D{ camera.x / levelInfo.level, camera.y }));
	}
}
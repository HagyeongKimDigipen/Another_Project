/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Purpose: header file for Sprite Module
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/

#pragma once
#include <string>
#include <vector>				//std::vector
#include "BasicDataTypes.h"		//Vector2DInt
#include "Animation.h"

class TransformMatrix;
class GameObject;
class Texture;

class Sprite {
public:
	Sprite();
	~Sprite();
	void Load(std::string spriteFilePath, GameObject* object);
	void Update(double dt);
	void Draw(TransformMatrix displayMatrix);
	void PlayAnimation(int anim);
	bool IsAnimationDone();
	void AddHotSpot(Vector2DInt position);
	Vector2DInt GetHotSpot(int index);
	Vector2DInt GetFrameSize() const;
	Vector2DInt GetFrameTexel(int frameNum) const;
private:
	Texture *texturePtr;
	int currAnim;
	Vector2DInt frameSize;
	std::vector<Vector2DInt> frameTexel;
	std::vector<Animation*> animations;
	std::vector<Vector2DInt> hotSpots;
};


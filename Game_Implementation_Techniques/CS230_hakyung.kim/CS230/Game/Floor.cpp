/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.cpp
Purpose: Floor source file
Project: CS230
Author: Kevin Wright
Creation date: 5/4/2020
-----------------------------------------------------------------*/

#include "..\Engine\Collision.h"
#include "GameObjectTypes.h"
#include "Floor.h"

Floor::Floor(RectInt rect) : GameObject(rect.bottomLeft) {
	AddComponent(new RectCollision({ { 0, 0 }, {rect.topRight - rect.bottomLeft} }, this));
}

void Floor::Update(double) {}

void Floor::Draw(TransformMatrix) {}

std::string Floor::GetObjectTypeName() { 
	return "Floor"; 
}

GameObjectType Floor::GetObjectType() { 
	return GameObjectType::Floor; 
}

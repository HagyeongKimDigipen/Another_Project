/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Purpose: Camera header file
Project: CS230
Author: Kevin Wright
Creation date: 6/6/2020
-----------------------------------------------------------------*/
#pragma once

#include "Component.h"
#include "BasicDataTypes.h" //Vector2D rect

class GameObject;
class TransformMatrix;

class Camera : public Component {
public:
	Camera(GameObject* followObject, Vector2D position);
	Vector2D GetCameraPosition();
	void Update();
	TransformMatrix &GetCameraMatrix();
	void SetCameraRange(RectInt newCameraRange);
private:
	static const double cameraPlayerMoveRange;

	TransformMatrix cameraMatrix;
	RectInt cameraRange;
	GameObject* followObject;
	Vector2D cameraPos;
};
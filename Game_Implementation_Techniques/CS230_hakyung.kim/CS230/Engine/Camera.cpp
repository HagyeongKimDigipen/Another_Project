/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Purpose: Camera source file
Project: CS230
Author: Kevin Wright
Creation date: 6/6/2020
-----------------------------------------------------------------*/

#include "TransformMatrix.h"
#include "Engine.h"
#include "Camera.h"

const double Camera::cameraPlayerMoveRange = .35;

Camera::Camera(GameObject* followObject, Vector2D position) : followObject(followObject), cameraPos(position), cameraRange({ { 0,0 }, { 0,0 } }) {}

Vector2D Camera::GetCameraPosition() { return cameraPos; }

void Camera::Update() {
	if (followObject == nullptr) {
		return;
	}

	double cameraDistance = Engine::GetWindow().GetSize().x * Camera::cameraPlayerMoveRange;
	if (followObject->GetPosition().x - cameraPos.x > cameraDistance) {
		cameraPos.x = followObject->GetPosition().x - cameraDistance;
	}

	if (cameraPos.x < cameraRange.bottomLeft.x) {
		cameraPos.x = cameraRange.bottomLeft.x;
	}
	if (cameraPos.x > cameraRange.topRight.x) {
		cameraPos.x = cameraRange.topRight.x;
	}
	if (cameraPos.y < cameraRange.bottomLeft.y) {
		cameraPos.y = cameraRange.bottomLeft.y;
	}
	if (cameraPos.y > cameraRange.topRight.y) {
		cameraPos.y = cameraRange.topRight.y;
	}
	cameraMatrix = TranslateMatrix(-cameraPos);

	// Boundary Check
	if (followObject->GetPosition().x < cameraPos.x + followObject->GetSprite().GetFrameSize().x / 2) {
		followObject->SetPositionX(cameraPos.x + followObject->GetSprite().GetFrameSize().x / 2);
	}
	if (followObject->GetPosition().x + followObject->GetSprite().GetFrameSize().x / 2 > cameraPos.x + Engine::GetWindow().GetSize().x) {
		followObject->SetPositionX(cameraPos.x + Engine::GetWindow().GetSize().x - followObject->GetSprite().GetFrameSize().x / 2);
	}
}

void Camera::SetCameraRange(RectInt newCameraRange) {
	cameraRange = newCameraRange;
}

TransformMatrix &Camera::GetCameraMatrix() {
	return cameraMatrix;
}
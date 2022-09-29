/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Purpose: Header file for Ship
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\Input.h"		//Input::InputKey
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Ship : public GameObject {
public:
	Ship(Vector2D startPos);
	void Update(double dt);
	void Draw(TransformMatrix displayMatrix);

	GameObjectType GetObjectType() override { return GameObjectType::Ship; }
	std::string GetObjectTypeName() override { return "Ship"; }
	bool CanCollideWith(GameObjectType collideAgainstType) override;
	void ResolveCollision(GameObject* collidedWith);

	bool IsDead() { return isDead; }
private:
	Sprite flameLeft;
	Sprite flameRight;
	bool isAccelerating;
	bool isDead;

	static const double accel;
	static const double drag;
	static const double maxVel;
	static const double rotationRate;

	Input::InputKey fireLazerKey;
	Input::InputKey rotateCounterKey;
	Input::InputKey rotateClockKey;
	Input::InputKey accelerateKey;
};
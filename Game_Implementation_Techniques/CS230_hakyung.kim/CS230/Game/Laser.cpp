/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.cpp
Purpose: Laser source file
Project: CS230
Author: Kevin Wright
Creation date: 5/27/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "Laser.h"
#include "GameObjectTypes.h"

Laser::Laser(Vector2D pos, double rotation, Vector2D scale, Vector2D newVelocity) : GameObject(pos, rotation, scale) {
	velocity = newVelocity;
	sprite.Load("assets/Laser.spt", this); 
}

void Laser::Update(double dt) {
	GameObject::Update(dt);

	if (GetPosition().y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0) {
		Destroy();
		return;
	}
	else if (GetPosition().y < 0 - sprite.GetFrameSize().y / 2.0) {
		Destroy();
		return;
	}
	if (GetPosition().x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0) {
		Destroy();
		return;
	}
	else if (GetPosition().x < 0 - sprite.GetFrameSize().x / 2.0) {
		Destroy();
		return;
	}
}

GameObjectType Laser::GetObjectType() {
	return GameObjectType::Laser;
}

/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Purpose: Source file for Ship
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"	//Logger, Window
#include "..\Engine\GameObject.h"		//GetCollision
#include "..\Engine\Collision.h"		
#include "ScreenWrap.h"
#include "Ship.h"
#include "Laser.h"
#include "Flame_Anims.h"
#include "Ship_Anims.h"

const double Ship::accel = 400;
const double Ship::drag = 0.5;
const double Ship::maxVel = 400;
const double Ship::rotationRate = 2;

Ship::Ship(Vector2D pos) : GameObject(pos, 0, { 0.75, 0.75 }), rotateCounterKey(Input::KeyboardButton::A), rotateClockKey(Input::KeyboardButton::D),
							fireLazerKey(Input::KeyboardButton::Space), accelerateKey(Input::KeyboardButton::W), isAccelerating(false), isDead(false) {
	sprite.Load("assets/Ship.spt", this);
	flameLeft.Load("assets/flame.spt", this);
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	flameRight.Load("assets/flame.spt", this);
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	isAccelerating = false;
	components.AddComponent(new ScreenWrap(*this));
}

void Ship::Update(double dt) {
	sprite.Update(dt);
	flameLeft.Update(dt);
	flameRight.Update(dt);
	if (IsDead() == false) {
		if (rotateClockKey.IsKeyDown() == true) {
			UpdateRotation(-Ship::rotationRate * dt);
		}
		if (rotateCounterKey.IsKeyDown() == true) {
			UpdateRotation(Ship::rotationRate * dt);
		}
		if (accelerateKey.IsKeyDown() == true) {
			if (isAccelerating == false) {
				flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				isAccelerating = true;
			}
			velocity += RotateMatrix(GetRotation()) * Vector2D { 0, accel* dt };
		}
		else {
			if (isAccelerating == true) {
				flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				isAccelerating = false;
			}
		}

		if (fireLazerKey.IsKeyReleased() == true) {
			Engine::GetGameObjectManager().Add(new Laser(GetMatrix() * sprite.GetHotSpot(3), GetRotation(), GetScale(), RotateMatrix(GetRotation()) * Vector2D { 0, 600 }));
			Engine::GetGameObjectManager().Add(new Laser(GetMatrix() * sprite.GetHotSpot(4), GetRotation(), GetScale(), RotateMatrix(GetRotation()) * Vector2D { 0, 600 }));
		}

		velocity -= (velocity * Ship::drag * dt);
		if (velocity.LengthSquare() > maxVel * maxVel) {
			velocity = velocity.Normalize() * maxVel;
		}
	}

	UpdatePosition(velocity * dt);
	components.GetComponent<ScreenWrap>()->TestForWrap();
}

void Ship::Draw(TransformMatrix cameraMatrix) {
	TransformMatrix shipScreenMatrix = cameraMatrix * GetMatrix();
	flameRight.Draw(shipScreenMatrix * TranslateMatrix(sprite.GetHotSpot(1)));
	flameLeft.Draw(shipScreenMatrix * TranslateMatrix(sprite.GetHotSpot(2)));
	sprite.Draw(shipScreenMatrix);

	if (Engine::Instance().ShowCollision() == true) {
		GetComponent<Collision>()->Draw(cameraMatrix * GetMatrix());
	}
}

bool Ship::CanCollideWith(GameObjectType) {
	return false;
}

void Ship::ResolveCollision(GameObject* collidedWith) {
	switch (collidedWith->GetObjectType()) {
	case GameObjectType::Meteor:
		sprite.PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		isDead = true;
		break;
	}
}
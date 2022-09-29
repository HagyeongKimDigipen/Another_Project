/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Purpose: Meteor source file
Project: CS230
Author: Kevin Wright
Creation date: 4/27/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/GameState.h"
#include "../Engine/GameObject.h"
#include "../Engine/Collision.h"
#include "Score.h"
#include "Particle.h"
#include "ScreenWrap.h"
#include "Meteor.h"
#include "Meteor_Anims.h"

constexpr double PI = 3.1415926535897932384626433832795;

Meteor::Meteor() : GameObject({ static_cast<double>(rand() % static_cast<int> (Engine::GetWindow().GetSize().x)),
									static_cast<double>(rand() % static_cast<int> (Engine::GetWindow().GetSize().y)) },
									((rand() % static_cast<int>(PI * 2 * 1024)) / 1024.0f), { 1, 1 }), health(100), size(1), isDead(false) {
	sprite.Load("assets/Meteor.spt", this);

	velocity.x = 100 - static_cast<double> (rand() % 200);
	velocity.y = 100 - static_cast<double> (rand() % 200);

	double scaleAmount = (rand() % 100) / 400.0 + .75;
	SetScale({ scaleAmount, scaleAmount });
	AddComponent(new ScreenWrap(*this));
}

Meteor::Meteor(Meteor& original) : GameObject(original.GetPosition(), GetRotation(), { 1,1 }), size(original.size + 1), health(100) {
	sprite.Load("assets/Meteor.spt", this);
	double scaleAmount = 1;
	switch (size) {
	case 2:
		scaleAmount = (rand() % 100) / 400.0 + .50;
		break;
	case 3:
		scaleAmount = (rand() % 100) / 400.0 + .25;
		break;
	}
	SetScale({ scaleAmount, scaleAmount });
	AddComponent(new ScreenWrap(*this));
}

void Meteor::Update(double dt) {
	GameObject::Update(dt);
	if (sprite.IsAnimationDone() == true) {
		Destroy();
	}
	components.GetComponent<ScreenWrap>()->TestForWrap();
}

bool Meteor::CanCollideWith(GameObjectType collideAgainstType) {
	if (collideAgainstType == GameObjectType::Laser) {
		return true;
	}
	return false;
}

void Meteor::ResolveCollision(GameObject* objectB) {
	if (isDead == true) {
  		return;
	}
	switch (objectB->GetObjectType()) {
	case GameObjectType::Laser:
		health -= 10;
		break;
	}

	if (health <= 0) {
		Engine::GetGameStateManager().GetComponent<Score>()->AddScore(100);
		if (size < 3) {
			Meteor* newMeteorA = new Meteor(*this);
			newMeteorA->velocity = RotateMatrix(PI / 6) * velocity;
			Meteor* newMeteorB = new Meteor(*this);
			newMeteorB->velocity = RotateMatrix(-PI / 6) * velocity;
 			Engine::GetGameObjectManager().Add(newMeteorA);
			Engine::GetGameObjectManager().Add(newMeteorB);
		}
		isDead = true;
		sprite.PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
	}
	else {
		Engine::GetGameStateManager().GetComponent<Score>()->AddScore(20);
		velocity += objectB->GetVelocity() * 0.01;
		Vector2D emitVector = (objectB->GetPosition() - GetPosition()).Normalize();
		Vector2D emitterPosition = GetPosition() + emitVector * GetComponent<CircleCollision>()->GetRadius();
		Engine::GetGameStateManager().GetComponent<MeteorBitsParticles>()->Emit(5, emitterPosition, velocity, emitVector * 50, PI / 2);  //ParticleType::MeteorBits
		Engine::GetGameStateManager().GetComponent<HitParticles>()->Emit(1, emitterPosition, velocity, { 0,0 }, 0); // ParticleType::Hit
	}
	objectB->Destroy();
}

GameObjectType Meteor::GetObjectType() { return GameObjectType::Meteor; }
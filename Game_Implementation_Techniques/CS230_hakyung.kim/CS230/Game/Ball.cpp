/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Purpose: Hero source file
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"

#include "Level1.h"		//Level1::gravity
#include "Ball.h"
#include "Ball_Anims.h"
#include "Gravity.h"

const double Ball::bounceVelocity = 703.125;

Ball::Ball(Vector2D startPos) : GameObject(startPos) {
	sprite.Load("assets/Ball.spt", this);
	currState = &stateSquish;
	currState->Enter(this);
}

void Ball::State_Bounce::Enter(GameObject* object) {
	Ball* ball = static_cast<Ball*>(object);
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
	ball->velocity.y = Ball::bounceVelocity;
}
void Ball::State_Bounce::Update(GameObject* object, double dt) {
	Ball* ball = static_cast<Ball*>(object);
	ball->velocity.y -= Engine::GetGameStateManager().GetComponent<Gravity>()->GetValue() * dt;
}
void Ball::State_Bounce::TestForExit(GameObject*) {
}

void Ball::State_Squish::Enter(GameObject* object) {
	Ball* ball = static_cast<Ball*>(object);
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}
void Ball::State_Squish::Update(GameObject*, double) {}
void Ball::State_Squish::TestForExit(GameObject* object) {
	Ball* ball = static_cast<Ball*>(object);
	if (ball->sprite.IsAnimationDone() == true) {
		ball->ChangeState(&ball->stateBounce);
	}
}

bool Ball::CanCollideWith(GameObjectType collideAgainstType) {
	if (collideAgainstType == GameObjectType::Floor) {
		return true;
	}
	return false;
}

void Ball::ResolveCollision(GameObject* collideWith) {
	RectCollision *collideRect = collideWith->GetComponent<RectCollision>();

	if (collideWith->GetObjectType() == GameObjectType::Floor) {
		SetPositionY(collideRect->GetWorldCoorRect().Top());
		velocity.y = 0;
		ChangeState(&stateSquish);
	}
}
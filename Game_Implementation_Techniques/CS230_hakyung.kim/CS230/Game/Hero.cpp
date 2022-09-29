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
#include "..\Engine\Engine.h"		//Logger
#include "..\Engine\Collision.h"

#include "Level1.h"
#include "Hero.h"
#include "Hero_Anims.h"
#include "GameObjectTypes.h"
#include "Gravity.h"

const double Hero::jumpVelocity = 937.5;
const double Hero::xAccel = 500;
const double Hero::xDrag = 800;
const double Hero::maxXVelocity = 650;
const double Hero::hurtTime = 2;

Hero::Hero(Vector2D startPos) : GameObject(startPos),
									moveLeftKey(Input::KeyboardButton::Left), moveRightKey(Input::KeyboardButton::Right), 
									jumpKey(Input::KeyboardButton::Up), hurtTimer(0), drawHero(true), standingOnObject(nullptr), isDead(false) {
	sprite.Load("assets/Hero.spt", this);
	isFlipped = false;
	currState = &stateIdle;
	currState->Enter(this);

	for (GameObject* objectB : Engine::GetGameObjectManager()) {
		if (objectB->GetObjectType() == GameObjectType::Floor && DoesCollideWith(objectB)) {
			SetPositionY(objectB->GetComponent<RectCollision>()->GetWorldCoorRect().Top());
			standingOnObject = objectB;
		}
	}
}

void Hero::Update(double dt) {
	if (hurtTimer > 0) {
		hurtTimer -= dt;
		drawHero = !drawHero;
		if (hurtTimer <= 0) {
			hurtTimer = 0;
			drawHero = true;
		}
	}
	if (IsDead() == false) {
		GameObject::Update(dt);
	}

	if (isFlipped == true) {
		SetScale({ -1, 1 });
	} else {
		SetScale({ 1, 1 });
	}
}

void Hero::Draw(TransformMatrix displayMatrix) {
	if (drawHero == true) {
		GameObject::Draw(displayMatrix);
	}
}

void Hero::State_Idle::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
	if (hero->standingOnObject == nullptr) {
		Engine::GetLogger().LogError("Hero standing on null");
	}
}
void Hero::State_Idle::Update(GameObject*, double) {}
void Hero::State_Idle::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->isFlipped = false;
	}
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->isFlipped = true;
	}
	if (hero->standingOnObject == nullptr) {
		Engine::GetLogger().LogError("Hero running on null");
	}
}
void Hero::State_Running::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->velocity.x > 0 && hero->moveRightKey.IsKeyDown() == true) {
		hero->isFlipped = false;
	}
	if (hero->velocity.x < 0 && hero->moveLeftKey.IsKeyDown() == true) {
		hero->isFlipped = true;
	}
	hero->UpdateXVelocity(dt);
}
void Hero::State_Running::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true && hero->velocity.x > 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->moveRightKey.IsKeyDown() == true && hero->velocity.x < 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->velocity.x == 0) {
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
	if (hero->standingOnObject != nullptr && hero->standingOnObject->GetComponent<RectCollision>()->DoesCollideWith(hero->GetPosition()) == false) {
		hero->standingOnObject = nullptr;
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Skidding::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}
void Hero::State_Skidding::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->velocity.x > 0) {
		hero->velocity.x -= (xDrag + xAccel) * dt;
	} else if (hero->velocity.x < 0) {
		hero->velocity.x += (xDrag + xAccel) * dt;
	}
}
void Hero::State_Skidding::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true) {
		if (hero->velocity.x <= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	} else if (hero->moveRightKey.IsKeyDown() == true) {
		if (hero->velocity.x >= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	} else {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->velocity.y = Hero::jumpVelocity;
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->velocity.y -= Engine::GetGameStateManager().GetComponent<Gravity>()->GetValue() * dt;
	hero->UpdateXVelocity(dt);
}
void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == false) {
		hero->ChangeState(&hero->stateFalling);
		hero->velocity.y = 0;
	} else if (hero->velocity.y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim)); 
}
void Hero::State_Falling::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->velocity.y -= Engine::GetGameStateManager().GetComponent<Gravity>()->GetValue() * dt;
	hero->UpdateXVelocity(dt);
}
void Hero::State_Falling::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetPosition().y < -hero->sprite.GetFrameSize().y * 2 ) {
		hero->isDead = true;
	}
}

void Hero::UpdateXVelocity(double dt) {
	if (moveLeftKey.IsKeyDown() == true) {
		velocity.x -= Hero::xAccel * dt;	// apply acceleration
		if (velocity.x < -Hero::maxXVelocity) {
			velocity.x = -Hero::maxXVelocity;
		}
	} else if (moveRightKey.IsKeyDown() == true) {
		velocity.x += Hero::xAccel * dt;	// apply acceleration
		if (velocity.x > Hero::maxXVelocity) {
			velocity.x = Hero::maxXVelocity;
		}
	} else {
		// no key is down, need to apply drag to slow down
		double xDragDt = Hero::xDrag * dt;
		if (velocity.x > xDragDt) {
			velocity.x -= xDragDt;
		} else if (velocity.x < -xDragDt) {
			velocity.x += xDragDt;
		} else {
			velocity.x = 0;
		}
	}
}


GameObjectType Hero::GetObjectType() {
	return GameObjectType::Hero; 
}

std::string Hero::GetObjectTypeName() {
	return "Hero";
}

bool Hero::CanCollideWith(GameObjectType) {
	return true;
}

void Hero::ResolveCollision(GameObject* collidedWith) {
	Rect collideRect = collidedWith->GetComponent<RectCollision>()->GetWorldCoorRect();
	Rect heroRect = GetComponent<RectCollision>()->GetWorldCoorRect();

	switch (collidedWith->GetObjectType()) {
	case GameObjectType::Ball:
		if (currState == &stateFalling) {
			if (GetPosition().y > collideRect.Bottom()) {
				velocity.y = Hero::jumpVelocity;
			}
			return;
		}
		hurtTimer = Hero::hurtTime;
		if (heroRect.Left() < collideRect.Left()) {
			SetPositionX(GetPosition().x - (heroRect.Right() - collideRect.Left()));
			velocity = { -Hero::xAccel / 2, Hero::jumpVelocity / 4 };
			ChangeState(&stateFalling);
		}
		else {
			SetPositionX(GetPosition().x + (collideRect.Right() - heroRect.Left()));
			velocity = { Hero::xAccel / 2, Hero::jumpVelocity / 4 };
			ChangeState(&stateFalling);
		}
		break;
	case GameObjectType::Bunny:
		if (currState == &stateFalling) {
			if (GetPosition().y > collideRect.Bottom()) {
				collidedWith->ResolveCollision(this);
				velocity.y = Hero::jumpVelocity / 2;
			}
			return;
		}
		hurtTimer = Hero::hurtTime;
		if (heroRect.Left() < collideRect.Left()) {
			SetPositionX(GetPosition().x - (heroRect.Right() - collideRect.Left()));
			velocity = { -Hero::xAccel / 2, Hero::jumpVelocity / 4 };
			ChangeState(&stateFalling);
		}
		else {
			SetPositionX(GetPosition().x + (collideRect.Right() - heroRect.Left()));
			velocity = { Hero::xAccel / 2, Hero::jumpVelocity / 4 };
			ChangeState(&stateFalling);
		}
		break;
	case GameObjectType::Floor: [[fallthrough]];
	case GameObjectType::TreeStump:
		if (currState == &stateFalling) {
			if (heroRect.Top() > collideRect.Top() &&collidedWith->DoesCollideWith(GetPosition())) {
				SetPositionY(collideRect.Top());
				standingOnObject = collidedWith;
				velocity.y = 0;
				if (velocity.x != 0) {
					ChangeState(&stateRunning);
				}
				else {
					ChangeState(&stateIdle);
				}
				return;
			}
		}
		if (heroRect.Left() < collideRect.Left()) {
			SetPositionX(GetPosition().x - (heroRect.Right() - collideRect.Left()));
			velocity.x = 0;
		}
		else {
			SetPositionX(GetPosition().x + (collideRect.Right() - heroRect.Left()));
			velocity.x = 0;
		}
		break;
	case GameObjectType::Trigger:
		collidedWith->ResolveCollision(this);
		break;
	}
}
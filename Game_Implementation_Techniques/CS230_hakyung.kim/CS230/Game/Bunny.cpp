/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Purpose: Bunny source file
Project: CS230
Author: hakyung.kim
Creation date: 4/27/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "Bunny.h"
#include "Bunny_Anims.h"
#include "Score.h"

Bunny::Bunny(Vector2D pos) : GameObject(pos), isDead(false) 
{
	sprite.Load("assets/Bunny.spt", this);
}

GameObjectType Bunny::GetObjectType()
{
	if (isDead == true)
	{
		return GameObjectType::DeadBunny;
	}
	else
	{
		return GameObjectType::Bunny;
	}
}

void Bunny::ResolveCollision(GameObject* collideWith) 
{
	if (collideWith->GetObjectType() == GameObjectType::Hero) 
	{
		Engine::GetGameStateManager().GetComponent<Score>()->AddScore(100);
		isDead = true;
		
		sprite.PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	}
}
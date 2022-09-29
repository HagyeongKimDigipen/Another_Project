/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Exit.cpp
Purpose: Exit source file
Project: CS230
Author: Kevin Wright
Creation date: 5/4/2020
-----------------------------------------------------------------*/

#include "..\Engine\Collision.h"
#include "..\Engine\Engine.h"
#include "Screens.h"
#include "Exit.h"

Exit::Exit(RectInt rect) : GameObject(rect.bottomLeft) {
	AddComponent(new RectCollision({ { 0, 0 }, rect.Size() }, this));
}

void Exit::Update(double) {}

void Exit::Draw(TransformMatrix) {}

void Exit::ResolveCollision(GameObject*) {
	Engine::GetGameStateManager().SetNextState(LEVEL2);
}
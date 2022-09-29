/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Purpose: Header file for Level 2
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"		//Input::InputKey
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\TransformMatrix.h"

#include "Particle.h"

class Ship;

class Level2 : public GameState {
public:
	Level2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Level 2"; }
private:
	Ship* ship;

	Input::InputKey debugCollision;
	Input::InputKey levelReload;
	Input::InputKey levelNext;
};


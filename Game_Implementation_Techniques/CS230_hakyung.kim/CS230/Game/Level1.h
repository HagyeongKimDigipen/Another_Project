/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Purpose: Header file for Level 1
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"        //Input::InputKey

class Hero;

class Level1 : public GameState {
public:
	Level1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Level 1"; }
private:
	int lives;
	double timer;

	Hero* heroPtr;

	Input::InputKey debugCollision;
	Input::InputKey levelReload;
	Input::InputKey levelNext;
};


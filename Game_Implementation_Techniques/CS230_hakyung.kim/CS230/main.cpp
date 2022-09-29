/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Purpose: Source file for Main
Project: CS230
Author: Kevin Wright
Creation date: 3/17/2020
-----------------------------------------------------------------*/

#include <exception>    // std::exception
#include <stdlib.h>		// srand
#include <time.h>       // time

#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/Level1.h"
#include "Game/Level2.h"
#include "Game/Screens.h"


int main(void) {
	Engine& engine = Engine::Instance();

	try {
		engine.Init("Week 13");
		Splash splash;
		Level1 level1;
		Level2 level2;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(level1);
		engine.GetGameStateManager().AddGameState(level2);
		engine.AddSpriteFont("assets/font.png");

		while (engine.HasGameEnded() == false) {
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	} catch (std::exception & e) {
		Engine::GetLogger().LogError(e.what());
		return -1;
	}
}
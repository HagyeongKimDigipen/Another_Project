/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Purpose: Header file for Game State Manager
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include <vector>
#include "GameState.h"


class GameStateManager {
public:
	GameStateManager();

	void AddGameState(GameState& gameState);
	void Update(double dt);
	void SetNextState(int initState);
	void Shutdown();
	void ReloadState();
	GameState* GetCurrentState();
	bool HasGameEnded() { return state == State::EXIT; }

	template<typename T>
	T* GetComponent() { return GetCurrentState()->GetComponents().GetComponent<T>(); }
	template<typename T>
	void AddComponent(T* component) { GetCurrentState()->GetComponents().AddComponent<T>(component); }
private:
	enum class State {
		START,
		LOAD,
		RUNNING,
		UNLOAD,
		SHUTDOWN,
		EXIT,
	};

	std::vector<GameState*> gameStates;
	State state;
	GameState* currGameState;
	GameState* nextGameState;
};


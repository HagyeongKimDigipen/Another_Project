/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Purpose: Hero header file
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\BasicDataTypes.h"	//Vector2D
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Ball : public GameObject {
public:
	Ball(Vector2D startPos);
	GameObjectType GetObjectType() override { return GameObjectType::Ball; }
	std::string GetObjectTypeName() override { return "Ball"; }
	bool CanCollideWith(GameObjectType collideAgainstType) override;
	void ResolveCollision(GameObject* collideWith) override;
private:
	class State_Bounce : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override {	return "bounce"; }
	};
	class State_Squish : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "squish"; }
	};
	State_Bounce stateBounce;
	State_Squish stateSquish;
	
	static const double bounceVelocity;
};
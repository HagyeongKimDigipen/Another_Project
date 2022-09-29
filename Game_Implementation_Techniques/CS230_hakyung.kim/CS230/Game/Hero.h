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
#include "..\Engine\Input.h"		//Input::InputKey
#include "..\Engine\BasicDataTypes.h"	//Vector2D
#include "..\Engine\GameObject.h"

enum class GameObjectType;
class TransformMatrix;

class Hero : public GameObject {
public:
	Hero(Vector2D startPos);
	void Update(double dt);
	void Draw(TransformMatrix displayMatrix) override;
	GameObjectType GetObjectType();
	std::string GetObjectTypeName() override;
	bool CanCollideWith(GameObjectType collideAgainstType) override;
	void ResolveCollision(GameObject* collidedWith) override;

	bool IsDead() { return isDead; }
private:
	class State_Idle : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Idle"; }
	};
	class State_Running : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Running"; }
	};
	class State_Skidding : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Skidding"; }
	};
	class State_Jumping : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Jumping"; }
	};
	class State_Falling : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Falling"; }
	};
	State_Idle stateIdle;
	State_Running stateRunning;
	State_Skidding stateSkidding;
	State_Jumping stateJumping;
	State_Falling stateFalling;

	void UpdateXVelocity(double dt);

	GameObject* standingOnObject;

	static const double jumpVelocity;
	static const double xAccel;
	static const double xDrag;
	static const double maxXVelocity;
	static const double hurtTime;

	double hurtTimer;
	bool isFlipped;
	bool drawHero;
	bool isDead;

	Input::InputKey moveLeftKey;
	Input::InputKey moveRightKey;
	Input::InputKey jumpKey;
};
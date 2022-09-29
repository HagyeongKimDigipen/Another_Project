/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Purpose: GameObject header file
Project: CS230
Author: Kevin Wright
Creation date: 4/27/2020
-----------------------------------------------------------------*/

#pragma once

#include "BasicDataTypes.h"	//Vector2D
#include "Sprite.h"			
#include "TransformMatrix.h"	
#include "ComponentManager.h"


class Collision;
enum class GameObjectType;

class GameObject {
public:
	GameObject(Vector2D position);
	GameObject(Vector2D position, double rotation, Vector2D scale);
	virtual ~GameObject();
	void Destroy();
	bool ShouldDestroy() { return destroyObject; }

	virtual void Update(double dt);
	virtual void Draw(TransformMatrix displayMatrix);
	virtual GameObjectType GetObjectType() = 0;
	virtual std::string GetObjectTypeName() = 0;

	const TransformMatrix& GetMatrix();
	Vector2D GetPosition() const;
	Vector2D GetScale() const;
	double GetRotation() const;
	Vector2D GetVelocity() const;

	virtual bool CanCollideWith(GameObjectType collideAgainstType);
	bool DoesCollideWith(GameObject* objectB);
	bool DoesCollideWith(Vector2D point);
	virtual void ResolveCollision(GameObject*);

	template<typename T>
	T* GetComponent() { return components.GetComponent<T>(); }
	template<typename T>
	void AddComponent(T* component) { components.AddComponent<T>(component); }

	void SetPosition(Vector2D newPosition);
	void SetPositionX(double newPosX);
	void SetPositionY(double newPosY);
	Sprite& GetSprite();
protected:
	class State {
	public:
		virtual void Enter(GameObject* object) = 0;
		virtual void Update(GameObject* object, double dt) = 0;
		virtual void TestForExit(GameObject* object) = 0;
		virtual std::string GetName() = 0;
	};
	class State_Nothing : public State {
	public:
		void Enter(GameObject*) override {}
		void Update(GameObject*, double) override {}
		void TestForExit(GameObject*) override {}
		std::string GetName() override { return ""; }
	};
	State_Nothing state_nothing;

	void UpdatePosition(Vector2D adjustPosition);
	void SetScale(Vector2D newScale);
	void SetRotation(double newRotationAmount);
	void UpdateRotation(double adjustRotation);
	void ChangeState(State* newState);

	Sprite sprite;
	Vector2D velocity;
	State* currState;
	ComponentManager components;

private:
	TransformMatrix objectMatrix;
	bool updateMatrix;

	double rotation;
	Vector2D scale;
	Vector2D position;
	bool destroyObject;
};
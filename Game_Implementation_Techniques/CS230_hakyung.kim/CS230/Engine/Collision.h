/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.h
Purpose: Collision header file
Project: CS230
Author: Kevin Wright
Creation date: 4/29/2020
-----------------------------------------------------------------*/

#pragma once
#include "BasicDataTypes.h"
#include "Component.h"

class GameObject;
class TransformMatrix;

class Collision : public Component {
public:
	enum class CollideType {
		Rect_Collide,
		Circle_Collide,
	};
	virtual ~Collision() = default;
	virtual void Draw(TransformMatrix displayMatrix) = 0;
	virtual CollideType GetCollideType() = 0;
	virtual bool DoesCollideWith(GameObject* gameObject) = 0;
	virtual bool DoesCollideWith(Vector2D point) = 0;
};

class RectCollision : public Collision {
public:
	RectCollision(RectInt rect, GameObject* objectPtr) : rect(rect), objectPtr(objectPtr) {}
	void Draw(TransformMatrix displayMatrix) override;
	bool DoesCollideWith(GameObject* testAgainstObject) override;
	bool DoesCollideWith(Vector2D point) override;
	CollideType GetCollideType() override { return Collision::CollideType::Rect_Collide; };
	Rect GetWorldCoorRect();
private:
	GameObject* objectPtr;
	RectInt rect;
};

class CircleCollision : public Collision {
public:
	CircleCollision(double radius, GameObject* objectPtr) : radius(radius), objectPtr(objectPtr) {}
	void Draw(TransformMatrix displayMatrix) override;
	bool DoesCollideWith(GameObject* testAgainstObject) override;
	bool DoesCollideWith(Vector2D point) override;
	double GetRadius();
	CollideType GetCollideType() override { return Collision::CollideType::Circle_Collide; };
private:
	GameObject* objectPtr;
	double radius;
};
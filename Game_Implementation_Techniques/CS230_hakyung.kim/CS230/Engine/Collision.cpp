/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Purpose: Collision source file
Project: CS230
Author: Kevin Wright
Creation date: 4/29/2020
-----------------------------------------------------------------*/

#include "doodle/drawing.hpp"
#include "../Engine/Engine.h"

#include "Collision.h"
#include "TransformMatrix.h"
#include "GameObject.h"
#include "BasicDataTypes.h"


void RectCollision::Draw(TransformMatrix displayMatrix) {
	doodle::no_fill();
	doodle::set_outline_width(2);
	doodle::set_outline_color(0xFFFFFFFF);
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_rectangle(rect.bottomLeft.x, rect.bottomLeft.y, rect.Size().x, rect.Size().y);
	doodle::pop_settings();
}

void CircleCollision::Draw(TransformMatrix displayMatrix) {
	doodle::no_fill();
	doodle::set_outline_width(2);
	doodle::set_outline_color(0xFFFFFFFF);
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_ellipse(0, 0, radius*2);
	doodle::pop_settings();
}

Rect RectCollision::GetWorldCoorRect() {
	return { objectPtr->GetMatrix() * rect.bottomLeft, objectPtr->GetMatrix() * rect.topRight };
}

bool RectCollision::DoesCollideWith(GameObject* testAgainstObject) {
	if (testAgainstObject->GetComponent<RectCollision>() == nullptr) {
		Engine::GetLogger().LogError("Doing Rect/Rect collision without Rect/Rect collide objects");
		return false;
	}

	Rect rectA = GetWorldCoorRect();
	Rect rectB = testAgainstObject->GetComponent<RectCollision>()->GetWorldCoorRect();

	if (rectA.Right() > rectB.Left() && rectA.Left() < rectB.Right() &&
		rectA.Bottom() < rectB.Top() && rectA.Top() > rectB.Bottom()) {
		return true;
	}
	return false;
}

bool RectCollision::DoesCollideWith(Vector2D point) {
	Rect worldRect = GetWorldCoorRect();
	return point.x >= worldRect.Left() && point.x <= worldRect.Right() && point.y <= worldRect.Top() && point.y >= worldRect.Bottom();
}

double CircleCollision::GetRadius() {
	return (ScaleMatrix(objectPtr->GetScale()) * Vector2D { radius, 0 }).x;
}

bool CircleCollision::DoesCollideWith(GameObject* testAgainstObject) {
	if (testAgainstObject->GetComponent<CircleCollision>() == nullptr) {
		Engine::GetLogger().LogError("Doing Circle/Circle collision without Circle/Circle collide objects");
		return false;
	}

	CircleCollision* objectBCollision = testAgainstObject->GetComponent<CircleCollision>();

	Vector2D dist = objectPtr->GetPosition() - testAgainstObject->GetPosition();
	double radiusA = (ScaleMatrix(objectPtr->GetScale()) * Vector2D { radius, 0 }).x;
	double radiusB = (ScaleMatrix(testAgainstObject->GetScale()) * Vector2D { objectBCollision->radius, 0 }).x;
	double collideDistSquare = (radiusA + radiusB) * (radiusA + radiusB);

	return dist.LengthSquare() < collideDistSquare;
}

bool CircleCollision::DoesCollideWith(Vector2D point) {

	Vector2D dist = objectPtr->GetPosition() - point;
	double radiusA = (objectPtr->GetMatrix() * Vector2D { radius, 0 }).x;
	double collideDistSquare = radiusA * radiusA;

	return dist.LengthSquare() < collideDistSquare;
}
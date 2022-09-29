/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Purpose: GameObject source file
Project: CS230
Author: Kevin Wright
Creation date: 4/27/2020
-----------------------------------------------------------------*/
#include "Engine.h"
#include "Collision.h"


GameObject::GameObject(Vector2D position) : GameObject(position, 0, { 1, 1 }) {}

GameObject::GameObject(Vector2D position, double rotation, Vector2D scale)
							: velocity{ 0,0 }, position(position), updateMatrix(true), 
							scale(scale), rotation(rotation), currState(&state_nothing) {
}

GameObject::~GameObject() { 
}

void GameObject::Update(double dt) {
	currState->Update(this, dt);
	sprite.Update(dt);
	if (velocity.x != 0 || velocity.y != 0) {
		position += velocity * dt;
		updateMatrix = true;
	}
	currState->TestForExit(this);
}

void GameObject::ChangeState(State* newState) {
	currState = newState;
	currState->Enter(this);
}

void GameObject::Draw(TransformMatrix displayMatrix) {
	sprite.Draw(displayMatrix * GetMatrix());
	if (Engine::Instance().ShowCollision() == true) {
		components.GetComponent<Collision>()->Draw(displayMatrix * objectMatrix);
	}
}

void GameObject::Destroy() { destroyObject = true; }

Vector2D GameObject::GetPosition() const { return position; }
Vector2D GameObject::GetScale() const { return scale; }
double GameObject::GetRotation() const { return rotation; }
const TransformMatrix& GameObject::GetMatrix() {
	if (updateMatrix == true) {
		objectMatrix = TranslateMatrix(position) * RotateMatrix(rotation) * ScaleMatrix(scale);
		updateMatrix = false;
	}
	return objectMatrix;
}
Vector2D GameObject::GetVelocity() const { return velocity; }

void GameObject::SetPosition(Vector2D newPosition) {
	position = newPosition;
	updateMatrix = true;
}
void GameObject::SetPositionX(double newPosX) {
	position.x = newPosX;
	updateMatrix = true;
}
void GameObject::SetPositionY(double newPosY) {
	position.y = newPosY;
	updateMatrix = true;
}
void GameObject::UpdatePosition(Vector2D adjustPosition) {
	position += adjustPosition;
	updateMatrix = true;
}

void GameObject::SetScale(Vector2D newScale) {
	scale = newScale;
	updateMatrix = true;
}

void GameObject::SetRotation(double newRotationAmount) {
	rotation = newRotationAmount;
	updateMatrix = true;
}
void GameObject::UpdateRotation(double adjustRotation) {
	rotation += adjustRotation;
	updateMatrix = true;
}

bool GameObject::CanCollideWith(GameObjectType) {
	return false;
}

bool GameObject::DoesCollideWith(GameObject *objectB) {
	return components.GetComponent<Collision>() != nullptr && components.GetComponent<Collision>()->DoesCollideWith(objectB);
}

bool GameObject::DoesCollideWith(Vector2D point) {
	return components.GetComponent<Collision>() != nullptr && components.GetComponent<Collision>()->DoesCollideWith(point);
}

void GameObject::ResolveCollision(GameObject*) {
	Engine::GetLogger().LogError("Base class collision resolution should not be called");
}

Sprite& GameObject::GetSprite() {
	return sprite;
}
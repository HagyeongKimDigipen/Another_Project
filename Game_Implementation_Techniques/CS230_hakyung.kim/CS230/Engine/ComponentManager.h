/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ComponentManager.h
Purpose: Header file to handle managing components
Project: CS230
Author: Kevin Wright
Creation date: 5/29/2020
-----------------------------------------------------------------*/

#pragma once
#include <vector>
#include "Component.h"

class ComponentManager {
public:
	~ComponentManager() {
		Clear();
	}
	template<typename T>
	T* GetComponent() {
		for (Component* component : components) {
			if (dynamic_cast<T*>(component) != nullptr) {
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}

	template<typename T>
	void AddComponent(T* component) {
		components.push_back(component);
	}
	void Clear() {
		for (Component* component : components) {
			delete component;
		}
		components.clear();
	}
private:
	std::vector<Component*> components;
};

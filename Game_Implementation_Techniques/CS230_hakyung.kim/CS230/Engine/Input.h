/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.h
Purpose: Header file for Input Module
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/
#pragma once
#include <vector>

class Input {
public:
	enum class KeyboardButton {
		None,	Enter,	Escape, Space, 	Left,	Up,		Right,	Down,
		A,		B,		C,		D,		E,		F,		G,		H,		I,		J,
		K,		L,		M,		N,		O,		P,		Q,		R,		S,		T,
		U,		V,		W,		X,		Y,		Z,
		Count
	};
	class InputKey {
	public:
		InputKey(KeyboardButton button);
		bool IsKeyDown() const;
		bool IsKeyReleased() const;
	private:
		KeyboardButton button;
	};

	Input();
	bool IsKeyDown(KeyboardButton key) const;
	bool IsKeyUp(KeyboardButton key) const;
	bool IsKeyReleased(KeyboardButton key) const;
	void SetKeyDown(KeyboardButton key, bool value);
	void Update();
private:
	std::vector<bool> keyDown;
	std::vector<bool> wasKeyDown;
};




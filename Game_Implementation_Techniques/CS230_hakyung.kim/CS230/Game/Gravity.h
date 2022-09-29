/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.h
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\Component.h" 

class Gravity : public Component {
public:
	double GetValue() { return gravity; }
private:
	static const double gravity;
};
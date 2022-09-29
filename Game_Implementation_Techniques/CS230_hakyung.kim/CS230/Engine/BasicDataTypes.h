/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: BasicDataTypes.h
Purpose: Utility file for various commonly used data structures
Project: CS230
Author: Kevin Wright
Creation date: 3/21/2020
-----------------------------------------------------------------*/
#include <algorithm>
#include <cmath>

#pragma once

struct Vector2D {
	double x;
	double y;

	Vector2D operator *(double scale) const { return { x * scale, y * scale }; }
	Vector2D operator /(double scale) const { return { x / scale, y / scale }; }
	Vector2D operator +(Vector2D rhs) const { return { x + rhs.x, y + rhs.y }; }
	Vector2D operator -(Vector2D rhs) const { return { x - rhs.x, y - rhs.y }; }
	void operator +=(Vector2D rhs) { x += rhs.x; y += rhs.y; }
	void operator -=(Vector2D rhs) { x -= rhs.x; y -= rhs.y; }
	Vector2D operator -() const { return { -x, -y }; }
	double LengthSquare() const { return x * x + y * y; }
	Vector2D Normalize() const { double length = std::sqrt(LengthSquare());  return { x / length, y / length }; }
};

struct Vector2DInt {
	int x;
	int y;

	Vector2DInt operator *(int scale) const { return { x * scale, y * scale }; }
	Vector2DInt operator /(int scale) const { return { x / scale, y / scale }; }
	Vector2D operator *(double scale) const { return { x * scale, y * scale }; }
	Vector2D operator /(double scale) const { return { x / scale, y / scale }; }
	Vector2DInt operator +(Vector2DInt rhs) const { return { x + rhs.x, y + rhs.y }; }
	Vector2DInt operator -(Vector2DInt rhs) const { return { x - rhs.x, y - rhs.y }; }
	void operator +=(Vector2DInt rhs) { x += rhs.x; y += rhs.y; }
	void operator -=(Vector2DInt rhs) { x -= rhs.x; y -= rhs.y; }
	Vector2DInt operator -() const { return { -x, -y }; }
	operator Vector2D() { return Vector2D{ static_cast<double>(x), static_cast<double>(y) }; }
};

struct Rect {
	Vector2D bottomLeft;
	Vector2D topRight;
	Vector2D Size() { return { Right() - Left(), Top() - Bottom() }; }
	double Left() { return std::min(bottomLeft.x, topRight.x); }	 // if the rect was flipped, then bottomLeft.x > topRight.x
	double Right() { return std::max(bottomLeft.x, topRight.x); }	// if the rect was flipped, then bottomLeft.x > topRight.x
	double Top() { return topRight.y; }
	double Bottom() { return bottomLeft.y; }
};

struct RectInt {
	Vector2DInt bottomLeft;
	Vector2DInt topRight;
	Vector2DInt Size() { return { Right() - Left(), Top() - Bottom() }; }
	int Left() { return std::min(bottomLeft.x, topRight.x); }	 // if the rect was flipped, then bottomLeft.x > topRight.x
	int Right() { return std::max(bottomLeft.x, topRight.x); }	// if the rect was flipped, then bottomLeft.x > topRight.x
	int Top() { return topRight.y; }
	int Bottom() { return bottomLeft.y; }
};

typedef unsigned Color;
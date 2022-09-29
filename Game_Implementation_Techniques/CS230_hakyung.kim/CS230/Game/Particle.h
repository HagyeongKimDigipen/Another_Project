/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Particle.h
Purpose: Particle header file
Project: CS230
Author: Kevin Wright
Creation date: 5/19/2020
-----------------------------------------------------------------*/

#pragma once
#include <vector>
#include "..\Engine\BasicDataTypes.h"	//Vector2D
#include "..\Engine\GameObject.h"


class ParticleEmitter : public Component {
public:
	ParticleEmitter(std::string spriteFile, int totalParticles, double lifetime);
	void Emit(int number, Vector2D position, Vector2D emitterVelocity, Vector2D emitVector, double spread);
	void Clear();
private:
	class Particle : public GameObject {
	public:
		Particle(std::string spriteFile);
		void Revive(Vector2D position, Vector2D velocity, double life);
		void Update(double dt) override;
		void Draw(TransformMatrix matrix) override;
		bool IsAlive() { return life > 0; }

		GameObjectType GetObjectType() override;
		std::string GetObjectTypeName() { return "Particle"; }
	private:
		double life;
	};

	int numParticles;
	std::vector<Particle*> particles;
	int particleIndexToUse;
	double lifetime;
};

class HitParticles : public ParticleEmitter {
public:
	HitParticles();
};

class MeteorBitsParticles : public ParticleEmitter {
public:
	MeteorBitsParticles();
};
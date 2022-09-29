/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Particle.cpp
Purpose: Particle source file
Project: CS230
Author: Kevin Wright
Creation date: 5/19/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "Particle.h"


#include "../Game/GameObjectTypes.h"


HitParticles::HitParticles() : ParticleEmitter("assets/hit.spt", 30, 1) {
}

MeteorBitsParticles::MeteorBitsParticles() : ParticleEmitter("assets/particle.spt", 6, 1) {
};

ParticleEmitter::ParticleEmitter(std::string spriteFile, int numParticles, double lifetime)
				: numParticles(numParticles), lifetime(lifetime), particleIndexToUse(0) {
	for (int i = 0; i < numParticles; ++i) {
		particles.push_back(new Particle(spriteFile));
		Engine::GetGameObjectManager().Add(particles[i]);
	}
}


void ParticleEmitter::Emit(int toEmit, Vector2D emitterPosition, Vector2D emitterVelocity, Vector2D emitVector, double spread) {
	for (int i = 0; i < toEmit; i++) {
		if (particles[particleIndexToUse]->IsAlive() == true) {
			Engine::GetLogger().LogError("Particle is being overwritten");
		}

		double angleVariation = spread != 0 ? ((rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread/2 : 0;
		Vector2D particleVelocity = RotateMatrix(angleVariation) * emitVector + emitterVelocity;
		particles[particleIndexToUse++]->Revive(emitterPosition, particleVelocity, lifetime);
		if (particleIndexToUse >= numParticles) {
			particleIndexToUse = 0;
		}
	}
}

void ParticleEmitter::Clear() {
	for (Particle* particle : particles) {
		delete particle;
	}
	particles.clear();
}

ParticleEmitter::Particle::Particle(std::string spriteFile) : GameObject({ 0,0 }), life(0) {
	sprite.Load(spriteFile, this);
}

void ParticleEmitter::Particle::Revive(Vector2D newPosition, Vector2D newVelocity, double newLife) {
	life = newLife;
	SetPosition(newPosition);
	velocity = newVelocity;
	sprite.PlayAnimation(0);
}

void ParticleEmitter::Particle::Update(double dt) {
	if (IsAlive() == true) {
		life -= dt;
		GameObject::Update(dt);
	}
}

void ParticleEmitter::Particle::Draw(TransformMatrix matrix) {
	if (IsAlive() == true) {
		GameObject::Draw(matrix);
	}
}

GameObjectType ParticleEmitter::Particle::GetObjectType() {
	return GameObjectType::Particle; 
}

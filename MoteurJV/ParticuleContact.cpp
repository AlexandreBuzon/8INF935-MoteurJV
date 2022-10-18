#include "ParticuleContact.h"

void ParticuleContact::resolve(float duration) 
{
	resolveVelocity(duration);
	resolveInterpenetration(duration);
};

float ParticuleContact::calculateSeparatingVelocity() const 
{
	Vecteur3D relativeVelocity = particule[0]->velocity;
	if (particule[1]) relativeVelocity -= particule[1]->velocity;
	return relativeVelocity * contactNormal;
}

void ParticuleContact::resolveVelocity(float duration) 
{
	float separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity > 0) {
		return;
	}
	float newSepVelocity = -separatingVelocity * restitution;

	float deltaVelocity = newSepVelocity - separatingVelocity;

	float totalInverseMass = particule[0]->getInverseMass();
	if (particule[1]) totalInverseMass += particule[1]->getInverseMass();

	if (totalInverseMass <= 0) return;

	float impulse = deltaVelocity / totalInverseMass;

	Vecteur3D implulsePerMass = contactNormal * impulse;

	particule[0]->setVelocity(particule[0]->velocity + implulsePerMass * particule[0]->getInverseMass());

	if (particule[1])
	{
		particule[1]->setVelocity(particule[1]->velocity + implulsePerMass * particule[1]->getInverseMass());
	}
}

void ParticuleContact::resolveInterpenetration(float duration) 
{
	if (penetration <= 0) return;

	float totalInverseMass = particule[0]->getInverseMass();
	if (particule[1]) totalInverseMass += particule[1]->getInverseMass();

	if (totalInverseMass <= 0) return;

	Vecteur3D movePerIMass = contactNormal * (penetration / totalInverseMass);

	Vecteur3D particuleMovement[2];
	particuleMovement[0] = movePerIMass * particule[0]->getInverseMass();

	if (particule[1]) 
	{
		particuleMovement[1] = movePerIMass * -particule[1]->getInverseMass();
	}
	else 
	{
		particuleMovement[1].clear();
	}

	particule[0]->setPosition(particule[0]->position + particuleMovement[0]);
	if (particule[1]) 
	{
		particule[1]->setPosition(particule[1]->position + particuleMovement[1]);
	}
}

void ParticuleContact::resolveVelocity(float duration) 
{
	float separatingVelocity = calculateSeparatingVelocity();

	if (separatingVelocity > 0) 
	{
		return;
	}

	float newSepVelocity = -separatingVelocity * restitution;

	Vecteur3D accCausedVelocity = particule[0]->acceleration;
	if (particule[1]) accCausedVelocity -= particule[1]->acceleration;
	float accCausedSepVelocity = accCausedVelocity * contactNormal * duration;

	if (accCausedSepVelocity < 0)
	{
		newSepVelocity += restitution * accCausedSepVelocity;
		if (newSepVelocity < 0) newSepVelocity = 0;
	}

	float deltaVelocity = newSepVelocity - separatingVelocity;

	float totalInverseMass = particule[0]->getInverseMass();
	if (particule[1]) totalInverseMass += particule[1]->getInverseMass();

	if (totalInverseMass <= 0) return;
	float impulse = deltaVelocity / totalInverseMass;
	Vecteur3D impulsePerIMass = contactNormal * impulse;

	particule[0]->setVelocity(particule[0]->velocity + impulsePerIMass * particule[0]->getInverseMass());

	if (particule[1]) 
	{
		particule[1]->setVelocity(particule[1]->velocity + impulsePerIMass * -particule[1]->getInverseMass());
	}

}
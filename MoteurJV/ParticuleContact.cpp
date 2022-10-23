#include "ParticuleContact.h"

ParticuleContact::ParticuleContact() {

	particule[0] = NULL;
	particule[1] = NULL;

	restitution = 0;

	penetration = 0;

	contactNormal = Vecteur3D();

}

ParticuleContact::ParticuleContact(float restit, float pene, Vecteur3D contactNormal,
	Particle* p_P1, Particle* p_P2) {

	particule[0] = p_P1;
	particule[1] = p_P2;

	restitution = restit;

	penetration = pene;

	this->contactNormal = contactNormal;

}

ParticuleContact::~ParticuleContact(){}

void ParticuleContact::resolve(float duration) 
{
	resolveVelocity(duration);
	resolveInterpenetration(duration);
};

const float ParticuleContact::calculateSeparatingVelocity()
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

	Vecteur3D impulsePerMass = contactNormal * impulse;

	particule[0]->setVelocity(particule[0]->velocity + impulsePerMass * particule[0]->getInverseMass());

	if (particule[1])
	{
		particule[1]->setVelocity(particule[1]->velocity + impulsePerMass * particule[1]->getInverseMass());
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
		//particuleMovement[1].clear;
	}

	particule[0]->setPosition(particule[0]->position + particuleMovement[0]);
	if (particule[1]) 
	{
		particule[1]->setPosition(particule[1]->position + particuleMovement[1]);
	}
}
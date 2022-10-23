#include "ParticuleContactResolver.h"
#include "ParticuleContact.h"

void ParticuleContactResolver::resolveContacts(ParticuleContact* contactArray, unsigned int numContacts, float duration) 
{
	unsigned i;

	iterationUsed = 0;
	while (iterationUsed < iteration) 
	{
		float max;
		unsigned maxIndex = numContacts;
		for (i = 0; i < numContacts; i++) 
		{
			float sepVel = contactArray[i].calculateSeparatingVelocity();
			if (sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0)) 
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		if (maxIndex == numContacts) break;
		contactArray[maxIndex].resolve(duration);
		iterationUsed++;
	}
}
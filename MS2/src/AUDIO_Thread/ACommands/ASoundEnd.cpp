#include "ASoundEnd.h"
#include "ASoundManager.h"

ASoundEnd::ASoundEnd(SndID snd_id, Sounds* p)
	:ACommand(snd_id, p)
{
}

void ASoundEnd::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASounds* pA;
	this->pSnd->GetASound(pA);
	assert(pA);

	// Now End the sound
	pA->SoundEnd();

}

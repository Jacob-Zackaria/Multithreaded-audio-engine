#include "AStopSound.h"
#include "ASoundManager.h"

AStopSound::AStopSound(SndID snd_id, Sounds* p)
	:ACommand(snd_id, p)
{
}

void AStopSound::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASounds* pA;
	this->pSnd->GetASound(pA);
	assert(pA);

	// Now play it
	pA->SoundEnd();

}
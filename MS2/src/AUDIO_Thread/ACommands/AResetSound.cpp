#include "AResetSound.h"
#include "ASoundManager.h"

AResetSound::AResetSound(SndID snd_id, Sounds* p)
	:ACommand(snd_id, p)
{
}

void AResetSound::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASounds* pA;
	this->pSnd->GetASound(pA);
	assert(pA);

	// Now play it
	pA->Reset();

}
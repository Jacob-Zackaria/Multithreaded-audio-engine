#include "APlaySound.h"
#include "ASoundManager.h"

APlaySound::APlaySound(SndID snd_id, Sounds* p)
	:ACommand(snd_id, p)
{
}

void APlaySound::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASounds* pA;
	this->pSnd->GetASound(pA);
	assert(pA);

	// Now play it
	pA->Play();

}
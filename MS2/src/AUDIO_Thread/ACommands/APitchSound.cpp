#include "APitchSound.h"
#include "ASoundManager.h"

APitchSound::APitchSound(SndID snd_id, Sounds* p, float snd_pitch)
	:ACommand(snd_id, p), pitch(snd_pitch)
{
}

void APitchSound::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASounds* pA;
	this->pSnd->GetASound(pA);
	assert(pA);

	// Now play it
	pA->SetPitch(this->pitch);

}
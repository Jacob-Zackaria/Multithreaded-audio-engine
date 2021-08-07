//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AVolSound.h"
#include "ASoundManager.h"

AVolSound::AVolSound(SndID snd_id, Sounds* p, float snd_vol)
	:ACommand(snd_id, p), vol(snd_vol)
{
}

void AVolSound::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASounds* pA;
	this->pSnd->GetASound(pA);
	assert(pA);

	// Now change its attributes
	pA->SetVolume(this->vol);

}

// --- End of File ---

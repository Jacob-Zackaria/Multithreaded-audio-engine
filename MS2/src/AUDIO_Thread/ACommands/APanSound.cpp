//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "APanSound.h"
#include "ASoundManager.h"

APanSound::APanSound(SndID snd_id, Sounds* p, float snd_pan)
	:ACommand(snd_id, p), pan(snd_pan)
{
}

void APanSound::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASounds* pA;
	this->pSnd->GetASound(pA);
	assert(pA);

	// Now play it
	pA->SetPan(this->pan);

}

// --- End of File ---

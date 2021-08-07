#include "APrempt.h"
#include "ASoundManager.h"

APrempt::APrempt(SndID snd_id, Sounds* p, Sounds* pOld)
	:ACommand(snd_id, p),
	oldSound(pOld)
{
}

void APrempt::Execute()
{
	assert(this->pSnd);
	assert(this->oldSound);

	// Get the ASnd
	ASounds* pA;
	this->oldSound->GetASound(pA);
	assert(pA);

	// Now play it
	pA->SoundEnd();

	// add new sound.
	this->pSnd->Play();

	// Print snd priority table
	Sounds::PrintPriorityTable();

}
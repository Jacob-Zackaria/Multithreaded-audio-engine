#include "ACommandQueue.h"
#include "SoundManager.h"
#include "ASounds.h"
#include "SndID.h"
#include "ASoundEnd.h"

void ACommandQueue::SoundEnd(ASounds* pASnd)
{
	// Place the Play command in the queue to the Audio thread
	CircularData* pOut = SoundManager::GetG2A();
	assert(pOut);

	SndID id;
	assert(pASnd);
	Handle::Status status = pASnd->GetId(id);
	assert(status == Handle::Status::SUCCESS);

	Sounds* pSnd = pASnd->GetSound();
	assert(pSnd);

	Command* pCmd = new ASoundEnd(id, pSnd);
	assert(pCmd);

	pOut->PushBack(pCmd);
}
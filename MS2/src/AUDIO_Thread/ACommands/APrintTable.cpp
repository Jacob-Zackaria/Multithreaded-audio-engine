#include "APrintTable.h"
#include "ASoundManager.h"

APrintTable::APrintTable(SndID snd_id, Sounds* pSnd)
	:ACommand(snd_id, pSnd)
{
}

void APrintTable::Execute()
{
	// Print snd priority table
	Sounds::PrintPriorityTable();
}
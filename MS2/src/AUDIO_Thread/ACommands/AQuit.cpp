//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AQuit.h"
#include "ASoundManager.h"

AQuit::AQuit(SndID snd_id, Sounds* p)
	:ACommand(snd_id, p)
{
}

void AQuit::Execute()
{
	ASoundManager::SetQuit();
}

// --- End of File ---

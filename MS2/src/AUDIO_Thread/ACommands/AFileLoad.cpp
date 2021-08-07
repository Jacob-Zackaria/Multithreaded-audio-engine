//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"
#include "AFileLoad.h"
#include "WaveManager.h"

AFileLoad::AFileLoad(const char * const _pWaveName, Wave::ID name, FileUserCallback *pFileCB)
	: 	pFileUserCallback(pFileCB),
	waveID(name),
	pWaveName(_pWaveName)
{
}

void AFileLoad::Execute()
{
	Trace::out("\n%s AFileLoad: \n  callback:%p, \n  waveID:%x, \n  wavename:%s \n", ThreadHelper::GetThreadName(), pFileUserCallback, waveID, pWaveName);

	WaveManager::Add(pWaveName, waveID, pFileUserCallback);

}

// --- End of File ---

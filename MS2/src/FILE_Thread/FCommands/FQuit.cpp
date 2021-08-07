//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FQuit.h"
#include "FileManager.h"

FQuit::FQuit()
	:FCommand()
{
}

void FQuit::Execute()
{
	FileManager::SetQuit();
}

// --- End of File ---

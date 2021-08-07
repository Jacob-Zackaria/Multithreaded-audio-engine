//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FileMain.h"
#include "FileManager.h"
#include "ThreadHelper.h"


//-------------------------------------------------------------
// Audio thread main (loop)
//-------------------------------------------------------------
void FileMain()
{
	ThreadHelper::DebugBegin(2);

	while (!FileManager::IsQuit())
	{
		Command *pCmd = nullptr;

		// Any commands to process?
		if (FileManager::GetFileInQueue()->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();

			// Commands are instantly killed after execution
			// todo... recycle commands

			delete pCmd;
		}
		// delay 1 ms
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	ThreadHelper::DebugEnd(2);
}

// --- End of File ---

#include "ThreadHelper.h"
#include "AudioThread.h"
#include "SoundManager.h"
#include "ASoundManager.h"

void Audio_Main()
{
	ThreadHelper::DebugBegin(1);

	//----------------------------------------------
	// Loop.
	//----------------------------------------------
	while (!ASoundManager::IsQuit())
	{
		Command* pCmd = nullptr;

		// Any commands to process?
		if (SoundManager::GetG2A()->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();

			// Commands are instantly killed after execution
			// todo... recycle commands

			delete pCmd;
		}
		// delay 1 ms.
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	Trace::out("\n");
	ThreadHelper::DebugEnd(1);
}
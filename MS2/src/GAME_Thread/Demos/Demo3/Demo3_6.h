//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_6_H
#define DEMO3_6_H

#include "Command.h"
#include "SoundManager.h"
#include "APrintTable.h"

class Demo3_6 : public Command
{
public:
	Demo3_6() = default;
	~Demo3_6() = default;
	Demo3_6(const Demo3_6&) = delete;
	Demo3_6& operator = (const Demo3_6&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (13 sec) --\n");
		Trace::out("Stop All\n");
		// Stop all pending sounds.
		Sounds::StopPendingSounds();

		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SoundManager::GetG2A();
		assert(pOut);

		Sounds pS;
		Command* pCmd = new APrintTable(SndID::Uninitialized, &pS);
		pOut->PushBack(pCmd);
	}

};

#endif

// --- End of File ---

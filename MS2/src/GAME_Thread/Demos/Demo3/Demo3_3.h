//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_3_H
#define DEMO3_3_H

#include "Command.h"
#include "SoundManager.h"
class Demo3_3 : public Command
{
public:
	Demo3_3() = default;
	~Demo3_3() = default;
	Demo3_3(const Demo3_3 &) = delete;
	Demo3_3 & operator = (const Demo3_3 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (3 sec) --\n");
		Trace::out("Priority : 100\n");
		// Play A

		Sounds *pSndA = SoundManager::Add(SndID::Coma, nullptr, 100);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->SetVol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Print snd priority table
		Sounds::PrintPriorityTable();
	
	}

};

#endif

// --- End of File ---

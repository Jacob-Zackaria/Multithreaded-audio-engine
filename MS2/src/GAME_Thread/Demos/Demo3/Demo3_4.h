//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_4_H
#define DEMO3_4_H

#include "Command.h"
#include "SoundManager.h"
class Demo3_4 : public Command
{
public:
	Demo3_4(int time) : newTime(time) {}
	~Demo3_4() = default;
	Demo3_4(const Demo3_4 &) = delete;
	Demo3_4 & operator = (const Demo3_4 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (%d sec) --\n", this->newTime);
		Trace::out("Priority : 150\n");
		// Play A

		Sounds *pSndA = SoundManager::Add(SndID::Coma, nullptr, 150);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->SetVol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

	}
private:
	int newTime;
};

#endif

// --- End of File ---

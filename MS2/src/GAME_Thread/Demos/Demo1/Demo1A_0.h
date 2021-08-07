
//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1A_0_H
#define DEMO1A_0_H

#include "Command.h"
#include "SoundManager.h"

class Demo1A_0 : public Command
{
public:
	Demo1A_0() = default;
	~Demo1A_0() = default;
	Demo1A_0(const Demo1A_0&) = delete;
	Demo1A_0& operator = (const Demo1A_0&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n101 - Fiddle: (0 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.7f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");

		// Create a Snd Call
		Sounds* pSndA = SoundManager::Add(SndID::Fiddle, nullptr, 200);
		assert(pSndA);

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}
};


#endif

// --- End of File ---

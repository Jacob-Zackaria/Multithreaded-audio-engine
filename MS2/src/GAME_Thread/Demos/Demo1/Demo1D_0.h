#ifndef DEMO1D_0_H
#define DEMO1D_0_H

#include "Command.h"
#include "SoundManager.h"

class Demo1D_0 : public Command
{
public:
	Demo1D_0() = default;
	~Demo1D_0() = default;
	Demo1D_0(const Demo1D_0&) = delete;
	Demo1D_0& operator = (const Demo1D_0&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n104 - SongA: (30 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.7f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");

		// Create a Snd Call
		Sounds* pSndA = SoundManager::Add(SndID::SongA, nullptr, 200);
		assert(pSndA);

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}
};


#endif
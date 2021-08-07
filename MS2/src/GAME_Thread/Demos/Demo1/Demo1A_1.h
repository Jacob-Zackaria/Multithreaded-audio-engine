#ifndef DEMO1A_1_H
#define DEMO1A_1_H

#include "Command.h"
#include "SoundManager.h"

class Demo1A_1 : public Command
{
public:
	Demo1A_1() = default;
	~Demo1A_1() = default;
	Demo1A_1(const Demo1A_1&) = delete;
	Demo1A_1& operator = (const Demo1A_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n101 - Fiddle: (3 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.7f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");

		// Create a Snd Call
		Sounds* pSndA = SoundManager::Add(SndID::Fiddle, nullptr, 200);
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

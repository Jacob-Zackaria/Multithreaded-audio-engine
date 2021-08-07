#ifndef DEMO5_1_H
#define DEMO5_1_H

#include "Command.h"
#include "SoundManager.h"

class Demo5_1 : public Command
{
public:
	Demo5_1(int time) : newTime(time) {}
	~Demo5_1() = default;
	Demo5_1(const Demo5_1&) = delete;
	Demo5_1& operator = (const Demo5_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (%d sec) --\n", this->newTime);
		Trace::out("\n502 - Alarm:\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.3f | Pan : Left |\n Pitch : 1.0f | Priority : 200 |\n");
		// create a sound call.
		Sounds* pSndA = SoundManager::Add(SndID::Alarm, nullptr, 200);


		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}
private:
	int newTime;
};

#endif
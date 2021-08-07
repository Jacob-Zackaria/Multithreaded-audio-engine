#ifndef DEMO2A_1_H
#define DEMO2A_1_H

#include "Command.h"
#include "SoundManager.h"
#include "TimeEventManager.h"

class Demo2A_1 : public Command
{
public:
	Demo2A_1(int time) : newTime(time) {}
	~Demo2A_1() = default;
	Demo2A_1(const Demo2A_1&) = delete;
	Demo2A_1& operator = (const Demo2A_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n-- (%d sec) --\n", this->newTime);
		// create a sound call.
		Sounds* pSndA = SoundManager::Find(SndID::Intro_mono);

		Trace::out(" Vol : 0.8f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.8f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
	}
private:
	int newTime;
};


#endif
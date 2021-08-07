#ifndef DEMO1B_1_H
#define DEMO1B_1_H

// Command stuff
#include "Command.h"
#include "SoundManager.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1B_1_Main(Sounds* pSnd);

// Command
class Demo1B_1 : public Command
{
public:
	Demo1B_1() = default;
	~Demo1B_1() = default;
	Demo1B_1(const Demo1B_1&) = delete;
	Demo1B_1& operator = (const Demo1B_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n102 - Bassoon: (15 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.7f | Pan : Right to Left (2 sec) |\n Pitch : 1.0f | Priority : 200 |\n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

		Sounds* pSndA = SoundManager::Add(SndID::Bassoon, nullptr, 200);
		assert(pSndA);

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

		std::thread  Demo1B_1_Thread(Demo1B_1_Main, pSndA);
		ThreadHelper::SetThreadName(Demo1B_1_Thread, "DEMO_1B_1");
		Demo1B_1_Thread.detach();
	}
};




#endif
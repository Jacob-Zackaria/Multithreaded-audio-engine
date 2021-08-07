#ifndef DEMO1B_0_H
#define DEMO1B_0_H

// Command stuff
#include "Command.h"
#include "SoundManager.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1B_0_Main(Sounds* pSnd);

// Command
class Demo1B_0 : public Command
{
public:
	Demo1B_0() = default;
	~Demo1B_0() = default;
	Demo1B_0(const Demo1B_0&) = delete;
	Demo1B_0& operator = (const Demo1B_0&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n102 - Bassoon: (10 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 0.7f | Pan : Left to Right (2 sec) |\n Pitch : 1.0f | Priority : 200 |\n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

		Sounds* pSndA = SoundManager::Add(SndID::Bassoon, nullptr, 200);
		assert(pSndA);

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(-1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);
	
		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

		std::thread  Demo1B_0_Thread(Demo1B_0_Main, pSndA);
		ThreadHelper::SetThreadName(Demo1B_0_Thread, "DEMO_1B_0");
		Demo1B_0_Thread.detach();
	}
};




#endif
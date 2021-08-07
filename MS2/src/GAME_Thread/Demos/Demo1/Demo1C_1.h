#ifndef DEMO1C_1_H
#define DEMO1C_1_H

// Command stuff
#include "Command.h"
#include "SoundManager.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1C_1_Main(Sounds* pSnd);

// Command
class Demo1C_1 : public Command
{
public:
	Demo1C_1() = default;
	~Demo1C_1() = default;
	Demo1C_1(const Demo1C_1&) = delete;
	Demo1C_1& operator = (const Demo1C_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("\n103 - Oboe: (25 sec)\n");
		Trace::out("*************** Sound start *************\n");
		Trace::out(" Vol : 1.0f to 0.0f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

		Sounds* pSndA = SoundManager::Add(SndID::Oboe, nullptr, 200);
		assert(pSndA);

		// Vol, Pan & Pitch
		assert(pSndA->SetVol(1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

		std::thread  Demo1C_1_Thread(Demo1C_1_Main, pSndA);
		ThreadHelper::SetThreadName(Demo1C_1_Thread, "DEMO_1C_1");
		Demo1C_1_Thread.detach();
	}
};




#endif
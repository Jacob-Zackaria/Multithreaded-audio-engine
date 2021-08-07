#include "Demo1E_0.h"
#include "Timer.h"

void Demo1E_1_Main()
{
	// ---- SOUND A ----
	Trace::out("\n102 - Bassoon: (80 sec)\n");
	Trace::out("*************** Sound start *************\n");
	Trace::out(" Vol : 0.4f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");

	// Create a Snd Call
	Sounds* pSndA = SoundManager::Add(SndID::Bassoon, nullptr, 200);
	assert(pSndA);

	// Vol, Pan & Pitch
	assert(pSndA->SetVol(0.4f) == Handle::Status::SUCCESS);
	assert(pSndA->SetPan(0.0f) == Handle::Status::SUCCESS);
	assert(pSndA->SetPitch(1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndA->Play() == Handle::Status::SUCCESS);

	// delay 0.5 sec
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// ---- SOUND B ----
	Trace::out("\n102 - Bassoon: (80.5 sec)\n");
	Trace::out("*************** Sound start *************\n");
	Trace::out(" Vol : 0.4f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");

	Sounds* pSndB = SoundManager::Add(SndID::Bassoon, nullptr, 200);
	assert(pSndB);

	// Vol, Pan & Pitch
	assert(pSndB->SetVol(0.4f) == Handle::Status::SUCCESS);
	assert(pSndB->SetPan(0.0f) == Handle::Status::SUCCESS);
	assert(pSndB->SetPitch(1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndB->Play() == Handle::Status::SUCCESS);

	// delay 0.5 sec
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// ---- SOUND C ----
	Trace::out("\n102 - Bassoon: (81 sec)\n");
	Trace::out("*************** Sound start *************\n");
	Trace::out(" Vol : 0.4f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");

	Sounds* pSndC = SoundManager::Add(SndID::Bassoon, nullptr, 200);
	assert(pSndC);

	// Vol, Pan & Pitch
	assert(pSndC->SetVol(0.4f) == Handle::Status::SUCCESS);
	assert(pSndC->SetPan(0.0f) == Handle::Status::SUCCESS);
	assert(pSndC->SetPitch(1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndC->Play() == Handle::Status::SUCCESS);

	// delay 0.5 sec
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	// ---- SOUND D ----
	Trace::out("\n102 - Bassoon: (81.5 sec)\n");
	Trace::out("*************** Sound start *************\n");
	Trace::out(" Vol : 0.4f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");

	Sounds* pSndD = SoundManager::Add(SndID::Bassoon, nullptr, 200);
	assert(pSndD);

	// Vol, Pan & Pitch
	assert(pSndD->SetVol(0.4f) == Handle::Status::SUCCESS);
	assert(pSndD->SetPan(0.0f) == Handle::Status::SUCCESS);
	assert(pSndD->SetPitch(1.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndD->Play() == Handle::Status::SUCCESS);

	assert(pSndA->Stop() == Handle::Status::SUCCESS);
	assert(pSndB->Stop() == Handle::Status::SUCCESS);
	assert(pSndC->Stop() == Handle::Status::SUCCESS);
}
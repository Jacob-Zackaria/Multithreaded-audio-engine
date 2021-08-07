//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FileUserCallBack.h"
#include "SoundManager.h"

void FileUserCallback::Set(SndID _sndID)
{
	this->sndID = _sndID;
}

void FileUserCallback::Execute()
{
	Trace::out("------------------------------\n");
	Trace::out("  FileUserCallback() \n");
	Trace::out("------------------------------\n");
	Trace::out("     Play(%d)\n",this->sndID);
	Trace::out("\n503 - Beethoven:\n");
	Trace::out("*************** Sound start *************\n");
	Trace::out(" Vol : 0.5f | Pan : Center |\n Pitch : 1.0f | Priority : 200 |\n");
	// find electro
	Sounds* pSndB = SoundManager::Find(SndID::Electro);
	assert(pSndB);

	// stop
	pSndB->Stop();

	Sounds *pSndC = SoundManager::Add(this->sndID, nullptr, 200);
	assert(pSndC);

	// Vol & Pan
	assert(pSndC->SetVol(0.50f) == Handle::Status::SUCCESS);
	assert(pSndC->SetPan(0.0f) == Handle::Status::SUCCESS);
	assert(pSndC->SetPitch(1.0f) == Handle::Status::SUCCESS);
	// Call the sound
	assert(pSndC->Play() == Handle::Status::SUCCESS);


	Trace::out("------------------------------\n");
}

// --- End of File ---

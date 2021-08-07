//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FileManager.h"
#include "SoundManager.h"
#include "AFileLoad.h"
#include "FQuit.h"
#include "WaveManager.h"
FileManager::FileManager()
{
	this->poFileInQueue = new CircularData();
	assert(poFileInQueue);

	this->QuitFlag = false;
}

FileManager::~FileManager()
{
	assert(FileManager::IsQuit() == true);

	// We created it... so we delete it
	delete this->poFileInQueue;

	
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------

Wave::Status FileManager::GetStatus(Wave::ID id)
{
	FileManager* pMan = FileManager::privGetInstance();
	assert(pMan != nullptr);

	Wave::Status status = Wave::Status::UNINITIALIZED;

	Wave* pWave = WaveManager::Find(id);
	if (pWave)
	{
		status = pWave->WaveStatus;
	}

	return status;
}

void FileManager::Quit()
{
	FileManager* pMan = FileManager::privGetInstance();
	assert(pMan != nullptr);

	// Place the "Quit" command in the queue 
	CircularData* pOut = FileManager::GetFileInQueue();
	assert(pOut);

	Command* pCmd = new FQuit();
	assert(pCmd);

	pOut->PushBack(pCmd);
}


CircularData * FileManager::GetFileInQueue()
{
	FileManager *pMan = FileManager::privGetInstance();
	return pMan->poFileInQueue;
}

Handle::Status FileManager::Add(const char * const pWaveName, Wave::ID name, FileUserCallback *pFileCallback)
{
	FileManager *pMan = FileManager::privGetInstance();
	assert(pMan != nullptr);

	Handle::Lock lock(pMan->handle);

	if (lock)
	{
		// Now create a the sound call on the Audio thread
		// Place the "Create" command in the queue to the Audio thread
		CircularData *pOut = SoundManager::GetG2A();
		assert(pOut);

		// Doesn't need to know snd_priority its only on game side
		Command *pCmd = new AFileLoad(pWaveName, name, pFileCallback);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	else
	{
		assert(false);
	}

	//Trace::out("SndMan::Add() unlock\n");
	return lock;
}

void FileManager::SetQuit()
{
	FileManager* pMan = FileManager::privGetInstance();
	assert(pMan != nullptr);

	pMan->QuitFlag = true;
}

bool  FileManager::IsQuit()
{
	FileManager* pMan = FileManager::privGetInstance();
	assert(pMan != nullptr);

	return pMan->QuitFlag;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
FileManager * FileManager::privGetInstance()
{
	static FileManager fileMan;

	return &fileMan;
}


// --- End of File ---

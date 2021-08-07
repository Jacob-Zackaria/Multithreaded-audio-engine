//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


#include "PlayListManager.h"
#include "SoundManager.h"
#include "ASoundManager.h"
#include "GUserCallback.h"
ASounds::ASounds()
	: id(SndID::Uninitialized),
	pPlaylist(nullptr),
	pSnd(nullptr),
	poUserCallback(nullptr),
	vol(0.7f),
	pan(0.0f),
	pitch(1.0f),
	handle()
{
}

Handle::Status  ASounds::SoundEnd()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		Trace::out("*************** Sound end ***************\n");

		assert(this->id != SndID::Uninitialized);
		assert(this->pPlaylist);

		// UserCallback?
		if (this->poUserCallback)
		{
			// HaCK ALERT7
			char* pName = this->pPlaylist->pVoice->pWave->strName;
			assert(pName);

			int timeInMS;
			this->pSnd->GetTimeInMS(timeInMS);

			this->poUserCallback->Set(this->pSnd, pName, timeInMS);


			GUserCallback* pGUserCB = new GUserCallback(this->poUserCallback);
			assert(pGUserCB);

			//ownership was transfered to GUserCallback
			this->poUserCallback = nullptr;

			CircularData* pQueue = SoundManager::GetA2G();
			assert(pQueue);
			pQueue->PushBack(pGUserCB);

		}

		// Playlist (which will deal with Voice)
		pPlaylist->SoundEnd();

		// Snd needs to be alerted
		assert(this->pSnd);
		this->pSnd->RemoveFromPriorityTable();
		this->pSnd->SetASound(nullptr);
		SoundManager::Remove(this->pSnd);

		// ASndMan - remove from the active list
		this->pSnd = nullptr;
		ASoundManager::Remove(this);
		//Sounds::PrintPriorityTable();
	}
	return lock;
}

Handle::Status ASounds::SetId(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;
	}
	return lock;
}

Handle::Status ASounds::GetId(SndID& _id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

void ASounds::SetSound(Sounds* _pSnd)
{
	assert(_pSnd);
	this->pSnd = _pSnd;
}

Sounds* ASounds::GetSound()
{
	return this->pSnd;
}

Handle::Status ASounds::Wash()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Wash - clear the entire hierarchy
		DLink::ClearLink();

		// Sub class clear
		this->privClear();
	}
	return lock;
}

Handle::Status ASounds::Set(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pPlaylist = PlayListManager::Add(snd_id);
		this->id = snd_id;
		this->pSnd = nullptr;
		this->vol = 0.7f;
		this->pan = 0.0f;
		this->pitch = 1.0f;
	}
	return lock;
}

void ASounds::privClear()
{
	this->id = SndID::Uninitialized;
	// Remove the playlist if recycling
	if (this->pPlaylist)
	{
		PlayListManager::Remove(this->pPlaylist);
		this->pPlaylist = nullptr;
	}

	this->pSnd = nullptr;
	this->vol = 0.7f;
	this->pan = 0.0f;
	this->pitch = 1.0f;
}

Handle::Status ASounds::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %d (%p) \n", this->id, this);
	}
	return lock;
}

Handle::Status ASounds::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// start voice.
		this->pPlaylist->Play();

	}

	return lock;
}

Handle::Status ASounds::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		//stop voice.
		this->pPlaylist->Stop();
	}

	return lock;
}

Handle::Status ASounds::Reset()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		//stop voice.
		this->pPlaylist->Reset();
	}

	return lock;
}

Handle::Status ASounds::SetVolume(const float newVol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pPlaylist->SetVolume(newVol);
		this->vol = newVol;
	}

	return lock;
}

Handle::Status ASounds::GetVolume(float& newVol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pPlaylist->GetVolume(newVol);
	}

	return lock;
}

Handle::Status ASounds::SetPan(const float newPan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pPlaylist->SetPan(newPan);
		this->pan = newPan;
	}

	return lock;
}

Handle::Status ASounds::GetPan(float& newPan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pPlaylist->GetPan(newPan);
	}

	return lock;
}

Handle::Status ASounds::SetPitch(const float newPitch)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pPlaylist->SetPitch(newPitch);
		this->pitch = newPitch;
	}

	return lock;
}

Handle::Status ASounds::GetPitch(float& newPitch)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pPlaylist->GetPitch(newPitch);
	}

	return lock;
}


ASounds::~ASounds()
{
	this->privClear();
}

// --- End of File ---

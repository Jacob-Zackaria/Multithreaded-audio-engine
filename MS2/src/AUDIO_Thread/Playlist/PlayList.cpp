#include "PlayList.h"
#include "AudioEngine.h"
#include "Playlist.h"
#include "VoiceManager.h"


Playlist::Playlist()
	: //poScript(nullptr),
	pVoice(nullptr),
	id(SndID::Uninitialized),
	handle()
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Handle::Status Playlist::Wash()
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

Handle::Status Playlist::Set(SndID snd_id, Voice::ID voice_id, Wave::ID wave_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;
		
		this->pVoice = VoiceManager::Add(voice_id, wave_id);
		
		assert(this->pVoice);
	}
	return lock;
}

void Playlist::privClear()
{
	this->pVoice = nullptr;

	// Command pattern
	//this->poScript = nullptr;

	this->id = SndID::Uninitialized;
}

Handle::Status Playlist::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %d (%p) \n", this->id, this);
	}
	return lock;
}


Handle::Status Playlist::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// start voice.
		this->pVoice->Start();
	}

	return lock;
}

Handle::Status Playlist::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		//stop voice.
		this->pVoice->Stop();
	}

	return lock;
}

Handle::Status Playlist::Reset()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		//stop voice.
		this->pVoice->Stop();

		// flush queued buffers.
		this->pVoice->FlushBuffer();

		// sumbit buffer.
		this->pVoice->ReSubmitBuffer();
	}

	return lock;
}

Handle::Status Playlist::SetVolume(const float vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pVoice->SetVolume(vol);
	}

	return lock;
}

Handle::Status Playlist::GetVolume(float& vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pVoice->GetVolume(vol);
	}

	return lock;
}

Handle::Status Playlist::SetPan(const float pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pVoice->SetPan(pan);
	}

	return lock;
}

Handle::Status Playlist::GetPan(float& pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pVoice->GetPan(pan);
	}

	return lock;
}

Handle::Status Playlist::SetPitch(const float pitch)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pVoice->SetPitch(pitch);
	}

	return lock;
}

Handle::Status Playlist::GetPitch(float& pitch)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pVoice->GetPitch(pitch);
	}

	return lock;
}

Handle::Status Playlist::SoundEnd()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pVoice);

		// Stop the voice if its not already stopped
		this->pVoice->Stop();

		// Now remove it off the active
		VoiceManager::Remove(this->pVoice);
	}
	return lock;
}

Playlist::~Playlist()
{
	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

Handle::Status Playlist::SetId(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;
	}
	return lock;
}

Handle::Status Playlist::GetId(SndID& _id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

// --- End of File ---

//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_SOUNDS_H
#define A_SOUNDS_H

#include "DLink.h"
#include "SndID.h"
#include "Handle.h"
#include "Playlist.h"
class UserCallback;
class Sounds;
// This class is only there for pretty UML
class ASounds_Link : public DLink
{
};
class ASounds : public ASounds_Link
{
public:
	ASounds();
	ASounds(const ASounds&) = delete;
	ASounds& operator = (const ASounds&) = delete;
	~ASounds();

	Handle::Status SetId(SndID);
	Handle::Status GetId(SndID&);

	Handle::Status Set(SndID snd_id);

	Handle::Status Dump();
	Handle::Status Wash();

	// sound functions.
	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status Reset();
	Handle::Status SetVolume(const float vol);
	Handle::Status GetVolume(float& vol);
	Handle::Status SetPan(const float pan);
	Handle::Status GetPan(float& pan);
	Handle::Status SetPitch(const float pitch);
	Handle::Status GetPitch(float& pitch);


	Handle::Status SoundEnd();
	void SetSound(Sounds* pSnd);
	Sounds* GetSound();
private:
	void privClear();

	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

public:
	SndID	 id;
	Playlist* pPlaylist;
	Sounds* pSnd;
	UserCallback* poUserCallback;

	float vol;
	float pan;
	float pitch;

	// Protect it with a handle
	Handle	handle;
};

#endif

// --- End of File ---

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Handle.h"
#include "DLink.h"
#include "Wave.h"
#include "SndID.h"
#include "Voice.h"


//class PLScript
//{
//	// Future
//	// Command pattern
//};

// This class is only there for pretty UML
class Playlist_Link : public DLink
{
};
class Playlist : public Playlist_Link
{
public:
	// Big 4
	Playlist();
	Playlist(const Playlist&) = delete;
	Playlist& operator = (const Playlist&) = delete;
	virtual ~Playlist();

	Handle::Status Set(SndID snd_id, Voice::ID voice_id, Wave::ID wave_id);

	// Manager methods
	Handle::Status GetId(SndID&);
	Handle::Status SetId(SndID);

	Handle::Status Wash();
	Handle::Status Dump();

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

private:
	void privClear();

public:
	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------
	//PLScript* poScript;
	Voice* pVoice;
	SndID     id;

	Handle handle;
};

#endif


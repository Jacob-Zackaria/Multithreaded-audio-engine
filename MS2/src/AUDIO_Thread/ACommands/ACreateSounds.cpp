#include "ACreateSounds.h"
#include "ASoundManager.h"
#include "SourceCallback.h"
#include "UserCallBack.h"

ACreateSounds::ACreateSounds(SndID snd_id, Sounds* p, UserCallback* _pUserCallback)
	:ACommand(snd_id, p),
	pUserCallback(_pUserCallback)
{
}

void ACreateSounds::Execute()
{
	assert(this->id != SndID::Uninitialized);

	ASounds* pA = ASoundManager::Add(this->id);
	assert(pA);

	// Update the SND call
	// This way its faster to execute commands on the Audio thread side

	assert(this->pSnd);
	pSnd->SetASound(pA);
	pA->SetSound(pSnd);
	// user callback
	pA->poUserCallback = this->pUserCallback;
	// Set the ASnd pointer in the VoiceCallback - HACK
	// Not sure if this is the best place for this...
	Playlist* pPlaylist = pA->pPlaylist;
	assert(pPlaylist);

	Voice* pVoice = pPlaylist->pVoice;
	assert(pVoice);

	// OK to down cast this... might want to change voice.h to use VoiceCallback
	SourceCallback* pCallback = (SourceCallback*)pVoice->poCallback;
	assert(pCallback);

	pCallback->SetASound(pA);

}
#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

//Header file for xaudio2 API.
#include "XAudioHeaders.h"

class AudioEngine
{

public:

	//--------------------------------------------------------------
	// PUBLIC DATA.
	//--------------------------------------------------------------

	// master voice details.
	XAUDIO2_VOICE_DETAILS masterVoiceDetails;

public:

	//--------------------------------------------------------------
	// BIG FOUR.
	//--------------------------------------------------------------

	// copy constructor.
	AudioEngine(const AudioEngine&) = delete;

	// assignment operator.
	AudioEngine& operator = (const AudioEngine&) = delete;

	// destructor.
	~AudioEngine();

	static IXAudio2* GetXAudio2();
	static IXAudio2MasteringVoice* GetMasterVoice();

private:

	// default constructor.
	AudioEngine();

	//--------------------------------------------------------------
	// INITIALIZATION FUNCTIONS.
	//--------------------------------------------------------------

	// initialize COM Thread.
	const HRESULT StartCOMThread();

	// initialize COM Thread.
	void EndCOMThread();

	// create an audio engine instance.
	const HRESULT CreateEngine();

	// create a mastering voice.
	const HRESULT CreateMasterVoice();

private:

	//---------------------------------------------------------------
	// DATA.
	//---------------------------------------------------------------

	// engine instance.
	IXAudio2* pXAudio2;

	// master voice.
	IXAudio2MasteringVoice* pMasterVoice;

	// get audio engine instance.
	static AudioEngine* GetPrivateInstance();

	// singleton instance.
	static AudioEngine* pInstance;

};

#endif
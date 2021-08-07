#include "AudioEngine.h"

// constructor.
AudioEngine::AudioEngine()
	: pXAudio2(nullptr),
	pMasterVoice(nullptr)
{
    // Initialize COM Thread.
    HRESULT hr = this->StartCOMThread();

    // verify COM is created.
    assert(hr == S_OK);

    // Initialize AudioEngine.
    hr = this->CreateEngine();

    // verify engine is created.
    assert(hr == S_OK);

    // Create a mastering voice.
    hr = this->CreateMasterVoice();

    // verify mastering voice is created.
    assert(hr == S_OK);
};

// destructor.
AudioEngine::~AudioEngine()
{
	// destroy master voice.
	this->pMasterVoice->DestroyVoice();

	// destroy audio engine.
	this->pXAudio2->Release();

    // Uninitialize COMThread.
    this->EndCOMThread();
};


//--------------------------------------------------------------
// INITIALIZATION FUNCTIONS.
//--------------------------------------------------------------

// initialize COM Thread.
const HRESULT AudioEngine::StartCOMThread()
{
    return (CoInitializeEx(nullptr, COINIT_MULTITHREADED));
}

// uninitialize COM Thread.
void AudioEngine::EndCOMThread()
{
    CoUninitialize();
}

// create an audio engine instance.
const HRESULT AudioEngine::CreateEngine()
{
	return(XAudio2Create(&this->pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR));
}

// create a mastering voice.
const HRESULT AudioEngine::CreateMasterVoice()
{
	return(this->pXAudio2->CreateMasteringVoice(&this->pMasterVoice, 2, 48000));
}

//--------------------------------------------------------------
// PUBLIC FUNCTIONS.
//--------------------------------------------------------------

IXAudio2MasteringVoice* AudioEngine::GetMasterVoice()
{
    AudioEngine* pAudio = AudioEngine::GetPrivateInstance();
    assert(pAudio);

    return pAudio->pMasterVoice;
}

IXAudio2* AudioEngine::GetXAudio2()
{
    AudioEngine* pAudio = AudioEngine::GetPrivateInstance();
    assert(pAudio);

    return pAudio->pXAudio2;
}

//--------------------------------------------------------------
// PRIVATE FUNCTIONS.
//--------------------------------------------------------------

// get private instance.
AudioEngine* AudioEngine::GetPrivateInstance()
{
    static AudioEngine audio;
    return &audio;
}
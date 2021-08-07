#include "SourceCallback.h"
#include "ACommandQueue.h"
#include "WaveManager.h"
// specialized constructor.
SourceCallback::SourceCallback() noexcept
    : 
    pASnd(nullptr),
    pVoice(nullptr),
    counter(1)
{
}

// destructor.
SourceCallback::~SourceCallback()
{
}


void SourceCallback::SetASound(ASounds* _pASnd)
{
	assert(_pASnd);
	this->pASnd = _pASnd;
    SndID newID;
    this->pASnd->GetId(newID);

    if (newID == SndID::Intro_mono)
    {
        this->pVoice = this->pASnd->pPlaylist->pVoice;
    }   
}

ASounds* SourceCallback::GetASound()
{
	assert(this->pASnd);
	return this->pASnd;
}

void STDMETHODCALLTYPE SourceCallback::OnStreamEnd() noexcept
{
	
	// Send a command and leave
	assert(this->pASnd);
	ACommandQueue::SoundEnd(this->pASnd);
}

void STDMETHODCALLTYPE SourceCallback::OnVoiceProcessingPassEnd() noexcept
{
}

void STDMETHODCALLTYPE SourceCallback::OnVoiceProcessingPassStart(UINT32 v) noexcept
{
    if (this->pVoice != nullptr && v > 0 && this->counter < 8)
    {
        Trace::out("*************** Sound end ***************\n");

        this->counter++;

        switch (this->counter)
        {
        case 1: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::Intro_mono), false);
            break;
        case 2: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::A_mono), false);
            break;
        case 3: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::AtoB_mono), false);
            break;
        case 4: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::B_mono), false);
            break;
        case 5: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::BtoC_mono), false);
            break;
        case 6: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::C_mono), false);
            break;
        case 7: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::CtoA_mono), false);
            break;
        case 8: this->pVoice->SubmitBuffer(WaveManager::Find(Wave::ID::End_mono), true);
            break;
        }

    }
}

void STDMETHODCALLTYPE SourceCallback::OnBufferEnd(void*) noexcept
{
}

void STDMETHODCALLTYPE SourceCallback::OnBufferStart(void*) noexcept
{
    if (this->pVoice != nullptr)
    {
        switch (this->counter)
        {
        case 1: Trace::out("\n********** Sound started Intro_mono **********\n");
            break;
        case 2: Trace::out("\n********** Sound started A_mono **********\n");
            break;
        case 3: Trace::out("\n********** Sound started AtoB_mono **********\n");
            break;
        case 4: Trace::out("\n********** Sound started B_mono **********\n");
            break;
        case 5: Trace::out("\n********** Sound started BtoC_mono **********\n");
            break;
        case 6: Trace::out("\n********** Sound started C_mono **********\n");
            break;
        case 7: Trace::out("\n********** Sound started CtoA_mono **********\n");
            break;
        case 8: Trace::out("\n********** Sound started End_mono **********\n");
            break;
        }
    }
}

void STDMETHODCALLTYPE SourceCallback::OnLoopEnd(void*) noexcept
{
}

void STDMETHODCALLTYPE SourceCallback::OnVoiceError(void*, HRESULT) noexcept
{
}


// --- End of File ---
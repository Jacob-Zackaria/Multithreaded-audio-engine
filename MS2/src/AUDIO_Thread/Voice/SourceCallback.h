#ifndef SOURCE_CALLBACK_H
#define SOURCE_CALLBACK_H

#include "XaudioHeaders.h"
#include "ASounds.h"

class SourceCallback : public IXAudio2VoiceCallback
{

public:
    SourceCallback() noexcept;
    virtual ~SourceCallback();
    SourceCallback(const SourceCallback&) = delete;
    SourceCallback(SourceCallback&&) = delete;
    SourceCallback& operator = (const SourceCallback&) = delete;
    SourceCallback& operator = (SourceCallback&&) = delete;

    // set asound
    void SetASound(ASounds* _pASnd);

    // get asound
    ASounds* GetASound();

    //Called when the voice has just finished playing a contiguous audio stream.
    void STDMETHODCALLTYPE OnStreamEnd() noexcept override;

    void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() noexcept override;

    void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 v) noexcept override;

    void STDMETHODCALLTYPE OnBufferEnd(void*) noexcept override;

    void STDMETHODCALLTYPE OnBufferStart(void*) noexcept override;

    void STDMETHODCALLTYPE OnLoopEnd(void*) noexcept override;

    void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) noexcept override;

private:
    ASounds* pASnd;
    Voice* pVoice;
    unsigned int counter;
};

#endif
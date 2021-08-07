#include "AudioEngine.h"
#include "Voice.h"
#include "SourceCallback.h"

struct VoiceNameTable
{
	Voice::ID id;
	const char* pString;
};

VoiceNameTable table[] =
{
	{ Voice::ID::Fiddle, "Fiddle" },
	{ Voice::ID::Bassoon, "Bassoon" },
	{ Voice::ID::Calliope, "Calliope" },
	{ Voice::ID::Oboe, "Oboe" },
	{ Voice::ID::SongA, "SongA" },
	{ Voice::ID::SongB, "SongB" },
	{ Voice::ID::Intro_mono, "Intro_mono" },
	{ Voice::ID::A_mono, "A_mono" },
	{ Voice::ID::AtoB_mono, "AtoB_mono" },
	{ Voice::ID::B_mono, "B_mono" },
	{ Voice::ID::BtoC_mono, "BtoC_mono" },
	{ Voice::ID::C_mono, "C_mono" },
	{ Voice::ID::CtoA_mono, "CtoA_mono" },
	{ Voice::ID::End_mono, "End_mono" },
	{ Voice::ID::Coma, "Coma" },
	{ Voice::ID::Dial, "Dial" },
	{ Voice::ID::MoonPatrol, "Moon_Patrol" },
	{ Voice::ID::Sequence, "Sequence" },
	{ Voice::ID::Donkey, "Donkey" },
	{ Voice::ID::Electro, "Electro" },
	{ Voice::ID::Alarm, "Alarm" },
	{ Voice::ID::Beethoven, "Beethoven" },
	{ Voice::ID::Uninitialized, "Uninitialized"}
};

#define VoiceTableCount  (sizeof(table) / sizeof(table[0]))

Voice::Voice()
	: poBuff(nullptr),
	poCallback(nullptr),
	poSourceVoice(nullptr),
	pWave(nullptr),
	id(ID::Uninitialized),
	handle()
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Handle::Status Voice::Set(Voice::ID _id, Wave* _pWave)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// set id
		this->id = _id;

		// Set the wave pointer
		assert(_pWave);
		this->pWave = _pWave;

		// Create a voice callback
		this->poCallback = new SourceCallback();
		assert(this->poCallback);

		// create and setup xaudio2 buffer
		this->poBuff = new XAUDIO2_BUFFER_ALIAS();
		assert(this->poBuff);

		// Set the Buffer info...
		*this->poBuff = { 0 };	  // zeros out the complete structure
		this->poBuff->AudioBytes = _pWave->rawBuffSize;  //buffer containing audio data
		this->poBuff->pAudioData = _pWave->poRawBuff;  //size of the audio buffer in bytes
		assert(_pWave->poRawBuff);

		if (this->id == Voice::ID::Intro_mono)
		{
			this->poBuff->Flags = 0;
		}
		else
		{
			this->poBuff->Flags = XAUDIO2_END_OF_STREAM;
		}
		

		this->poBuff->LoopCount = 0;

		// Get XAudio2 from manager
		IXAudio2* pXAudio2 = AudioEngine::GetXAudio2();
		assert(pXAudio2);

		// Create Source Voice
		this->poSourceVoice = nullptr;

		HRESULT hr;
		hr = pXAudio2->CreateSourceVoice(&this->poSourceVoice, (WAVEFORMATEX*)this->pWave->poWfx, 0, XAUDIO2_MAX_FREQ_RATIO, this->poCallback);
		assert(hr == S_OK);
		assert(this->poSourceVoice);

		// submit buffer.
		hr = this->poSourceVoice->SubmitSourceBuffer((XAUDIO2_BUFFER*)this->poBuff);
		assert(hr == S_OK);
		assert(this->poBuff);
	}
	return lock;
}

Handle::Status Voice::SubmitBuffer(Wave* pNewWave, bool end)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Set the Buffer info...
		*this->poBuff = { 0 };	  // zeros out the complete structure
		this->poBuff->AudioBytes = pNewWave->rawBuffSize;  //buffer containing audio data
		this->poBuff->pAudioData = pNewWave->poRawBuff;  //size of the audio buffer in bytes
		assert(pNewWave->poRawBuff);

		if (end == false)
		{
			this->poBuff->Flags = 0;
		}
		else
		{
			this->poBuff->Flags = XAUDIO2_END_OF_STREAM;
		}
		this->poBuff->LoopCount = 0;

		HRESULT hr = this->poSourceVoice->SubmitSourceBuffer((XAUDIO2_BUFFER*)this->poBuff);
		assert(hr == S_OK);
		assert(this->poBuff);
	}
	return lock;
}

Handle::Status Voice::FlushBuffer()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr = this->poSourceVoice->FlushSourceBuffers();
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::ReSubmitBuffer()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr = this->poSourceVoice->SubmitSourceBuffer((XAUDIO2_BUFFER*)this->poBuff);
		assert(hr == S_OK);
	}
	return lock;
}


Voice::~Voice()
{
	// ------------------------------------------------------------------------
	//   Handle is invalidated automatically - through ~handle() destructor
	// ------------------------------------------------------------------------
	this->privClear();
	

	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

Handle::Status Voice::Start()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr;
		hr = poSourceVoice->Start(0);
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::Stop()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr;
		hr = poSourceVoice->Stop(0);
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::SetVolume(const float vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		HRESULT hr;
		hr = poSourceVoice->SetVolume(vol);
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::GetVolume(float& vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		poSourceVoice->GetVolume(&vol);
	}
	return lock;
}

Handle::Status Voice::SetPan(const float pan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		float outputMatrix[4] = { 0 };

		// pan of -1.0 indicates all left speaker, 
		// 1.0 is all right speaker, 0.0 is split between left and right
		float left = 0.5f - pan / 2;
		float right = 0.5f + pan / 2;

		outputMatrix[0] = outputMatrix[3] = left;
		outputMatrix[1] = outputMatrix[2] = right;

		// Get XAudio2 from manager
		IXAudio2MasteringVoice* pMaster = AudioEngine::GetMasterVoice();
		assert(pMaster);

		// get source voice details.
		XAUDIO2_VOICE_DETAILS VoiceDetails;
		this->poSourceVoice->GetVoiceDetails(&VoiceDetails);

		// get master voice details.
		XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
		pMaster->GetVoiceDetails(&MasterVoiceDetails);

		HRESULT hr = this->poSourceVoice->SetOutputMatrix(pMaster, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix);
		assert(hr == S_OK);
	}
	return lock;
}

Handle::Status Voice::GetPan(float& pan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Get XAudio2 from manager
		IXAudio2MasteringVoice* pMaster = AudioEngine::GetMasterVoice();
		assert(pMaster);

		poSourceVoice->GetOutputMatrix(pMaster, 1, 2, &pan);
	}
	return lock;
}

Handle::Status Voice::SetPitch(const float pitch)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		poSourceVoice->SetFrequencyRatio(pitch);
	}
	return lock;
}

Handle::Status Voice::GetPitch(float& pitch)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		poSourceVoice->GetFrequencyRatio(&pitch);
	}
	return lock;
}


Handle::Status Voice::GetId(Voice::ID& _id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

const char* Voice::privGetStringName()
{
	const char* p = "NOT_FOUND";
	const char* pTmp = p;

	for (int i = 0; i < VoiceTableCount; i++)
	{
		if (this->id == table[i].id)
		{
			pTmp = table[i].pString;
			break;
		}
	}

	return pTmp;
}

Handle::Status Voice::SetId(Voice::ID _id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = _id;
	}
	return lock;
}

void Voice::privClear()
{
	this->id = ID::Uninitialized;

	if (this->poSourceVoice)
	{
		// in case it was playing... 
		this->poSourceVoice->Stop();

		// Voice was initialized in XAudio2... so its destroyed there
		this->poSourceVoice->DestroyVoice();
	}
	this->poSourceVoice = nullptr;
	delete this->poBuff;
	this->poBuff = nullptr;

	// New warning C5205 warning... problem its in <xaudio2.h>
	if (this->poCallback)
	{
		delete this->poCallback;
		this->poCallback = nullptr;
	}
}

Handle::Status Voice::Wash()
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

Handle::Status Voice::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %s (%p) \n", this->privGetStringName(), this);
	}
	return lock;
}

// --- End of File ---
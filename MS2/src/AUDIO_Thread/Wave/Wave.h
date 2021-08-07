#ifndef WAVE_H
#define WAVE_H

#include"XAudioHeaders.h"
#include "Handle.h"
#include "DLink.h"
#include "FileUserCallback.h"
typedef unsigned char RawData;

// This class is only there for pretty UML
class Wave_Link : public DLink
{
};
class Wave : public Wave_Link
{
public:

	enum ID
	{
		Fiddle = 0x77770000,
		Bassoon,
		Calliope,
		Oboe,
		SongA,
		SongB,
		Intro_mono,
		A_mono,
		AtoB_mono,
		B_mono,
		BtoC_mono,
		C_mono,
		CtoA_mono,
		End_mono,
		Coma,
		Dial,
		MoonPatrol,
		Sequence,
		Donkey,
		Electro,
		Alarm,
		Beethoven,
		Uninitialized
	};
	enum class Status
	{
		READY,
		ASYNC_LOADING,
		UNINITIALIZED
	};
	static const unsigned int NAME_SIZE = 256;

	// Big Four.
	Wave();
	Wave(const Wave&) = delete;
	const Wave& operator = (Wave&) = delete;
	virtual ~Wave();


	Handle::Status Set(const char* const pWaveName, Wave::ID name, FileUserCallback* pFileUserCB);
	Handle::Status Completed(WAVEFORMATEXTENSIBLE* pWfx, unsigned int rawBuffSize, RawData* pRawBuff);

	Handle::Status SetId(Wave::ID id);
	Handle::Status GetId(Wave::ID&) const;

	Handle::Status Dump();
	Handle::Status Wash();


private:

	void privClear();
	void privSetName(const char* const pWaveName);
	unsigned int  privGetBuffSize(const char* const pWaveName);

public:
	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

	WAVEFORMATEXTENSIBLE* poWfx;
	RawData* poRawBuff;
	unsigned int            rawBuffSize;
	ID                      id;
	Status					WaveStatus;
	FileUserCallback* pFileUserCallback;
	char                    strName[NAME_SIZE];

	Handle handle;
};


#endif
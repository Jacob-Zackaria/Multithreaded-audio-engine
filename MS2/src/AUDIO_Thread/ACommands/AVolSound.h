
//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_VOL_SND_H
#define	A_VOL_SND_H

#include "ACommand.h"
#include "Sounds.h"

class AVolSound : public ACommand
{
public:
	AVolSound() = delete;
	AVolSound(const AVolSound&) = delete;
	AVolSound& operator = (const AVolSound&) = delete;
	~AVolSound() = default;

	AVolSound(SndID id, Sounds* pSnd, float vol);

	virtual void Execute() override;
private:
	float vol;
};

#endif

// --- End of File ---

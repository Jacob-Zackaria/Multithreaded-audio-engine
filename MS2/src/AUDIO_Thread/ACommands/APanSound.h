//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_PAN_SND_H
#define	A_PAN_SND_H

#include "ACommand.h"
#include "Sounds.h"

class APanSound : public ACommand
{
public:
	APanSound() = delete;
	APanSound(const APanSound&) = delete;
	APanSound& operator = (const APanSound&) = delete;
	~APanSound() = default;

	APanSound(SndID id, Sounds* pSnd, float pan);

	virtual void Execute() override;
private:
	float pan;
};

#endif

// --- End of File ---

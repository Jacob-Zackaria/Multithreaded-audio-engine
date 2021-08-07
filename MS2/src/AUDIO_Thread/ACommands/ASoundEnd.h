//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_SOUND_END_H
#define	A_SOUND_END_H

#include "ACommand.h"
#include "Sounds.h"

class ASoundEnd : public ACommand
{
public:
	ASoundEnd() = delete;
	ASoundEnd(const ASoundEnd&) = delete;
	ASoundEnd& operator = (const ASoundEnd&) = delete;
	~ASoundEnd() = default;

	ASoundEnd(SndID id, Sounds* pSnd);

	virtual void Execute() override;
};

#endif

// --- End of File ---

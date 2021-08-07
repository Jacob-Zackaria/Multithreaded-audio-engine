#ifndef A_RESET_SND_H
#define	A_RESET_SND_H

#include "ACommand.h"
#include "Sounds.h"

class AResetSound : public ACommand
{
public:
	AResetSound() = delete;
	AResetSound(const AResetSound&) = delete;
	AResetSound& operator = (const AResetSound&) = delete;
	~AResetSound() = default;

	AResetSound(SndID id, Sounds* pSnd);

	virtual void Execute() override;
};

#endif
#ifndef A_PLAY_SND_H
#define	A_PLAY_SND_H

#include "ACommand.h"
#include "Sounds.h"

class APlaySound : public ACommand
{
public:
	APlaySound() = delete;
	APlaySound(const APlaySound&) = delete;
	APlaySound& operator = (const APlaySound&) = delete;
	~APlaySound() = default;

	APlaySound(SndID id, Sounds* pSnd);

	virtual void Execute() override;
};

#endif

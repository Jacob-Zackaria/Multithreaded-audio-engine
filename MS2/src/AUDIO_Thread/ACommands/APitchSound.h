#ifndef A_PITCH_SND_H
#define	A_PITCH_SND_H

#include "ACommand.h"
#include "Sounds.h"

class APitchSound : public ACommand
{
public:
	APitchSound() = delete;
	APitchSound(const APitchSound&) = delete;
	APitchSound& operator = (const APitchSound&) = delete;
	~APitchSound() = default;

	APitchSound(SndID id, Sounds* pSnd, float pitch);

	virtual void Execute() override;
private:
	float pitch;
};

#endif
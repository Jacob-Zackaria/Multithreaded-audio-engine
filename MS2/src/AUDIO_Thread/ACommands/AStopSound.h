#ifndef A_STOP_SND_H
#define	A_STOP_SND_H

#include "ACommand.h"
#include "Sounds.h"

class AStopSound : public ACommand
{
public:
	AStopSound() = delete;
	AStopSound(const AStopSound&) = delete;
	AStopSound& operator = (const AStopSound&) = delete;
	~AStopSound() = default;

	AStopSound(SndID id, Sounds* pSnd);

	virtual void Execute() override;
};

#endif
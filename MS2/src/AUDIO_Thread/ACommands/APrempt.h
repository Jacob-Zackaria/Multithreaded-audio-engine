#ifndef A_PREMPT_H
#define	A_PREMPT_H

#include "ACommand.h"
#include "Sounds.h"

class APrempt : public ACommand
{
public:
	APrempt() = delete;
	APrempt(const APrempt&) = delete;
	APrempt& operator = (const APrempt&) = delete;
	~APrempt() = default;

	APrempt(SndID id, Sounds* pSnd, Sounds* pOld);

	virtual void Execute() override;
private:
	Sounds* oldSound;
};

#endif

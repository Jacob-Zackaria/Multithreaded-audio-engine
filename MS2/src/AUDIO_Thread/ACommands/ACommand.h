#ifndef A_COMMAND_H
#define	A_COMMAND_H

#include "Command.h"
#include "Sounds.h"

class ACommand : public Command
{
public:
	ACommand(SndID id, Sounds* pSnd);
	virtual ~ACommand() = default;
protected:
	// Data: ------------------
	SndID id;
	Sounds* pSnd;
};

#endif
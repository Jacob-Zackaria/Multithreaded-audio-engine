#include "ACommand.h"

ACommand::ACommand(SndID snd_id, Sounds* p)
{
	this->id = snd_id;

	assert(p);
	this->pSnd = p;
};
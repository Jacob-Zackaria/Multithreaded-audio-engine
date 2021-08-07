#ifndef A_CREATE_SND_H
#define	A_CREATE_SND_H

#include "ACommand.h"
#include "Sounds.h"

class ACreateSounds : public ACommand
{
public:
	ACreateSounds() = delete;
	ACreateSounds(const ACreateSounds&) = delete;
	ACreateSounds& operator = (const ACreateSounds&) = delete;
	~ACreateSounds() = default;

	ACreateSounds(SndID id, Sounds* pSnd, UserCallback* pUserCallback = nullptr);

	virtual void Execute() override;
private:
	// data
	UserCallback* pUserCallback;
};

#endif

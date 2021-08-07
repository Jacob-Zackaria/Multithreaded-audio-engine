#ifndef A_PRINT_TABLE_H
#define	A_PRINT_TABLE_H

#include "ACommand.h"
#include "Sounds.h"

class APrintTable : public ACommand
{
public:
	APrintTable() = delete;
	APrintTable(const APrintTable&) = delete;
	APrintTable& operator = (const APrintTable&) = delete;
	~APrintTable() = default;

	APrintTable(SndID id, Sounds* pSnd);

	virtual void Execute() override;
};

#endif
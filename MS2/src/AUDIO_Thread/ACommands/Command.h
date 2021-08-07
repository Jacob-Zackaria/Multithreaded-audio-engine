#ifndef COMMAND_H
#define	COMMAND_H

// Commands 
class Command
{
public:
	// Contract for the command
	virtual void Execute() = 0;

	virtual ~Command() = default;
};


#endif

#pragma once
#include"Action.h"

class AddEnd : public Action
{
private:
	Point Position1;	//Position where the user clicks to add the stat.
	Point Position2;
public:
	AddEnd(ApplicationManager* pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};

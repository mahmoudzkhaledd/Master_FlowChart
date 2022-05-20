#pragma once
#include"Action.h"
class CutStat : public Action
{
	Point NewPoint;

public:
	CutStat(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


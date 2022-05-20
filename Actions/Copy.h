#pragma once
#include"Action.h"
class CopyStatement : public Action
{
	Point NewPoint;


public:
	CopyStatement(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


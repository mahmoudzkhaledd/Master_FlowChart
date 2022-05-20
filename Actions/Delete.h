#pragma once
#include"Action.h"
class DeleteStat : public Action
{
	Statement* DelStatement;
public:
	DeleteStat(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};


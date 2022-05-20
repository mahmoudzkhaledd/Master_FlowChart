#pragma once
#include"Action.h"
class Comment : public Action
{
	Statement* CommSt;
	string com;
public:
	Comment(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


#pragma once
#include"Action.h"

class ClearDA : public Action
{
private:
	bool deleteStatements;
public:

	ClearDA(ApplicationManager* pAppManager, bool del = 1);
	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


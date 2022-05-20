#pragma once
#include"Action.h"
class GenerateCode : public Action
{
private:
	string nfile;
public:
	GenerateCode(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


#pragma once
#include"Action.h"
class AddWrite : public Action
{
private:
	Point Position1;	//Position where the user clicks to add the stat.
	Point Position2;
	Statement* LHSST;
	string RHS;
public:
	AddWrite(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};


#pragma once
#include"Action.h"
#include "../Statements/Condition.h"
class AddCondition : public Action
{
private:
	Point Position1;
	Point Position2;
	Statement* RHSST;
	Statement* LHSST;
	string txt;
	string LHS;
	string op;
	string S_RHS;
	double RHS = 0.0;
public:
	AddCondition(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


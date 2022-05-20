#pragma once
#include"Action.h"
class RunFlowChart : public Action
{
private:
	vector<Statement*>* st;
public:
	RunFlowChart(ApplicationManager* pAppManager);
	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


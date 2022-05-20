#pragma once
#include"Action.h"
class ValidateFlowChart : public Action
{
private:
	vector<string> LHSArr;
public:
	ValidateFlowChart(ApplicationManager* pAppManager);
	bool NameIsFound(string N);
	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};


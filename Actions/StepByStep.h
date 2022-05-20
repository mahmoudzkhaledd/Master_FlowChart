#pragma once
#include"Action.h"
class StepByStep : public Action
{
private:
	
public:
	StepByStep(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();  //Read Assignemt statements position

	virtual void Execute();
};


#pragma once
#include"Action.h"
class Select : public Action
{
	Statement* SelectedState; // pointer to the selected statement
	Point Pos;
public:
	Select(ApplicationManager* pAppManager, Point p);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};


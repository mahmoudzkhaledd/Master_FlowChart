#pragma once
#include"Action.h"

//Add Simple Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user
// 2 - Creating an object of Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddRead : public Action
{
private:
	Point Position1;	//Position where the user clicks to add the stat.
	Point Position2;
	string LHS;
	double RHS;
public:
	AddRead(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

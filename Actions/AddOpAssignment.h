#ifndef ADD_OP_ASSIGNMENT_H
#define ADD_OP_ASSIGNMENT_H

#include "Action.h"
#include "..\Statements\OpAssignment.h"
//Add SO Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user
// 2 - Creating an object of Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddOPAssignment : public Action
{
private:
	Point Position1;	//Position where the user clicks to add the stat.
	Point Position2;
	string txt; // txt -> "LHS = RHS1 Operator RHS2"
	string LHS;
	Statement* LHSST;
	Statement* RHSST1;
	Statement* RHSST2;
	string S_RHS1;
	char Operator;
	string S_RHS2;
	double RHS1;
	double RHS2;
public:
	AddOPAssignment(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
	
};

#endif
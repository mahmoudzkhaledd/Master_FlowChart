#pragma once
#include"Action.h"


#ifndef ADD_VAR_ASSIGN_H
#define ADD_VAR_ASSIGN_H

#include "Action.h"
#include "..\Statements\VarAssignment.h"

//Add Simple Assignment Statement Action
//This class is responsible for 
// 1 - Getting Assignment stat. coordinates from the user
// 2 - Creating an object of Assignment class and fill it parameters
// 3 - Adding the created object to the list of statements
class AddVarAssignment : public Action
{
private:
	Point Position1;	//Position where the user clicks to add the stat.
	Point Position2;
	string txt;
	string LHS;
	string S_RHS;
	Statement* LHSST;
	Statement* RHSST;
	double RHS = 0.0;
public:
	AddVarAssignment(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif
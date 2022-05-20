#pragma once
#include "Action.h"
#include "../ApplicationManager.h"
#include "../Statements/Statement.h"

class Move : public Action
{
	Point NewPoint;
	Statement* st;
public:
	Move(ApplicationManager* pAppManager);

	virtual void ReadActionParameters() ;

	virtual void Execute() ;
	
};


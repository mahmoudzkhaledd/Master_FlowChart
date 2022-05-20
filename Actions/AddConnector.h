#pragma once
#include"Action.h"
#include"../ApplicationManager.h"
class AddConnector : public Action
{
	Statement* SrcStat;
	Statement* DstStat;	
	Point Position1;	
	Point Position2;		
public:
	AddConnector(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();

	virtual void Execute();
};


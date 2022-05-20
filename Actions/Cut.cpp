#include "Cut.h"

CutStat::CutStat(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void CutStat::ReadActionParameters()
{
	vector<Statement*> *v = pManager->GetSelectedStatement();
	 pIn = pManager->GetInput();
	 pOut = pManager->GetOutput();
	v = pManager->GetSelectedStatement();
	if (v == NULL)
	{
		pOut->PrintMessage("no selected Statement");
		return;
	}


}

void CutStat::Execute()
{ /*
	ReadActionParameters();
	vector<Statement*>* v = pManager->GetSelectedStatement();
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	if (v == NULL)
	{
		return;
	}

	pManager->setcpytype(2);

	pManager->setcpy(v);
	pOut->PrintMessage("Statement is Cut ");


	pManager->deleteStatement(v);*/
}

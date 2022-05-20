#include "Copy.h"
#include"../Statements/Statement.h"
#include "../Statements/Start.h"

CopyStatement::CopyStatement(ApplicationManager* pAppManager):Action(pAppManager){}

void CopyStatement::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	if (pManager->GetSelectedStatement()->size() == 0) {
		pOut->PrintMessage("No Selected Statements !");
		return;
	}
	pOut->PrintMessage("Please Click anywhere. . .");
	if (pIn->GetPointClicked(NewPoint.x, NewPoint.y, 0))
		Execute();
	else pOut->ClearStatusBar();

}

void CopyStatement::Execute()
{
	vector<Statement*>* v = pManager->GetSelectedStatement();

	for (int i = 0; unsigned(i) < v->size(); i++) {
		string x = v->at(i)->GetType();
		if (x == "End") {
			
		}
		if (x == "End") {}
		if (x == "End") {}
		if (x == "End") {}
		if (x == "End") {}
		if (x == "End") {}
		if (x == "End") {}
	}
	pManager->UpdateInterface();
}

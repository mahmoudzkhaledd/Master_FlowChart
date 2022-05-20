#include "Run.h"

RunFlowChart::RunFlowChart(ApplicationManager* pAppManager):Action(pAppManager)
{
	st = pManager->GetVarList();
}

void RunFlowChart::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	
	if (!pManager->getSimulate()) {
		pOut->PrintMessage("Please Check The Validation First.");
		return;
	}
	Execute();
}

void RunFlowChart::Execute()
{
	Statement* Head = pManager->GetHead();
	Head->Simulate();
	
	//while (curr != NULL) {
	//	curr->Simulate();
	//	Statement* Next;
	//	curr->GetNext(Next, Next); // === curr = curr->GetNext();
	//	curr = Next;
	//}
//	int x, y;
	/*for (int i = 0; i < st->size(); i++) {
		pOut->PrintMessage(st->at(i)->GetLHS() + " = " + to_string(st->at(i)->GetRHS()) + " Click anywhere to continue.");
		pOut->pWind->WaitMouseClick(x,y);
		pOut->ClearStatusBar();
	}*/
	pOut->PrintMessage("Simulation Done.");

}

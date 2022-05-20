#include "StepByStep.h"

StepByStep::StepByStep(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void StepByStep::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();


	if (!pManager->getSimulate()) {
		pOut->PrintMessage("Please Check The Validation First.");
		return;
	}
	Execute();
	
}

void StepByStep::Execute()
{
	Statement* curr = pManager->GetHead();
	curr->StepByStep(pOut,pIn);
}

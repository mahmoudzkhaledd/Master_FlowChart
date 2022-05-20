#include "Comment.h"

Comment::Comment(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void Comment::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();

	vector<Statement*>* v = pManager->GetSelectedStatement();
	
	if (v->size() == 0) {
		pOut->PrintMessage("No Chosen Statement.");
		return;
	}
	else if (v->size() > 1) {
		pOut->PrintMessage("Please Select one statement only.");
		return;
	}


	CommSt = v->at(0);

	com = pIn->GetString(pOut, "Please Enter Comment : ");

	pOut->ClearStatusBar();
	Execute();
}

void Comment::Execute()
{
	CommSt->setComment(com);


	pManager->UpdateInterface();

	pOut->PrintMessage(com);

}

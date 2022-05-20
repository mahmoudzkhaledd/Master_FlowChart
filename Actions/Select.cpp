#include "Select.h"

Select::Select(ApplicationManager* pAppManager,Point p):Action(pAppManager)
{
	Pos = p;
}

void Select::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	
	
	SelectedState = pManager->GetStatement(Pos);
	if (SelectedState != NULL) {
		if(UI.AppMode  == DESIGN)
			pOut->ClearStatusBar();
		Execute();
	}
	else {
		pOut->ClearStatusBar();
		pManager->unSelectStatement(NULL, 1); // 0 for single statement , 1 for all statements
		if (UI.AppMode == DESIGN)
			pManager->UpdateInterface(); // redraws all current statements with the new changes
		return;
	}
}

void Select::Execute()
{									
	if (SelectedState->IsSelected()) // if it is selected it becomes unselected and vice versa
									// invert selection
	{
		pManager->unSelectStatement(SelectedState); // remove the statement from the selected array
		SelectedState->SetSelected(0);
		pOut->ClearStatusBar();
	}
	else {
		SelectedState->SetSelected(1);
		pManager->SetSelectedStatement(SelectedState); // add the statement to the selected array
		pOut->PrintMessage(SelectedState->GetComment()); // return comment in the statusbar of the selected statement 
	}
	if(UI.AppMode == DESIGN)
		pManager->UpdateInterface();
}

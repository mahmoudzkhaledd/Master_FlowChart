#include "AddEnd.h"
#include "../Statements/Start.h"
#include "../Statements/End.h"
AddEnd::AddEnd(ApplicationManager* pAppManager) :Action(pAppManager) {

}

void AddEnd::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();

	pOut->PrintMessage("End Statement: Click to add the statement");
	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0);
	pOut->ClearStatusBar();
	Position2.x = Position1.x + UI.Start_Width;
	Position2.y =  Position1.y + UI.Start_Height;
	bool bb = (pManager->GetStatement(Position1, Position2) == NULL);
	if (aa && bb)
	{
		if(pManager->GetTail() == NULL)
			Execute();
		else{
			pOut->PrintMessage("Multiple End Is Not allowed.");
			return;
		}
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement !");
}

void AddEnd::Execute()
{
	EndS* s = new EndS(Position1,Position2);
	pManager->SetTail(s);
	s->Draw(pManager->GetOutput());
	pManager->AddStatement(s);	
}
#include "AddStart.h"
#include "../Statements/Start.h"
#include "../GUI/Output.h"
#include<iostream>
using namespace std;
AddStart::AddStart(ApplicationManager* pAppManager) : Action(pAppManager) { // pAppManager is passed to parent action class

}

void AddStart::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();

	pOut->PrintMessage("Start Statement: Click to add the statement");


	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0); //check whether the click is on the status and tool bar 
																// 0 -> if the click is on the status and tool bar
	pOut->ClearStatusBar();

	Position2.x = Position1.x + UI.Start_Width;
	Position2.y = Position1.y + UI.Start_Height;
	
	bool bb = (pManager->GetStatement(Position1, Position2) == NULL); //checks whether the click is on a old statement 
																	// NULL if there is no old statement 
																// ptr if it is on an old statement
	if (aa && bb) { 
		if(pManager->GetHead() == NULL)
			Execute();
		else {
			pOut->PrintMessage("Multiple Start is Not allowed.");
			return;
		}
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement!");
}

void AddStart::Execute()
{
	Statement* st  = new Start(Position1,Position2);
	pManager->SetHead(st);
	st->Draw(pOut);
	pManager->AddStatement(st);
}

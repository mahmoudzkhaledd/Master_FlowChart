#include "AddRead.h"
#include"../Statements/Read.h"
#include"AddSmplAssign.h"
AddRead::AddRead(ApplicationManager* pAppManager) :Action(pAppManager) { RHS = 0.0; }

void AddRead::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Read Assignment Statement: Click to add the statement");

	Position2.x = Position1.x + UI.read_width;
	Position2.y = Position1.y + UI.read_height;

	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0);
	
	pOut->ClearStatusBar();
	
	bool bb = (pManager->GetStatement(Position1, Position2) == NULL);
	
	string txt = "";
	
	if (aa && bb) {
		txt = pIn->GetString(pOut, "Enter Variable Name : ");
		for (int i = 0; unsigned(i) < txt.length(); i++) {
			if (txt[i] != ' ') 
				LHS += txt[i];
			else {
				pOut->PrintMessage("Space in Names is Not allowed.");
				return;
			}
		}
		
		if (isdigit(LHS[0]) || pIn->CheckValue(pOut , LHS)) {
			pOut->PrintMessage("This name is not allowd.");
			return;
		}
		
		if (pManager->GetStatement(LHS) != NULL) {
			pOut->PrintMessage(LHS + " is taken by another statement.");
			return;
		}

		pOut->ClearStatusBar();
		
		int width = UI.read_width;
		int strw = 0, strh = 0;
		pOut->pWind->GetStringSize(strw, strh, "Read "+txt);
		
		if (strw / 2 + 20 > width / 2) 
			width = strw + 40;
		
		Position2.x = Position1.x + width;
		Position2.y = Position1.y + UI.read_height;
		
		pManager->CheckUnValidList(LHS);
		
		Execute();
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement !");
}

void AddRead::Execute()
{

	//Calculating left corner of assignement statement block
	Read* pRead = new Read(Position1,Position2,pOut,pIn, LHS,RHS);


	pRead->Draw(pManager->GetOutput());
	
	
	pManager->AddStatement(pRead);
}
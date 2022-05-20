#include "AddSmplAssign.h"

#include<iostream>
using namespace std;


#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>


using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddSmplAssign::AddSmplAssign(ApplicationManager* pAppManager, string t) :Action(pAppManager) {
	RHS = 0.0;
	LHS = t;
	LHSST = NULL;
}



void AddSmplAssign::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	pOut->PrintMessage("Simple Value Assignment Statement: Click to add the statement");

	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0);
	pOut->ClearStatusBar();
	
	Position2.x = Position1.x + UI.ASSGN_WDTH;
	Position2.y = Position1.y + UI.ASSGN_HI;
	
	

	bool bb = (pManager->GetStatement(Position1, Position2) == NULL);
	string S_RHS = "";
	if (aa && bb) {
		bool equalSign = 0;
		txt = pIn->GetString(pOut, "Enter Expression : "); // x = 5
		for (int i = 0; unsigned(i) < txt.length(); i++) {
			if (txt[i] == '=') equalSign = 1;
			else if (!equalSign && txt[i] != ' ') LHS += txt[i];
			else if (equalSign && txt[i] != ' '){
				S_RHS += txt[i];
			}
		}
		if (isdigit(LHS[0]) ||LHS[0] == '.') {
			pOut->PrintMessage("This name is not allowd.");
			return;
		}
		if (LHS == "" || S_RHS == "" || equalSign == 0 || S_RHS == ".") {
			pOut->PrintMessage("Please Enter a correct expression.");
			return;
		}
		if(pIn->CheckValue(pOut , S_RHS))
			RHS = stod(S_RHS);
		else {
			pOut->PrintMessage("Incorrect RHS");
			return;
		}
		LHSST = pManager->GetStatement(LHS);
		if (LHSST != NULL) {
			pOut->ClearStatusBar();
			int strw = 0, strh = 0 , width = UI.ASSGN_WDTH;
			pOut->pWind->GetStringSize(strw, strh, txt);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Position2.x = Position1.x + width;
			Position2.y = Position1.y + UI.ASSGN_HI;
			//LHSST->SetRHS(RHS, 0);
			Execute();
		}
		else {
			pOut->PrintMessage(LHS + " is Not Found.");
			return;
		}
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement !");
}

void AddSmplAssign::Execute()
{

	//Calculating left corner of assignement statement block
	
	SmplAssign* pAssign = new SmplAssign(Position1,Position2, LHS, RHS);
	pAssign->SetLHSStatement(LHSST);
	pAssign->Draw(pOut);
	pManager->AddStatement(pAssign);
}
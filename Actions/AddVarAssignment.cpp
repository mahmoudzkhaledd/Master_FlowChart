#include "AddVarAssignment.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>


using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddVarAssignment::AddVarAssignment(ApplicationManager* pAppManager) :Action(pAppManager) { LHSST = NULL; RHSST = NULL; }

void AddVarAssignment::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	pOut->PrintMessage("Variable Value Assignment Statement: Click to add the statement");
	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0);
	pOut->ClearStatusBar();
	Position2.x = Position1.x + UI.ASSGN_WDTH;
	Position2.y = Position1.y + UI.ASSGN_HI;
	bool bb = (pManager->GetStatement(Position1, Position2) == NULL);
	if (aa && bb) {
		bool equalSign = 0;
		txt = pIn->GetString(pOut, "Enter Expression : ");
		for (int i = 0; unsigned(i) < txt.length(); i++) {
			if (txt[i] == '=') equalSign = 1;
			else if (!equalSign && txt[i] != ' ') LHS += txt[i];
			else if (equalSign && txt[i] != ' ') S_RHS += txt[i];
		}
		if ((LHS == "" || S_RHS == "" || equalSign == 0) && LHS != S_RHS) {
			pOut->PrintMessage("Please Enter a correct expression.");
			return;
		}

		if (isdigit(LHS[0])) {
			pOut->PrintMessage("This name is not allowd.");
			return;
		}
		LHSST = pManager->GetStatement(LHS);
		if (LHSST != NULL) {
			RHSST = pManager->GetStatement(S_RHS);
			if (RHSST == nullptr) {
				pOut->PrintMessage("No Variable With Name " + S_RHS);
				return;
			}
			
			//LHSST->SetRHS(St2->GetRHS(), 0.0);
			pOut->ClearStatusBar();
		
			
			int strw = 0, strh = 0, width = UI.ASSGN_WDTH;

			pOut->pWind->GetStringSize(strw, strh, txt);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Position2.x = Position1.x + width;
			Position2.y = Position1.y + UI.ASSGN_HI;
			
			Execute();
		}
		else pOut->PrintMessage(LHS + " is Not Found.");
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement !");
}

void AddVarAssignment::Execute()
{
	VarAssignment* pAssign = new VarAssignment(Position1, Position2, S_RHS, LHS, RHS);
	pAssign->SetLHSStatement(LHSST);
	pAssign->Set_RHS_ST(RHSST);
	pAssign->Draw(pManager->GetOutput());
	pManager->AddStatement(pAssign);
}

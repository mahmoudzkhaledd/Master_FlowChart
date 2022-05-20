#include "AddOpAssignment.h"
#include "..\ApplicationManager.h"
#include"../Statements/OpAssignment.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOPAssignment::AddOPAssignment(ApplicationManager* pAppManager) :Action(pAppManager) {
	txt = "";
	S_RHS1 = "";
	LHSST = NULL;
	RHSST1 = NULL;
	RHSST2 = NULL;
	S_RHS2 = "";
	LHS = "";
}

void AddOPAssignment::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	pOut->PrintMessage("Simple operator Assignment Statement: Click to add the statement");
	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0);

	pOut->ClearStatusBar();
	Position2.x = Position1.x + UI.ASSGN_WDTH;
	Position2.y = Position1.y + UI.ASSGN_HI;

	bool bb = (pManager->GetStatement(Position1, Position2) == NULL);
	if (aa && bb) {
		bool equalSign = 0, Op = 0;
		txt = pIn->GetString(pOut, "Enter Expression : "); // 1x = 5
		for (int i = 0; unsigned(i) < txt.length(); i++) {
			if (txt[i] == '=') equalSign = 1;
			else if (!equalSign && txt[i] != ' ')
				LHS += txt[i];
			else if (equalSign && txt[i] != ' ')
			{
				if (txt[i] == '+' || txt[i] == '-' || txt[i] == '*' || txt[i] == '/') {
					Op = 1;
					Operator = txt[i];
				}
				else if (!Op) {
					S_RHS1 += txt[i];
				}
				else {
					S_RHS2 += txt[i];
				}
			}
		}
		if (isdigit(LHS[0]) || LHS[0] == '.') {
			pOut->PrintMessage("This name is not allowd.");
			return;
		}
		if (LHS == "" || S_RHS1 == "" || S_RHS2 == "" || equalSign == 0 || Op == 0) {
			pOut->PrintMessage("Please Enter a correct expression.");
			return;
		}
		LHSST = pManager->GetStatement(LHS);
		if (LHSST == NULL) {
			pOut->PrintMessage(LHS + " is Not Found.");
			return;
		}

		if (pIn->CheckValue(pOut, S_RHS1)){
			RHS1 = stod(S_RHS1);
			RHSST1 = NULL;
		}
		else {
			RHSST1 = pManager->GetStatement(S_RHS1);
			if (RHSST1 == NULL) {
				pOut->PrintMessage("No Variable With Name " + S_RHS1);
				return;
			}
			RHS1 = RHSST1->GetRHS();
		}
		
		if (RHS2 == 0 && Operator == '/')
		{
			pOut->PrintMessage("Division By Zero Is Not Allowed.");
			return;
		}

		if (pIn->CheckValue(pOut, S_RHS2)) {
			RHS2 = stod(S_RHS2);
			RHSST2 = NULL;
		}
		else{
			RHSST2 = pManager->GetStatement(S_RHS2);
			if (RHSST2 == NULL) {
				pOut->PrintMessage("No Variable With Name " + S_RHS2);
				return;
			}
			RHS2 = RHSST2->GetRHS();
		}
		pOut->ClearStatusBar();
		
		//LHSST->SetRHS(TRHS,0);
		int strw = 0, strh = 0, width = UI.ASSGN_WDTH;
		pOut->pWind->GetStringSize(strw, strh, txt);
		if (strw / 2 + 20 > width / 2)
			width = strw + 40;
		Position2.x = Position1.x + width;
		Position2.y = Position1.y + UI.ASSGN_HI;
		Execute();
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement !");
}
void AddOPAssignment::Execute()
{
	OpAssignment* pAssign = new OpAssignment(Position1,Position2, LHS, S_RHS1, Operator, S_RHS2,RHS1,RHS2);
	pAssign->SetLHSStatement(LHSST);
	pAssign->Set_RHS_ST1(RHSST1);
	pAssign->Set_RHS_ST2(RHSST2);
	pManager->AddStatement(pAssign);
	pAssign->Draw(pManager->GetOutput());
}

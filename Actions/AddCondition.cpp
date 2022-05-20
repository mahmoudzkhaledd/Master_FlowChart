#include "AddCondition.h"
#include<iostream>
using namespace std;
AddCondition::AddCondition(ApplicationManager* pAppManager) :Action(pAppManager) 
{
	op = "";
}

void AddCondition::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	pOut->PrintMessage("Condition Assignment Statement: Click to add the statement");
	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0);
	pOut->ClearStatusBar();
	Position2.x = Position1.x + UI.CondWidth;
	Position2.y = Position1.y + UI.CondHeight;
	bool bb = (pManager->GetStatement(Position1, Position2) == NULL);
	if (aa && bb) {
		bool equalSign = 0;
		txt = pIn->GetString(pOut, "Enter Expression : ");
		for (int i = 0; i < txt.length(); i++) {
			if (txt[i] == '>' || txt[i] == '<' || txt[i] == '='
				|| (txt[i] == '>' && txt[i + 1] == '=') ||
				(txt[i] == '<' && txt[i + 1] == '=') ||
				(txt[i] == '!' && txt[i + 1] == '='))
			{
				equalSign = 1;
				op = txt[i];
				if ((txt[i] == '>' && txt[i + 1] == '=') ||
					(txt[i] == '<' && txt[i + 1] == '=') ||
					(txt[i] == '!' && txt[i + 1] == '=')) {
					op = txt[i];
					op += txt[i + 1];
					i++;
				}
			}
			else if (!equalSign && txt[i] != ' ') LHS += txt[i];
			else if (equalSign && txt[i] != ' ')
				S_RHS += txt[i];
		}
		if (LHS == "" || S_RHS == "" || equalSign == 0 || S_RHS == "." || op == "") {
			pOut->PrintMessage("Please Enter a correct expression.");
			return;
		}
		
		LHSST = pManager->GetStatement(LHS);
		
		if (LHSST != NULL) {
			if (pIn->CheckValue(pOut,S_RHS)) {
				
				RHS = stod(S_RHS);
			
				RHSST = NULL;
			}
			else {
				RHSST = pManager->GetStatement(S_RHS);
				if (RHSST != NULL) {
					RHS = RHSST->GetRHS();
				}
				else {
					pOut->PrintMessage(S_RHS+ " is not found.");
					return;
				}
			}
			
			pOut->ClearStatusBar();
			int strw, strh, width = UI.CondWidth;
			pOut->pWind->GetStringSize(strw, strh, txt);
			if (strw / 2 + 20 > width / 2)
				width = strw + 50;
			Position2.x = Position1.x + width;
			Position2.y = Position1.y + UI.CondHeight;
			
			Execute();
		}
		else {
			pOut->PrintMessage("The Variable name is not found ! ");
			return;
		}
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement !");


}

void AddCondition::Execute()
{
	Condition* con = new Condition(Position1,Position2,LHS,S_RHS,op,RHS);
	con->SetRHSST(RHSST);
	cout << LHSST->GetType() << endl;
	
	con->SetLHSStatement(LHSST);
	con->Draw(pOut);
	pManager->AddStatement(con);
}
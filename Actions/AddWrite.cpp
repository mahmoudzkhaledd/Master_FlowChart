#include "AddWrite.h"
#include"../Statements/Write.h"
AddWrite::AddWrite(ApplicationManager* pAppManager) :Action(pAppManager) { LHSST = NULL; }

void AddWrite::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();

	pOut->PrintMessage("Read Assignment Statement: Click to add the statement");

	bool aa = pIn->GetPointClicked(Position1.x, Position1.y, 0);

	pOut->ClearStatusBar();
	Position2.x = Position1.x + UI.ASSGN_WDTH;
	Position2.y = Position1.y + UI.ASSGN_HI;
	
	bool bb = (pManager->GetStatement(Position1, Position2) == NULL);

	if (aa && bb) {
		RHS = pIn->GetString(pOut, "Enter Variable Name : ");
		
		LHSST = pManager->GetStatement(RHS);

		if (LHSST != NULL) {
			
			int width = UI.ASSGN_WDTH;
			int strw = 0, strh = 0;
			pOut->pWind->GetStringSize(strw, strh, "Write " + RHS);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;


			Execute();
		}
		else pOut->PrintMessage("The Variable name is not found!");
	}
	else if (!aa) pOut->PrintMessage("Don't add statement in the toolbar.");
	else if (!bb) pOut->PrintMessage("This area is taken by another statement !");
}

void AddWrite::Execute()
{

	//Calculating left corner of assignement statement block
	Write* pWrite = new Write(Position1,Position2,pOut, RHS);
	

	pWrite->Draw(pManager->GetOutput());
	
	pWrite->SetLHSStatement(LHSST);

	pManager->AddStatement(pWrite);
}

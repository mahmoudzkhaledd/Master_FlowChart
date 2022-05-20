#include "Move.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include <sstream>

Move::Move(ApplicationManager* pAppManager) :Action(pAppManager){}
void Move::ReadActionParameters() {
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();

	vector<Statement*>* v = pManager->GetSelectedStatement();

	if (v->size() == 0) {
		pOut->PrintMessage("Please Select statements to move.");
		return;
	}

	pOut->PrintMessage("Please Click on the new place.");
	
	bool aa = pIn->GetPointClicked(NewPoint.x, NewPoint.y, 0); // checks whether its on the toolbar
	pOut->ClearStatusBar();
	if (!aa) {
		pOut->PrintMessage("Please Click on the drawing area only.");
		return;
	}

	Execute();
}

void Move::Execute()
{
	vector<Statement*>* v = pManager->GetSelectedStatement();
	Point OldPoint, y; // OldPoint Has Coordinates of heighest selected Statement in Y Dir
	v->at(0)->getCoordinates(OldPoint, y);
	//v->at(0)->getCoordinates(OldPoint, y);
	int Tx = NewPoint.x - OldPoint.x,
		Ty = NewPoint.y - OldPoint.y;
	for (int i = 0; unsigned(i) < v->size(); i++) {
		if (i == 0) {
			v->at(i)->Move(NewPoint);
			v->at(i)->UpdateInletOutlet();
		}
		else {
			Point a, b, PointNew;
			v->at(i)->getCoordinates(a, b);
			
			
			PointNew.x = a.x + Tx;
			PointNew.y = a.y + Ty;
			//if (NewPoint.y < UI.TlBrHeight)
			//	NewPoint.y = UI.TlBrHeight + 1;
			//if (NewPoint.y < UI.TlBrWdth)
			//	NewPoint.y = UI.TlBrWdth + 1;
			
			v->at(i)->Move(PointNew);
			v->at(i)->UpdateInletOutlet();
		}
	}




	pOut->ClearDrawArea();

	pManager->UpdateInterface();
}





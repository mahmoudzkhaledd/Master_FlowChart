#include "AddConnector.h"
#include"../ApplicationManager.h"
#include"../Statements/Connector.h"
AddConnector::AddConnector(ApplicationManager* pAppManager):Action(pAppManager){}

void AddConnector::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	pOut->PrintMessage("Connector: Click to add the first statement.");
	
	bool p1 = pIn->GetPointClicked(Position1.x, Position1.y, 0);
	if (!p1) {
		return;
	}
	Connector* c1 = NULL, *c2 = NULL;
	SrcStat = pManager->GetStatement(Position1);
	if (SrcStat != NULL)
		SrcStat->GetConnector(c1, c2);
	else {
		pOut->PrintMessage("Please Click On any statement.");
		return;
	}
	if (SrcStat->GetType() == "End") {
		pOut->PrintMessage("there is no outlet connector");
		return;
	}
	
	
	
	if (SrcStat->GetType() != "Condition") {
		if (c1 != NULL) {
			pOut->PrintMessage("Each Statement must have one connector");
			return;
		}
	}
	pOut->PrintMessage("Connector: Click to add the second statement.");
	
	bool p2 = pIn->GetPointClicked(Position2.x, Position2.y, 0);
	if (!p2) {
		return;
	}

	DstStat = pManager->GetStatement(Position2);
	
	if (DstStat != NULL)
		DstStat->GetConnector(c1, c2);
	else {
		pOut->PrintMessage("Please Click On any statement.");
		return;
	}
	if (DstStat->GetType() == "Start") {
		pOut->PrintMessage("there is no Inlet connector");
		return;
	}
	
	if (SrcStat == DstStat) {
		pOut->PrintMessage("Can't connect the statement to itself.");
		return;
	}
	if ((p1 && SrcStat != NULL) && (p2 && DstStat != NULL)) { 
		Execute();
	}
	else pOut->PrintMessage("Please Click on any statement on drawing area.");

}

void AddConnector::Execute()
{

	

	if (SrcStat->GetType() == "Condition") {
		string chosen = pIn->GetString(pOut, "This Connector For Yes(Left of the statement) Or No(Rhght Of the statement).");
		pOut->ClearStatusBar();
		Connector* Lc = NULL, *Rc = NULL;
		SrcStat->GetConnector(Lc, Rc);
		if (chosen == "No" && Rc == NULL){
							
			SrcStat->setNext(NULL , DstStat);

			Connector* pCon = new Connector(SrcStat, DstStat, 0);
			SrcStat->SetConnector(NULL, pCon);
			pCon->Draw(pOut);
			pManager->PushConnector(pCon);//add the connector to the connectors array
		}
		else if (chosen == "Yes" && Lc == NULL) {
			SrcStat->setNext(DstStat , NULL);
			
			Connector* pCon = new Connector(SrcStat, DstStat, 1);
			
			
			SrcStat->SetConnector(pCon, NULL);
			pCon->Draw(pOut);
			pManager->PushConnector(pCon);
			
		}
		else {
			if (chosen == "No" && Rc != NULL) {
				pOut->PrintMessage("Right Connector is taken.");
				return;
			}
			if (chosen == "Yes" && Lc != NULL) {
				pOut->PrintMessage("Left Connector is taken.");
				return;
			}
			pOut->PrintMessage("Please Write Yes Or No Only.");
			return;
		}
	}
	else {
		SrcStat->setNext(DstStat);
		Connector* pCon = new Connector(SrcStat, DstStat);
		SrcStat->SetConnector(pCon, NULL);
		pCon->Draw(pOut);
		pManager->PushConnector(pCon);
	}
	
}
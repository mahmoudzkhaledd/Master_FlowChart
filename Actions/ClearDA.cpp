#include "ClearDA.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
ClearDA::ClearDA(ApplicationManager* pAppManager,bool del):Action(pAppManager)
{
	deleteStatements = del;
}

void ClearDA::ReadActionParameters()
{	
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
    
	pOut->PrintMessage("Action: Clear Drawing Area , Click anywhere");
	
	Execute();
}

void ClearDA::Execute()
{
	pOut->ClearDrawArea();
	

	if (deleteStatements) {
		vector<Statement*>* v = pManager->GetStateList();
		vector<Connector*>* v2 = pManager->GetConnectorList();
		vector<Statement*>* v3 = pManager->GetVarList();
		pManager->SetHead(NULL); // for simulation
		pManager->SetTail(NULL);// for simulation
		while (v3->size() != 0) {
			pManager->deleteStatement(v3->back());
		}	
		while (v->size() != 0) {
			Statement* s = v->back();
			pManager->deleteStatement(s);
		}
		
		while (v2->size() != 0) {
			pManager->DeleteConnector(v2->back());
		}
	}
}

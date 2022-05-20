#include "Delete.h"
#include "ClearDA.h"
DeleteStat::DeleteStat(ApplicationManager* pAppManager) :Action(pAppManager)
{
	DelStatement = NULL;
}

void DeleteStat::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	if (pManager->GetSelectedStatement()->size() != 0)
		Execute();
	else pOut->PrintMessage("No Selected Statements.");
}

void DeleteStat::Execute()
{
	pOut->ClearStatusBar();
	vector<Statement*> *v = pManager->GetSelectedStatement();
	vector<Connector*>* c = pManager->GetConnectorList();
	while (v->size() != 0) {
		Statement* st = *pManager->GetSelectedStatement()->begin();
		Connector* Conn = NULL,* AConn = NULL;
		st->GetConnector(Conn, AConn);
		if (st->GetType() != "Condition") {
			if (Conn != NULL) {
				for (int i = 0; unsigned(i) < c->size(); i++) {
					if (c->at(i)->getDstStat() == st) {
						c->at(i)->getSrcStat()->SetConnector(NULL, NULL);
						c->at(i)->getSrcStat()->setNext(NULL);
						pManager->DeleteConnector(c->at(i));
						break;
					}
				}
			pManager->DeleteConnector(Conn);
			}
		}
		else {
			if (Conn != NULL) {
				Conn->getDstStat()->SetConnector(NULL, NULL);
				pManager->DeleteConnector(Conn);
			}
			if (AConn != NULL) {
				AConn->getDstStat()->SetConnector(NULL, NULL);
				pManager->DeleteConnector(AConn);
			}
		}
		for (int i = 0; unsigned(i) < c->size(); i++) {
			if (c->at(i)->getDstStat() == st) {
				c->at(i)->getSrcStat()->SetConnector(NULL, NULL);
				c->at(i)->getSrcStat()->setNext(NULL);
				pManager->DeleteConnector(c->at(i));
				break;
			}
		}
		if(st->GetType() == "Read")	pManager->SetAllUnValid(st);
		if (st->GetType() == "Start") 
			pManager->SetHead(NULL);
		if (st->GetType() == "End")
			pManager->SetTail(NULL);

		vector<Statement*>* vs = pManager->GetUnValidList();
		for (int i = 0; unsigned(i) < vs->size(); i++) {
			if (vs->at(i) == st) {
				vs->erase(vs->begin() + i);
				break;
			}
		}
		vs = pManager->GetVarList();
		for (int i = 0; unsigned(i) < vs->size(); i++) {
			if (vs->at(i) == st) vs->erase(vs->begin() + i);
		}
		pManager->deleteStatement(st);
		
	}
	pOut->ClearDrawArea();
	pManager->UpdateInterface();
	
}

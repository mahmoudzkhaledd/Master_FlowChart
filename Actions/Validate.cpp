#include "Validate.h"

ValidateFlowChart::ValidateFlowChart(ApplicationManager* pAppManager):Action(pAppManager)
{
}

bool ValidateFlowChart::NameIsFound(string N)
{
	for (int i = 0; unsigned(i) < LHSArr.size(); i++){
		if (LHSArr[i] == N) return 1;
	}
	return 0;
}

void ValidateFlowChart::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	vector<Statement*>* v = pManager->GetStateList();
	int StatCount = v->size(), ActualStat = 0;
	if (StatCount == 0) {
		pOut->PrintMessage("There is No Statements in the drawing area.");
		pManager->setSimulate(0);
		return;
	}
	Statement* curr = pManager->GetHead();
	Statement* T = pManager->GetTail();
	if (curr == NULL) {
		pOut->PrintMessage("The FlowChart must have starting point.");
		pManager->setSimulate(0);
		return;
	}
	if (T == NULL) {
		pOut->PrintMessage("The FlowChart must have ending point.");
		pManager->setSimulate(0);
		return;
	}
	if (pManager->GetValidate()) {
		pOut->PrintMessage("Please Check Variable Declaration.");
		pManager->setSimulate(0);
		return;
	}

	for (int i = 0;i < v->size();i++) {
		Statement* s = v->at(i);
		Connector* c1 = NULL, * c2 = NULL;
		s->GetConnector(c1, c2);
		if (s->GetType() != "Condition") {
			if (c1 == NULL && s->GetType() != "End") {
				cout << 1 << " "<< s->GetType() <<endl;
				pOut->PrintMessage("Please Be sure of connecting all statements together.");
				return;
			}
		}
		else {
			if (c1 == NULL || c2 == NULL) {
				cout << 2 << endl;
				pOut->PrintMessage("Please Be sure of connecting all statements together.");
				return;
			}
		}
	}


	//while (curr != NULL) {
	//	ActualStat++;
	//	if (curr->GetType() == "Read") {
	//		LHSArr.push_back(curr->GetLHS());
	//	}
	//	if (curr->GetType() != "Read" && curr->GetType() != "Start" && curr->GetType() != "End") {
	//		if (!NameIsFound(curr->GetLHS())) {
	//			pOut->PrintMessage("Using Variable before declaring it is not allowed.");
	//			pManager->setSimulate(0);
	//			return;
	//		}
	//	}
	//	if (curr->GetType() == "Condition") {
	//		Connector* c1 = NULL, *c2 = NULL;
	//		curr->GetConnector(c1, c2);
	//		if (c1 == NULL || c2 == NULL) {
	//			pOut->PrintMessage("Each Condition Statement Must Have 2 Connectors Out from it.");
	//			return;
	//		}
	//		Statement* currR = NULL, * currL = NULL;
	//		curr->GetNext(currR, currL);
	//	}
	//	Statement* Next;
	//	curr->GetNext(Next, Next); // === curr = curr->GetNext();
	//	curr = Next;
	//}
	/*cout << ActualStat << " " << StatCount << endl;
	if (ActualStat != StatCount) {
		pOut->PrintMessage("Please Don't Let any statment Without Connecting it.");
		pManager->setSimulate(0);
		return;
	}*/
	pManager->setSimulate(1);
	pOut->PrintMessage("The FlowChart Is Correct.");
}

void ValidateFlowChart::Execute()
{

}


#include "EditStatement.h"



#include "..\ApplicationManager.h"
#include "..\Statements\Statement.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Statements\SmplAssign.h"
#include "..\Statements\VarAssignment.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\Condition.h"
#include "..\Statements\OpAssignment.h"
#include "..\Statements\Connector.h"
#include <sstream>
EditStatement::EditStatement(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void EditStatement::ReadActionParameters()
{
	pManager->GetOutput()->ClearStatusBar();
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();

	 v = pManager->GetSelectedStatement();

	if (v == NULL)
	{
		pOut->PrintMessage("no selected Statement");
		return;
	}


}

void EditStatement::Execute()
{
	ReadActionParameters();

	if (v != NULL) {
		/*if (dynamic_cast<Condition*>(ptr)) {
			Condition* pcond = (Condition*)ptr;
			lhs = pcond->GetLHS();
			rhs1 = pcond->GetRHS();
			op = pcond->GetOperator();
		}*/
		if (dynamic_cast<SmplAssign*>(p)) {
			SmplAssign* pcond = (SmplAssign*)p;
			lhs = pcond->GetLHS();
			rhs = pcond->GetRHS();
		}
		else if (dynamic_cast<VarAssignment*>(p)) {
			VarAssignment* pcond = (VarAssignment*)p;
			lhs = pcond->GetLHS();
			rhs1 = pcond->GetRHS();
		}
		else if (dynamic_cast<OpAssignment*>(p)) {
			OpAssignment* pcond = (OpAssignment*)p;
			lhs = pcond->GetLHS();
			op = pcond->Getop();
			rhs1 = pcond->GetRHS();

		}
		else if (dynamic_cast<Read*>(p)) {
			Read* pcond = (Read*)p;
			rhs1 = pcond->GetLHS();
		}
		else if (dynamic_cast<Write*>(p)) {
			Write* pcond = (Write*)p;
			rhs1 = pcond->GetLHS();
		}



	}
}

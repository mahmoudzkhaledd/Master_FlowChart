#include "VarAssignment.h"
#include <sstream>

#include<fstream>
#include<iostream>
using namespace std;
VarAssignment::VarAssignment(Point Lcorner,Point P2,string R, string LeftHS, double RightHS)
{
	Type = "VarAssignment";
	LHSStatement = NULL;
	Next = NULL;
	RHSST = NULL;
	LHS = LeftHS;
	RHS = RightHS;
	S_RHS = R;
	UpdateStatementText();

	X1 = Lcorner.x; 
	Y1 = Lcorner.y;
	X2 = P2.x; 
	Y2 = P2.y;

	pConn = NULL;	//No connectors yet

	width = X2 - X1;
	UpdateInletOutlet();

}

void VarAssignment::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = Next;
}

void VarAssignment::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VarAssignment::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

void VarAssignment::setNext(Statement* NR, Statement* NL)
{
	Next = NR;
}

void VarAssignment::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = Outlet;
}

void VarAssignment::UpdateInletOutlet()
{
	Inlet.x = X1 + width / 2;
	Inlet.y = Y1;

	Outlet.x = Inlet.x;
	Outlet.y = Y1 + UI.ASSGN_HI;
}

void VarAssignment::Simulate()
{
	RHS = RHSST->GetRHS();
	LHSStatement->SetRHS(RHS,0);
	Next->Simulate();
}

void VarAssignment::StepByStep(Output* pOut, Input* pIn)
{
	RHS = RHSST->GetRHS();
	LHSStatement->SetRHS(RHS, 0);
	pOut->PrintMessage(LHSStatement->GetLHS() + " = " + to_string(RHS)+" ,Click anyWhere to continue.");
	int x, y;
	pOut->pWind->WaitMouseClick(x,y);
	Next->StepByStep(pOut, pIn);
}

void VarAssignment::SetConnector(Connector* OutConn1, Connector* OutConn2) 
{
	pConn = OutConn1;
}

void VarAssignment::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = pConn;
}

void VarAssignment::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << S_RHS << ";";
}

void VarAssignment::Move(Point a) 
{
	X1 = a.x;
	Y1 = a.y;
	X2 = a.x + width;
	Y2 = a.y + UI.ASSGN_HI;
}

void VarAssignment::Save(ofstream& OutFile)
{
	Point a, b;
	getCoordinates(a, b);

	OutFile << "VARASSIGN" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t" << LHS << "\t" << S_RHS << "\t“" << comment << "”" << endl;
}

void VarAssignment::Set_RHS_ST(Statement* s)
{
	RHSST = s;
}


void VarAssignment::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	if (!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);

	Point p(X1, Y1);
	pOut->DrawAssign(&p, Text, Selected, width, Y2 - Y1);

}

string VarAssignment::GetLHS() const
{
	return LHS;
}

double VarAssignment::GetRHS() const
{
	return RHS;
}

void VarAssignment::SetLHS(string x)
{
	LHS = x;
}

void VarAssignment::SetS_RHS(string x)
{
	S_RHS = x;
}

void VarAssignment::SetRHS(double x, double y)
{
	RHS = x;
}

void VarAssignment::Edit(Output* pOut, Input* pIn)
{
	string x;

	
	
		pOut->PrintMessage("enter the < LeftHand Side > ");
		x= pIn->GetString(pOut);
		SetLHS(x);
	


	
		pOut->PrintMessage("enter the < rightHand Side > ");
		x = pIn->GetString(pOut);
		SetS_RHS(x);
		UpdateStatementText();
	pOut->ClearStatusBar();
}

void VarAssignment::Load(ifstream& Infile)
{
}




//This function should be called when LHS or RHS changes
void VarAssignment::UpdateStatementText()
{	
	Text = LHS + " = " + S_RHS;
}
# include "OpAssignment.h"
#include "SmplAssign.h"
#include <sstream>
#include<fstream>
#include<iostream>
using namespace std;

OpAssignment::OpAssignment(Point Lcorner, Point P2, string LeftHS , string RightHS1 , char op ,string RightHS2,double R1,double R2)
{	
	LHSStatement = NULL;
	LHS = LeftHS;
	S_RHS1 = RightHS1;
	Operator = op;
	S_RHS2 = RightHS2;
	RHS1 = R1;
	RHS2 = R2;
	UpdateStatementText();
	Next = NULL;
	X1 = Lcorner.x;
	Y1 = Lcorner.y;
	X2 = P2.x; 
	Y2 = P2.y;
	
	pConn = NULL;	//No connectors yet

	width = X2 - X1;
	UpdateInletOutlet();
	
}
void OpAssignment::Set_RHS_ST1(Statement* s)
{
	RHSST1 = s;
}
void OpAssignment::Set_RHS_ST2(Statement* s)
{
	RHSST2 = s;
}
void OpAssignment::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = Outlet;
}
void OpAssignment::UpdateInletOutlet()
{
	Inlet.x = X1 + width / 2;
	Inlet.y = Y1;

	Outlet.x = Inlet.x;
	Outlet.y = Y1 + UI.ASSGN_HI;
}
void OpAssignment::SetConnector(Connector* OutConn1, Connector* OutConn2) 
{
	pConn = OutConn1;
}
void OpAssignment::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = pConn;
}
void OpAssignment::setNext(Statement* NR, Statement* NL)
{
	Next = NR;
}
void OpAssignment::Move(Point a) 
{
	X1 = a.x;
	Y1 = a.y;
	X2 = a.x + width;
	Y2 = a.y + UI.ASSGN_HI;
}
void OpAssignment::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = Next;
}
void OpAssignment::SetLHS(string x)
{
	LHS = x;
}
void OpAssignment::SetRHS(double x, double y)
{
	RHS1 = x;
	RHS2 = y;
}

void OpAssignment::StepByStep(Output* pOut,Input* pIn)
{
	if (RHSST1 != NULL)
		RHS1 = RHSST1->GetRHS();
	if (RHSST2 != NULL)
		RHS2 = RHSST2->GetRHS();
	LHSStatement->SetRHS(GetRHS(), 0);
	
	pOut->PrintMessage("Now, "+LHS+" = "+to_string(GetRHS())+" ,Click anywhere to continue.");
	int x, y;
	pOut->pWind->WaitMouseClick(x, y);
	Next->StepByStep(pOut, pIn);
}

void OpAssignment::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << S_RHS1 << " " << Operator << " " << S_RHS2 << ";";
}

void OpAssignment::Simulate()
{
	if(RHSST1!=NULL)
		RHS1 = RHSST1->GetRHS();
	if (RHSST2 != NULL)
		RHS2 = RHSST2->GetRHS();
	LHSStatement->SetRHS(GetRHS(), 0);
	Next->Simulate();
}

string OpAssignment::GetLHS() const
{
	return LHS;
}
char OpAssignment::Getop() const
{
	return Operator;
}
double OpAssignment::GetRHS() const 
{
	if (Operator == '+')
		return RHS1 + RHS2;
	else if (Operator == '-')
		return RHS1 - RHS2;
	else if (Operator == '*')
		return RHS1 * RHS2;
	else if (Operator == '/')
		return RHS1 / RHS2;
}

void OpAssignment::Edit(Output* pOut, Input* pIn)
{
	string x;

	
		pOut->PrintMessage("enter the < LeftHand Side > ");
		x= pIn->GetString(pOut);
		
		pOut->PrintMessage("enter the < RightHand Side > ");
		x = pIn->GetString(pOut);

		
}

Statement* OpAssignment::Copy(Point P)
{
	/*Point New;
	New.x = P.x - width / 2;
	New.y = P.y;
OpAssignment* pAssign = new OpAssignment(P, New,LHS, RHS);
	return pAssign;*/
	return NULL;
}


void OpAssignment::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	if (!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);

	Point p(X1, Y1);
	pOut->DrawAssign(&p, Text, Selected, width, Y2 - Y1);
}
void OpAssignment::Load(ifstream& Infile)
{
}
void OpAssignment::Save(ofstream& OutFile)
{
	string x;
	Point a, b;
	getCoordinates(a, b);
	if (Operator == '+') {
		x = "PLUS";
	}
	else if (Operator == '-') {
		x = "SBTR";
	}
	else if (Operator == '/') {
		x = "DVID";
	}
	else if (Operator == '*') {
		x = "MULT";
	}
	OutFile << "SNGLOP" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t" << LHS << "\t" << S_RHS1 << "\t" << x << "\t" << S_RHS2 << "\t“" << comment << "”" << endl;
}

//This function should be called when LHS or RHS changes
void OpAssignment::UpdateStatementText()
{

	//	Build the statement text: Left handside then equals then right handside
	Text = LHS + " = " + S_RHS1 + " " + Operator + " " + S_RHS2;
}
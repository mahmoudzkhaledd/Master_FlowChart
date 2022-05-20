#include "SmplAssign.h"
#include <sstream>
#include<fstream>
#include<iostream>
using namespace std;
using namespace std;

SmplAssign::SmplAssign(Point Lcorner, Point Pos2, string LeftHS, double RightHS)
{	
	Type = "SmplAssign";
	Next = NULL;
	LHSStatement = NULL;
	
	LHS = LeftHS;
	RHS = RightHS;
	UpdateStatementText();
	
	X1 = Lcorner.x; 
	Y1 = Lcorner.y;

	X2 = Pos2.x;
	Y2 = Pos2.y;
	pConn = NULL;	//No connectors yet
	width = X2 - X1;
	UpdateInletOutlet();
	
}

void SmplAssign::Move(Point a)
{
	X1 = a.x;
	Y1 = a.y;
	X2 = a.x + width;
	Y2 = a.y + UI.ASSGN_HI;
}
void SmplAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	if (!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);

	if (X1 != -1 && Y1 != -1) {
		Point p(X1, Y1);
		pOut->DrawAssign(&p, Text, Selected,width, Y2-Y1);
	}
}
void SmplAssign::Load(ifstream& Infile)
{
}
void SmplAssign::UpdateStatementText()
{
	//	Build the statement text: Left handside then equals then right handside
	string r = to_string(RHS);
	while (r.back() == '0') r.erase(r.end() - 1);
	Text = LHS + " = " + r + '0';
}







//This function should be called when LHS or RHS changes

void SmplAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void SmplAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

void SmplAssign::setNext(Statement* NR, Statement* NL)
{
	Next = NR;
}

void SmplAssign::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = Outlet;
}

void SmplAssign::UpdateInletOutlet()
{
	Inlet.x = X1  + width / 2;
	Inlet.y = Y1;

	Outlet.x = Inlet.x;
	Outlet.y = Y1 + UI.ASSGN_HI;
}
void SmplAssign::Save(ofstream& OutFile)
{
	Point a, b;
	getCoordinates(a, b);

	OutFile << "SMPASSIGN" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t" << LHS << "\t" << RHS << "\t“" << comment << "”" << endl;
}
void SmplAssign::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << RHS << ";";
}
void SmplAssign::SetConnector(Connector* OutConn1, Connector* OutConn2) 
{
	pConn = OutConn1;
}

void SmplAssign::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = pConn;
}

void SmplAssign::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = Next;
}



string SmplAssign::GetLHS() const
{
	return LHS;
}

double SmplAssign::GetRHS() const
{
	return RHS;
}

void SmplAssign::SetLHS(string x)
{
	LHS = x;
}

void SmplAssign::SetRHS(double x, double y)
{
	RHS = y;
}

void SmplAssign::Simulate()
{

	LHSStatement->SetRHS(RHS, 0);
	Next->Simulate();
}

void SmplAssign::StepByStep(Output* pOut,Input* pIn)
{
	LHSStatement->SetRHS(RHS, 0);
	pOut->PrintMessage("Now, "+LHS+" "+" = "+ to_string(RHS));
	int x, y;
	pOut->pWind->WaitMouseClick(x, y);
	Next->StepByStep(pOut,pIn);
}

void SmplAssign::Edit(Output* pOut, Input* pIn)
{
	string x;

	
	
		pOut->PrintMessage("enter the < LeftHand Side > ");
		x = pIn->GetString(pOut);
		SetLHS(x);

		pOut->PrintMessage("enter the < RightHand Side > ");

		setRHS(pIn->GetValue(pOut));
		UpdateStatementText();
		pOut->ClearStatusBar();

	
}

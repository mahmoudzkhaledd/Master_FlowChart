#include "Read.h"
#include<fstream>
#include<iostream>
using namespace std;
Read::Read(Point Lcorner, Point RCorner, Output* pO,Input* p, string LEFTHS , double R)
{
	Type = "Read";
	LHSStatement = NULL;
	pOut = pO;
	pIn = p;
	LHS = LEFTHS;
	
	RHS = R;
	Next = NULL;
	UpdateStatementText();

	X1 = Lcorner.x; 
	Y1 = Lcorner.y;
	X2 = RCorner.x;
	Y2 = RCorner.y;

	pConn = NULL;	//No connectors yet
	width = X2 - X1;
	UpdateInletOutlet();
}

void Read::SetLHS(string x)
{
	LHS = x;
}

void Read::SetRHS(double x, double y)
{
	RHS = x;
}



void Read::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = Next;
}

void Read::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = Outlet;
}

void Read::UpdateInletOutlet()
{
	Inlet.x = X1 + width / 2;
	Inlet.y = Y1;

	Outlet.x = Inlet.x;
	Outlet.y = Y1 + UI.read_height;
}

void Read::SetConnector(Connector* OutConn1, Connector* OutConn2) 
{
	pConn = OutConn1;
}

void Read::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = pConn;
}

void Read::setNext(Statement* NR, Statement* NL)
{
	Next = NR;
}

void Read::Move(Point a) 
{
	X1 = a.x;
	Y1 = a.y;

	X2 = a.x + width;
	Y2 = a.y + UI.read_height;
}

void Read::GenerateCode(ofstream& OutFile)
{
	OutFile <<"double "<<LHS<<";"<<endl<<"cin >> "<<" " << LHS<<";";
}

void Read::Edit(Output* pOut, Input* pIn)
{
	string x;
	pOut->PrintMessage("Enter the name of variable you want to Read");
	x = pIn->GetString(pOut);
	SetLHS(x);
	UpdateStatementText();
	pOut->ClearStatusBar();
}

string Read::GetLHS() const
{
	return LHS;
}

double Read::GetRHS() const
{
	return RHS;
}

void Read::Save(ofstream& OutFile)
{
	Point a, b;
	getCoordinates(a, b);

	OutFile << "READ" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t" << LHS << "\t“" << comment << "”" << endl;
}
void Read::Simulate()
{
	RHS = pIn->GetValue(pOut, "Enter " + LHS + " : ");
	Next->Simulate();
}
void Read::StepByStep(Output* pOut,Input* pIn)
{
	RHS = pIn->GetValue(pOut, "Enter " + LHS + " : ");
	Next->StepByStep(pOut,pIn);
}

void Read::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	if (!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);
	
	Point p(X1, Y1);
	pOut->DrawReadWrite(&p, Text, Selected, width, UI.read_height);
}

void Read::Load(ifstream& Infile)
{
}




//This function should be called when LHS or RHS changes
void Read::UpdateStatementText()
{
	//	Build the statement text: Left handside then equals then right handside
	string r = LHS;
	Text = "Read " + LHS;
}


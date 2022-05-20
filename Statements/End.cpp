#include "End.h"
#include<fstream>
#include<iostream>
using namespace std;
EndS::EndS(Point c, Point d)
{
	Type = "End";
	
	Next = NULL;
	pConn = NULL;
	
	X1 = c.x;
	Y1 = c.y;
	
	X2 = d.x;
	Y2 = d.y;
	
	UpdateInletOutlet();
}

void EndS::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = Outlet;
}

void EndS::UpdateInletOutlet()
{
	Inlet.x = X1 + UI.Start_Width / 2;
	Inlet.y = Y1;

	Outlet.x = Inlet.x;
	Outlet.y = Y1 + UI.Start_Height;
}

void EndS::SetConnector(Connector* OutConn1, Connector* OutConn2) 
{
	pConn = OutConn1;
}

void EndS::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = pConn;
}

void EndS::setNext(Statement* NR, Statement* NL)
{
	Next = NR;
}

void EndS::Move(Point a) 
{
	X1 = a.x;
	Y1 = a.y;

	X2 = a.x + UI.Start_Width;
	Y2 = a.y + UI.Start_Height;
}

void EndS::StepByStep(Output* pOut,Input* pIn)
{
	pOut->PrintMessage("End of the chart , click anywhere to end.");
	int x, y;
	pOut->pWind->WaitMouseClick(x, y);
	return;
}

void EndS::Draw(Output* pOut) const
{
	
	if (!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);

	Point a(X1, Y1);
	pOut->DrawStart(&a,"End", Selected);
}

void EndS::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = Next;
}

void EndS::SetLHS(string x)
{
}

void EndS::SetRHS(double x, double y)
{
}

void EndS::Save(ofstream& OutFile)
{
	Point a, b;
	getCoordinates(a, b);
	OutFile << "END" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t“" << comment << "”" << endl;
}

void EndS::Simulate()
{
}

void EndS::GenerateCode(ofstream& OutFile)
{
}

double EndS::GetRHS() const
{
	return 0.0;
}

string EndS::GetLHS() const
{
	return "";
}

void EndS::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("This Statement can't be edited");
}

void EndS::Load(ifstream& Infile)
{
}

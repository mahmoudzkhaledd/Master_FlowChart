#include "Start.h"
#include<fstream>
#include<iostream>
using namespace std;

Start::Start(Point c , Point d) // (TopLeft , Bottom Right)
{
	Type = "Start";
	LHSStatement = NULL;
	Next = NULL;
	pConn = NULL;
	
	X1 = c.x;
	Y1 = c.y;
	
	X2 = d.x ;
	Y2 = d.y ;


	UpdateInletOutlet();

}

void Start::StepByStep(Output* pOut,Input* pIn)
{
	pOut->PrintMessage("Starting point of the flowchar ,click anywhere to continue.");
	int x, y;
	pOut->pWind->WaitMouseClick(x, y);
	Next->StepByStep(pOut,pIn);
}

void Start::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = Outlet;
}

void Start::UpdateInletOutlet()
{
	Inlet.x = X1 + UI.Start_Width / 2;
	Inlet.y = Y1;

	Outlet.x = Inlet.x;
	Outlet.y = Y1 + UI.Start_Height;
}

void Start::GenerateCode(ofstream& OutFile)
{
}

void Start::Simulate()
{
	Next->Simulate();
}

void Start::SetConnector(Connector* OutConn1, Connector* OutConn2)
{
	pConn = OutConn1;
}

void Start::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = pConn;
}

void Start::setNext(Statement* NR, Statement* NL)
{
	Next = NR;
}

void Start::Move(Point a) // a = new Point
{
	X1 = a.x;
	Y1 = a.y;

	X2 = a.x + UI.Start_Width;
	Y2 = a.y + UI.Start_Height;
}

void Start::Draw(Output* pOut) const
{
	if(!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);

	Point a(X1, Y1);
	pOut->DrawStart(&a,"Start",Selected);
}

void Start::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = Next;
}

void Start::SetLHS(string x)
{
}

void Start::SetRHS(double x, double y)
{
}
void Start::Save(ofstream& OutFile)
{
	Point a, b;
	getCoordinates(a, b);
	OutFile << "STRT" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t“" << comment << "”" << endl;

}


string Start::GetLHS() const
{
	return "";
}

double Start::GetRHS() const
{
	return 0.0;
}

void Start::Edit(Output* pOut, Input* pIn)
{
	pOut->PrintMessage("This statement can't be edited");

}

void Start::Load(ifstream& Infile)
{
}

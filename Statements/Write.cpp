#include "Write.h"
#include<fstream>
#include <sstream>
#include<iostream>
using namespace std;
Write::Write(Point Lcorner, Point P2, Output* pO, string RightHS)
{
	Type = "Write";
	Next = NULL;
	RHS = RightHS;
	LHSStatement = NULL;
	UpdateStatementText();
	pOut = pO;
	X1 = Lcorner.x;
	Y1 = Lcorner.y;
	X2 = P2.x;
	Y2 = P2.y;

	pConn = NULL;	//No connectors yet
	width = X2 - X1;
	UpdateInletOutlet();
	
}
void Write::Move(Point a) 
{
	X1 = a.x;
	Y1 = a.y;

	X2 = a.x + width;
	Y2 = a.y + UI.read_height;

}
void Write::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 
	if (!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);

	Point p(X1, Y1);
	pOut->DrawReadWrite(&p, Text, Selected, width, UI.read_height);
}

void Write::Edit(Output* pOut, Input* pIn)
{
	string x;

	
	
		pOut->PrintMessage("Enter the name of variable you want to Write");
		x = pIn->GetString(pOut);
		
		setRHS(x);
	pOut->ClearStatusBar();
	
}

void Write::Load(ifstream& Infile)
{
}


//This function should be called when LHS or RHS changes
void Write::UpdateStatementText()
{
	//	Build the statement text: Left handside then equals then right handside
	string r = RHS;

	Text = "Write " + RHS;
}



void Write::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}

void Write::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = Outlet;
}

void Write::UpdateInletOutlet()
{
	Inlet.x = X1 + width / 2;
	Inlet.y = Y1;

	Outlet.x = Inlet.x;
	Outlet.y = Y1 + UI.read_height;
}

void Write::StepByStep(Output* pOut,Input* pIn)
{
	pOut->PrintMessage(RHS + " = " + to_string(LHSStatement->GetRHS()) + " ,Click anywhere to continue.");
	int x, y;
	pOut->pWind->WaitMouseClick(x, y);
	Next->StepByStep(pOut,pIn);
}

void Write::Simulate()
{
	pOut->PrintMessage(RHS + " = " + to_string(LHSStatement->GetRHS()) + " ,Click anywhere to continue.");
	int x, y;
	pOut->pWind->WaitMouseClick(x,y);
	Next->Simulate();
}
void Write::Save(ofstream& OutFile)
{
	Point a, b;
	getCoordinates(a, b);

	OutFile << "WRITE" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t" << RHS << "\t“" << comment << "”" << endl;

}
void Write::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = Next;
}

void Write::SetConnector(Connector* OutConn1, Connector* OutConn2)
{
	pConn = OutConn1;
}

void Write::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = pConn;
}

void Write::setNext(Statement* NR, Statement* NL)
{
	Next = NR;
}

void Write::GenerateCode(ofstream& OutFile)
{
	OutFile << "cout << " << RHS << ";";
}


string Write::GetLHS() const
{
	return RHS;
}

double Write::GetRHS() const
{
	return 0.0;
}

void Write::SetLHS(string x)
{
	
}

void Write::SetRHS(double x, double y)
{
}





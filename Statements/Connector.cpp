#include "Connector.h"
#include<fstream>
#include<iostream>
using namespace std;
#include "..\GUI\UI_Info.h"
#include "..\GUI\output.h"
#include "../Statements/Statement.h"
Connector::Connector(Statement* Src, Statement* Dst, bool LR)
//When a connector is created, it must have a source statement and a destination statement
//There are no free connectors in the folwchart
{
	type = "Connector";
	SrcStat = Src;
	DstStat = Dst;
	selected = 0;
	LorR = LR;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) const
{
	///TODO: Call output to draw a connector from SrcStat to DstStat on the output window
	Point p1, p2,p3;
	if (SrcStat->GetType() == "Condition") {
		if (!LorR) { //Left
			SrcStat->getInletOutlet(p3, p3, p1);
		}
		else { //Right
			SrcStat->getInletOutlet(p3, p1, p3);
		}
	}
	else {
		SrcStat->getInletOutlet(p3, p1, p3);
	}
	DstStat->getInletOutlet(p2, p3, p3);
	
	pOut->DrawConnector(&p1, &p2, selected);
}

void Connector::Save(ofstream& ofile)
{
	string x;
	if (SrcStat->GetType() != "Condition")
	{
		ofile << SrcStat->getID() << "\t" << DstStat->getID() << "\t" << "0" << endl;
	}
	else
	{
		Connector* c1 = NULL, * c2 = NULL;
		SrcStat->GetConnector(c1, c2);
		Statement* RS = c1->getSrcStat();
		Statement* LS = c2->getDstStat();
		ofile << SrcStat->getID() << "\t" << LS->getID() << "\t" << 1 << endl;
		ofile << SrcStat->getID() << "\t" << RS->getID() << "\t" << 2 << endl;
	}

}

#include "Condition.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
#include"../CMUgraphicsLib/CMUgraphics.h"
#include"../CMUgraphicsLib/image.h"
#include<iostream>
#include<fstream>
using namespace std;

Condition::Condition(Point Lcorner, Point Pos, string LeftHS,string rhs, string o , double RightHS)
{
	Type = "Condition";
	NextR = NULL;
	NextL = NULL;
	RConn = NULL;
	LConn = NULL;
	LHSStatement = NULL;
	RHSST = NULL;
	X1 = Lcorner.x;
	Y1 = Lcorner.y;
	X2 = Pos.x;
	Y2 = Pos.y;
	LHS = LeftHS;
	op = o;
	S_RHS = rhs;
	RHS = RightHS;
	UpdateStatementText();
	width = X2 - X1;
	UpdateInletOutlet();
}
void Condition::UpdateStatementText()
{
	string r =S_RHS;

	
	Text = LHS + " " + op + " " + r ;
}



void Condition::getInletOutlet(Point& in, Point& ou1, Point& ou2) const
{
	in = Inlet;
	ou1 = OutletL; 
	ou2 = OutletR;
}

void Condition::UpdateInletOutlet()
{
	
	Inlet.x = X1 + width / 2;
	Inlet.y = Y1;

	OutletR.x = X2;
	OutletR.y = Y1 + UI.CondHeight/2;

	OutletL.x = X1;
	OutletL.y = OutletR.y;
}

void Condition::setNext(Statement* NR, Statement* NL)
{
	if (NR != NULL)
		NextR = NR;
	if (NL != NULL)
		NextL = NL;
}

void Condition::GetNext(Statement*& st1, Statement*& st2) const
{
	st1 = NextL;
	st2 = NextR;
}

bool Condition::IsSaved()
{
	return Saved;
}

void Condition::SetSaved(bool z)
{
	Saved = z;
}

void Condition::SetLHS(string x)
{
	LHS = x;
}

void Condition::SetCOP(string x)
{
	op = x;
}

void Condition::SetRHS(double x, double y)
{
}

void Condition::Load(ifstream& Infile)
{
}


void Condition::Save(ofstream& OutFile)
{
	Point a, b;
	string opr;
	if (op == "=")
		opr = "EQUL";
	else if (op == ">")
		opr = "GTR";
	else if (op == "<")
		opr = "SML";
	else if (op == "<=")
		opr = "SMLOREQUL";
	else if (op == ">=")
		opr = "GTROREQUL";
	else if (op == "!=")
		opr = "NOTEQUL";
	getCoordinates(a, b);
	OutFile << "COND" << "\t" << ID << "\t" << a.x << "\t" << a.y << "\t" << LHS << "\t" << opr << "\t" << RHS << "\t“" << comment << "”" << endl;
}
void Condition::Move(Point a)
{
	X1 = a.x;
	Y1 = a.y;
	X2 = a.x + width;
	Y2 = a.y + UI.CondHeight;
}

void Condition::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void Condition::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

void Condition::setS_RHS(string x)
{
	S_RHS = x;
}

void Condition::SetConnector(Connector* OutConn1, Connector* OutConn2) 
{
		RConn = OutConn1;
	if (OutConn2 != NULL)
		LConn = OutConn2;
}

void Condition::GetConnector(Connector*& OutConn1, Connector*& OutConn2) const
{
	OutConn1 = RConn;
	OutConn2 = LConn;
}

void Condition::GenerateCode(ofstream& OutFile)
{
	OutFile << "if("<<LHS<<" "<<op<<" "<<RHS<<")"<<endl<<"{"<<endl;
	NextR->GenerateCode(OutFile);
	OutFile << "}" << endl << "else" << endl << "{" << endl;
	NextL->GenerateCode(OutFile);
	OutFile << "}";
}

void Condition::StepByStep(Output* pOut,Input* pIn)
{
	

	if (RHSST != NULL) {
		RHS = RHSST->GetRHS();
	}
	DLHS = LHSStatement->GetRHS();
	if (op == "=") {
		if (DLHS == RHS) {
			pOut->PrintMessage("True condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextR->StepByStep(pOut, pIn);

		}
		else {
			pOut->PrintMessage("Flase condition, click anywhere to continue.");


			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextL->StepByStep(pOut, pIn);
		}
	}
	else if (op == ">") {
		if (DLHS > RHS) {
			pOut->PrintMessage("True condition, click anywhere to continue.");


			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextR->StepByStep(pOut, pIn);
		}
		else {
			pOut->PrintMessage("Flase condition, click anywhere to continue.");


			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextL->StepByStep(pOut, pIn);
		}
	}
	else if (op == "<") {
		if (DLHS < RHS) {
			pOut->PrintMessage("True condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextR->StepByStep(pOut, pIn);
		}
		else {
			pOut->PrintMessage("Flase condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextL->StepByStep(pOut, pIn);
		}
	}
	else if (op == "!=") {
		if (DLHS != RHS) {
			pOut->PrintMessage("True condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextR->StepByStep(pOut, pIn);
		}
		else {
			pOut->PrintMessage("Flase condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextL->StepByStep(pOut, pIn);
		}
	}
	else if (op == ">=") {
		if (DLHS >= RHS) {
			pOut->PrintMessage("True condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextR->StepByStep(pOut, pIn);
		}
		else {
			pOut->PrintMessage("Flase condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextL->StepByStep(pOut, pIn);
		}
	}
	else if (op == "<=") {
		if (DLHS == RHS) {
			pOut->PrintMessage("True condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextR->StepByStep(pOut, pIn);
		}
		else {
			pOut->PrintMessage("Flase condition, click anywhere to continue.");
			int x, y;
			pOut->pWind->WaitMouseClick(x, y);
			NextL->StepByStep(pOut, pIn);
		}
	}
}

void Condition::SetLHSST(Statement* s)
{

}

void Condition::SetRHSST(Statement* s)
{
	RHSST = s;
}

void Condition::Simulate()
{
	if (RHSST != NULL) {
		RHS = RHSST->GetRHS();
	}
	DLHS = LHSStatement->GetRHS();
	if (op == "=") {
		if (DLHS == RHS) {
			NextR->Simulate();
		}
		else {
			NextL->Simulate();
		}
	}
	else if (op == ">") {
		if (DLHS > RHS) {
			NextR->Simulate();
		}
		else {
			NextL->Simulate();
		}
	}
	else if (op == "<") {
		if (DLHS < RHS) {
			NextR->Simulate();
		}
		else {
			NextL->Simulate();
		}
	}
	else if (op == "!=") {
		if (DLHS != RHS) {
			NextR->Simulate();
		}
		else {
			NextL->Simulate();
		}
	}
	else if (op == ">=") {
		if (DLHS >= RHS) {
			NextR->Simulate();
		}
		else {
			NextL->Simulate();
		}
	}
	else if (op == "<=") {
		if (DLHS == RHS) {
			NextR->Simulate();
		}
		else {
			NextL->Simulate();
		}
	}
}

string Condition::GetLHS() const
{
	return LHS;
}

void Condition::Edit(Output* pOut, Input* pIn)
{
//	string x;
//	double y;
//
//	// for setting left hand side ;
//		pOut->PrintMessage("enter the < LeftHand Side > ");
//		x = pIn->GetString(pOut, LHS);
//		setLHS(x);	
//		
//	
//		pOut->PrintMessage("enter compartor{ ==, !=, >, <, >= and <= }");
//		x = pIn->GetString(pOut);
//		if (x == "==" || x == "!=" || x == ">" || x == "<" || x == ">=" || x == "<=")
//		{
//			SetCOP(x);
//		}else 
//			pOut->PrintMessage("enter compartor { ==, !=, >, <, >= and <= } only");
//	
//	
//		pOut->PrintMessage("enter the < RightHand Side > ");
//		x = pIn->GetString(pOut);
//		if (x[0]>='a'||x[0]<='z'||x[0]>='A'||x[0]<='Z')
//			setS_RHS(x);
//		if (x[0] >= '0' || x[0] <= '9')
//		{
//			double D;
//			char z;
//
//			do
//			{
//				int n = 0;
//				int dot = 0;
//				bool num = 1;
//				bool digits = 0;
//				for (int i = 0; unsigned(i) < x.length(); i++) {
//					if (x[i] == '.')
//						dot++;
//					else if (x[i] == '-')
//						n++;
//					else if (isdigit(x[i]))
//						digits = 1;
//					else {
//						digits = 0;
//						break;
//					}
//				}
//				if (!digits || n > 1 || dot > 1) {
//
//					pOut->PrintMessage("Invalid value please enter numbers (only with one decimal ) , Press any key to Re-Enter");
//					pIn->WaitKeyPress(z);
//					x = "";
//					pOut->ClearStatusBar();
//				}
//				else
//					break;
//				
//			} while (1);
//
//			y = stod(x);	//convert the string to double 
//
//		}
//		setRHS(y);
//		UpdateStatementText();
//		pOut->ClearStatusBar();
//
}
Statement* Condition::Copy(Point P)
{/*
	Condition* pCondition = new Condition(P, LHS, op, RHS);
	return pCondition;*/
	return NULL;
}

void Condition::Draw(Output* pOut) const
{
	if (!valid)
		pOut->SetBrush(RED);
	else
		pOut->SetBrush(UI.shapesColor);

	Point a(X1, Y1);
	pOut->drawCondition(&a,Text, Selected,width);
}

double Condition::GetRHS() const
{
	return RHS;
}

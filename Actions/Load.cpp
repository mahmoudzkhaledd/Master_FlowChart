#include "Load.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <vector>
#include <sstream>
#include <fstream> // for the file. txt (input and output
//it is used to create files, write information to files, and read information from files.#include "..\Statements\SmplAssign.h"
#include "..\Statements\SmplAssign.h"
#include "..\Statements\VarAssignment.h"
#include "..\Statements\Start.h"
#include "..\Statements\End.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\Condition.h"
#include "..\Statements\OpAssignment.h"
#include "..\Statements\Connector.h"
using namespace std;
loadchart::loadchart(ApplicationManager* pAppManager, string name) :Action(pAppManager)
{
	mfile = name;
}

void loadchart::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	

	mfile = pIn->GetString(pOut, "Enter the name of the input file you want to load :");

	if (mfile == "")
	{
		pOut->PrintMessage("Error! No file name is written  ");
		return;
	}
	Execute();
}


void loadchart::Execute()
{
	
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	
	
	ifile.open(mfile + ".txt", ios::app);

	Load1(ifile);
	ifile.close();
}
void loadchart::Load1(ifstream& file)
{
	Statement* ptr = NULL;
	Connector* ptr2;
	int ID;

	int x, y;
	string name;
	string lhs, rhs1, rhs2, oper;

	string com;
	int statcount;
	int conncount;
	ifile >> statcount;
	
	for (int i = 0; i < statcount; i++)
	{
		ifile >> name;
		if (name == "READ")
		{
			
			ifile >> ID >> x >> y >> lhs >> com;
			int strw, strh,width = UI.read_width;
			pOut->pWind->GetStringSize(strw,strh,lhs+" = "+rhs1);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Point L(x, y), R(x + width, y + UI.read_height);
			ptr = new Read(L, R, pOut, pIn, lhs);
			ptr->SetId(ID);
		}
		else if (name == "WRITE")
		{
			ifile >> ID >> x >> y >> lhs;
			int strw, strh, width = UI.read_width;
			pOut->pWind->GetStringSize(strw, strh, lhs + " = " + rhs1);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Point L(x, y), R(x + width, y + UI.read_height);
			ptr = new Write(L, R, pOut, lhs);
			ptr->SetId(ID);
		}
		else if (name == "COND")
		{
			string a;
			ifile >> ID >> x >> y >> lhs>>oper>>rhs1>>com;
			if (oper == "EQUL")
				a= "=";
			else if (oper == "GTR")
				a = ">";
			else if (oper == "SML")
				a = "<";
			else if (oper == "SMLOREQUL")
				a= "<=";
			else if (oper == "GTROREQUL")
				a= ">=";
			else if (oper == "NOTEQUL")
				a= "!=";
			int strw, strh, width = UI.CondWidth;
			pOut->pWind->GetStringSize(strw, strh, lhs + " " + a + " " + rhs1);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Point L(x, y), R(x + width, y + UI.CondHeight);
			ptr = new Condition(L,R,lhs,rhs1,a);
			ptr->SetId(ID);
		}
		else if (name == "SNGLOP")
		{
			char x;
			ifile >> ID >> x >> y >> lhs >> rhs1 >> oper >> rhs2>>com;
			if (oper == "PLUS") {
				x = '+';
			}
			else if (oper == "SBTR") {
				x = '-';
			}
			else if (oper == "DVID") {
				x = '/';
			}
			else if (oper == "MULT") {
				x = '*';
			}
			int strw, strh, width = UI.ASSGN_WDTH;
			pOut->pWind->GetStringSize(strw, strh, lhs + " = " + rhs1);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Point L(x, y), R(x + width, y + UI.read_height);
			ptr = new OpAssignment(L, R, lhs, rhs1, x, rhs2, 0.0, 0.0);
			ptr->SetId(ID);
		}
		else if (name == "STRT")
		{

			ifile >> ID >> x >> y >> com;
			
			Point L(x, y), R(x+UI.Start_Width,y+UI.Start_Height);
			ptr = new Start(L, R);
			ptr->SetId(ID);
		}
		else if (name == "END")
		{
			ifile >> ID >> x >> y >> com;
			Point L(x, y), R(x + UI.Start_Width, y + UI.Start_Height);
			ptr = new EndS(L, R);
			ptr->SetId(ID);
			cout << ID << x << " " << y << lhs << com << endl;
		}
		else if (name == "SMPASSIGN")
		{
			ifile >> ID >> x >> y >> lhs >> rhs1 >> com;
			int strw, strh, width = UI.ASSGN_WDTH;
			pOut->pWind->GetStringSize(strw, strh, lhs + " = " + rhs1);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Point L(x, y), R(x + width, y + UI.read_height);
			ptr = new SmplAssign(L, R, lhs, stod(rhs1));
			ptr->SetId(ID);
		}
		else if (name == "VARASSIGN")
		{
			ifile >> ID >> x >> y >> lhs >> rhs1 >> com;
			int strw, strh, width = UI.ASSGN_WDTH;
			pOut->pWind->GetStringSize(strw, strh, lhs + " = " + rhs1);
			if (strw / 2 + 20 > width / 2)
				width = strw + 40;
			Point L(x, y), R(x + width, y + UI.read_height);
			ptr = new VarAssignment(L, R, rhs1, lhs, 0.0);
			ptr->SetId(ID);
		}
		pManager->AddStatement(ptr);
	
		ptr->Draw(pOut);
	}
	
	ifile >> conncount;
	cout << conncount << endl;
	int ID1, ID2,cond;
	for (int i = 0;i < conncount;i++)
	{
		ifile >> ID1 >> ID2 >> cond;
		
		Statement* src = pManager->GetIDST(ID1);
		Statement* dst = pManager->GetIDST(ID2);
		ptr2 = new Connector(src, dst, 0);
		pManager->PushConnector(ptr2);
		ptr2->Draw(pOut);
	}
}

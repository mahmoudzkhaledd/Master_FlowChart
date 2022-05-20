#include "Generate.h"
#include<fstream>
#include<iostream>
using namespace std;
GenerateCode::GenerateCode(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void GenerateCode::ReadActionParameters()
{
	pIn = pManager->GetInput();
	pOut = pManager->GetOutput();
	
	if (!pManager->getSimulate()) { // get validate
		pOut->PrintMessage("Please Check The Validation First.");
		return;
	}

	nfile = pIn->GetString(pOut, "Enter the name of the output file :");

	if (nfile == ""){
		pOut->PrintMessage("Error! No file name is written  ");
		return;
	}

	pOut->ClearStatusBar();
	Execute();
}

void GenerateCode::Execute()
{
	Statement* curr = pManager->GetHead(),*Next;
	ofstream os;
	os.open(nfile + ".cpp", ios::app);
	
	os << "#include<iostream>"<< endl
		<< "using namespace std;" << endl 
		<< "int main()" << "{" << endl;
	
	while (curr != NULL) {
		curr->GenerateCode(os);
		os << endl;
		curr->GetNext(Next, Next); // === curr = curr->GetNext();
		curr = Next;
	}

	os << "}";

	os.close();
}

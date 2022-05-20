#include "Save.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <vector>
#include <sstream>
#include <fstream> // for the file. txt (input and output
//it is used to create files, write information to files, and read information from files.
using namespace std;
savechart::savechart(ApplicationManager* pAppManager, string name ) :Action(pAppManager)
{
	nfile = name;
}
void savechart::ReadActionParameters()
{
     pIn = pManager->GetInput();
	 pOut = pManager->GetOutput();
	vector <Statement*>* v = pManager->GetStateList();
	if (v->size() == 0)
	{
		pOut->ClearStatusBar();
		pOut->PrintMessage("No flowcharts to save!");
		return;
	}
	
	nfile = pIn->GetString(pOut, "Enter the name of the output file :");
	
	if (nfile == "")
	{
		pOut->PrintMessage("Error! No file name is written  ");
			return;
	}
	pOut->ClearStatusBar();
	Execute();
}

void savechart::Execute()
{
	vector <Statement*>* v = pManager->GetStateList();
	
	ofile.open(nfile + ".txt",ios::app);
	
	pManager->Save(ofile);
	ofile.close();
}
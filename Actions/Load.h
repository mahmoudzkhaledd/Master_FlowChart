#ifndef LOAD_H
#define LOAD_H
#include <sstream>
#include <fstream>// for the file. txt (input and output
//it is used to create files, write information to files, and read information from files.
#include <string>
#include "Action.h"
#include "../Statements/Statement.h"
class loadchart :public Action
{
private:
	Point Position;
	ifstream ifile;
	string mfile;
public:
	loadchart(ApplicationManager* pAppManager, string mfile = "");
	
	virtual void ReadActionParameters();  //Read Assignemt statements position

	virtual void Execute();
	void Load1(ifstream& file);
};



#endif
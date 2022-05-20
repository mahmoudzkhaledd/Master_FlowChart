#ifndef SAVE_H
#define SAVE_H
#include <sstream>
#include <fstream>// for the file. txt (input and output
//it is used to create files, write information to files, and read information from files.
#include <string>
#include "Action.h"
#include "../Statements/Statement.h"
class savechart :public Action
{
private:
	Point position;
	ofstream ofile;
	string nfile;
public:
	savechart(ApplicationManager* pAppManager , string nfile="");
	virtual void ReadActionParameters();  //Read Assignemt statements position

	virtual void Execute();
};
#endif
#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include"GUI/AnotherWindow.h"
#include<vector>
#include "Statements\Statement.h"
#include"Statements/Connector.h"
class Input;
class Output;

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	buttonstate b;
	Point pointer;
	Statement* HeighesitStat;
	vector<Statement*> StatList;	//List of all statements (Array of pointers)
	vector<Statement*> UnValidList;
	vector<Statement*> VarList;
	vector<Statement*> CutS;
	Statement* Head;
	Statement* Tail;
	Statement* pcpy;
	bool Validate;
	bool simulate;
	image *imHovered = NULL;
	image *lastHovered = NULL;
	vector<Connector*> ConnList;	//List of all connectors (Array of pointers)
	vector<Statement*> SelectedStat; //a pointer to the last selected statement
	//Pointers to Input and Output classes
	Input* pIn;
	Output* pOut;
	window* pWind;
	int lastX;
	int lastY;
	int cpyt;
	image screen;
	image lastscreen;
public:
	ApplicationManager();
	~ApplicationManager();
	string getName(ImageFunction im,bool n = 0);
	
	void SetBuffering(bool x = 0);
	// -- Actions Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction();
	window* getWindow();
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	 
	bool getSimulate();
	void setSimulate(bool x);
	// -- Statements/Connector Management Functions
	void AddStatement(Statement* pStat); //Adds a new Statement to the Flowchart
	
	void SetHead(Statement* pStat);
	Statement* GetHead();
	Statement* GetIDST(int s);
	void SetTail(Statement* T);
	Statement* GetTail();

	Statement *GetStatement(Point p1, Point p2) const;	//search for a statement where point P belongs
	Statement* GetStatement(Point p) const;
	Statement* GetStatement(string L ) const;	//search for a statement by id  
	
	void PushConnector(Connector* pConn); //Adds a new Connector to the Flowchart
	void SetValidate(bool x);
	bool GetValidate();
	
	Statement* GetHeighestState();
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs
	void Save(ofstream& ofile);
	void DeleteConnector(Connector* conn);
	vector<Statement*>* GetVarList();
	vector<Statement*>* GetUnValidList();
	vector<Statement*>* GetStateList();
	vector<Statement*>* GetSelectedStatement() ;	//Returns the selected Statement
	vector<Connector*>* GetConnectorList();
	void SetSelectedStatement(Statement *pStat, int index=0); //Set the Statement selected by the user
	void SetValidStatement(Statement* S,bool v);
	void SetAllUnValid(Statement* S);
	void CheckUnValidList(string L);
	void unSelectStatement(Statement *pStat,bool allststements = 0); // 0 for un select
	void deleteStatement(Statement* pStat);
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	void setcpy(Statement* P); //set statement to copy or cut
	Statement* getcpy();//get copy or cut
	void setcpytype(int c);// to select the type of copy if 1 is copy and 2 is cut
	int getcpytype();
};

#endif
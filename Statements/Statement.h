#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "Connector.h"
#include"../Actions/Action.h"
//class Output;
#include "..\GUI\Output.h"

//Base class for all Statements
class Statement
{
protected:
	int ID;			// Each Statement has an ID
	static int initial_id; 

	string Text;	// Statement text (e.g.  "X = 5" OR "if(salary > 3000)" and so on )
	string Type;
	string comment = "";
	bool Selected;	// true if the statement is selected on the folwchart
	
	bool valid = 1;
	
	Statement* LHSStatement;
	
	int X1, Y1; // Coordinates Of the Statement
	int X2, Y2;


	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	
	


	/// Add more parameters if needed.

public:
	Statement();
	Statement(int a,int b,int c,int d);
	
	string GetType();
	int getID();
	
	void getCoordinates(Point &a,Point &b);

	virtual void getInletOutlet(Point &in,Point &ou1, Point& ou2) const = 0; // out1 = Left , out2 = Right
	virtual void UpdateInletOutlet() = 0;

	void setComment(string c);
	virtual void setNext(Statement* NR, Statement* NL = NULL) = 0;
	void SetLHSStatement(Statement* s);
	void SetSelected(bool s);
	void SetValid(bool v);
	bool IsValid();
	bool IsSelected() const;
	void SetId(int i);
	string GetComment();
	virtual void GenerateCode(ofstream& OutFile) = 0;	// write the statement code to a file
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2) = 0;
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const = 0;
	virtual void StepByStep(Output* pOut,Input* pIn) = 0;
	virtual void GetNext(Statement*& st1, Statement*& st2) const = 0;


	virtual void Move(Point a) = 0;					//Move the Statement on the flowchart a= new point
	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	
	virtual string GetLHS() const = 0; 
	virtual double GetRHS() const = 0;

	virtual void Save(ofstream& OutFile) = 0;    //Save the Statement parameters to a file

	virtual void SetLHS(string x)  = 0;

	virtual void SetRHS(double x , double y)  = 0;

	virtual void Simulate() = 0;

	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type	



	//virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	
	virtual void Edit(Output* pOut, Input* pIn) = 0;// Edit statement by taking pointers from output and input using dynamic casting		//Edit the Statement parameter


	//
	//	// Execute the statement in the simulation mode



	//virtual void PrintInfo(Output* pOut) = 0;	//print all Statement info on the status bar
	
	///TODO: Add more functions if needed
};

#endif
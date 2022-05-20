#ifndef SMPL_ASSIGN_H
#define SMPL_ASSIGN_H

#include "Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class SmplAssign : public Statement{
private:
	int width;
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)
	//ex: x = 15
	Statement* Next;
		
	Connector *pConn;	//Simple Assignment Stat. has one Connector to next statement
	Point Inlet;
	Point Outlet;
	//Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	SmplAssign(Point Lcorner,Point Pos2, string LeftHS = "", double RightHS = 0.0);
	virtual void Simulate();
	void setLHS(const string &L);
	void setRHS(double R);
	virtual void setNext(Statement* NR, Statement* NL = NULL);
	virtual void getInletOutlet(Point& in, Point& ou1, Point& ou2)const;
	virtual void UpdateInletOutlet();
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2);
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const;
	virtual void GetNext(Statement*& st1, Statement*& st2) const;
	virtual void Move(Point a);
	virtual string GetLHS() const;
	virtual double GetRHS() const;
	virtual void Save(ofstream& OutFile);
	virtual void GenerateCode(ofstream& OutFile);
	virtual void SetLHS(string x);
	virtual void SetRHS(double x, double y);
	virtual void StepByStep(Output* pOut,Input* pIn);
	virtual void Edit(Output* pOut, Input* pIn);

	virtual void Draw(Output* pOut) const;
	virtual void Load(ifstream& Infile);
};

#endif
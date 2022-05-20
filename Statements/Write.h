#pragma once
#include"Statement.h"
class Write :public Statement
{
private:
	string RHS;	//Left Handside of the assignment (name of a variable)
	//ex: x = 15

	int width;
	Connector* pConn;	//Simple Assignment Stat. has one Connector to next statement
	Point Inlet;
	Point Outlet;
	Output* pOut;
	Input* pIn;
	Statement* Next;
	
	//Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Write(Point Lcorner,Point P2,Output* pO, string RightHS = "");

	void setRHS(string R);

	virtual void getInletOutlet(Point& in, Point& ou1, Point& ou2)const;
	virtual void UpdateInletOutlet();
	virtual void StepByStep(Output* pOut,Input* pIn);
	virtual void Save(ofstream& OutFile);
	virtual void Simulate();
	virtual void GetNext(Statement*& st1, Statement*& st2) const;
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2);
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const;
	virtual void setNext(Statement* NR, Statement* NL = NULL);
	virtual void GenerateCode(ofstream& OutFile);
	
	virtual void Move(Point a);
	virtual string GetLHS() const;
	virtual double GetRHS() const;
	virtual void SetLHS(string x);
	virtual void SetRHS(double x, double y);
	virtual void Draw(Output* pOut) const;
	virtual void Edit(Output* pOut, Input* pIn);
	virtual void Load(ifstream& Infile);
};


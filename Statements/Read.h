#pragma once
#include"Statement.h"
class Read : public Statement {
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	
	double RHS; // Value

	Statement* Next;

	Connector* pConn;	//Simple Assignment Stat. has one Connector to next statement
	Output* pOut;
	Input* pIn;
	Point Inlet;
	Point Outlet;

	int width;
	//Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Read(Point Lcorner, Point RCorner, Output* pO, Input* p, string LEFTHS = "",double R = 0.0);

	virtual void Save(ofstream& OutFile);
	virtual void StepByStep(Output* pOut,Input* pIn);
	virtual void SetLHS(string x);
	virtual void SetRHS(double x, double y);
	virtual void Simulate();
	virtual void GetNext(Statement*& st1, Statement*& st2) const;
	virtual void getInletOutlet(Point& in, Point& ou1, Point& ou2)const;
	virtual void UpdateInletOutlet();
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2);
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const;
	virtual void setNext(Statement* NR, Statement* NL = NULL);
	virtual void Move(Point a);
	virtual void GenerateCode(ofstream& OutFile);
	virtual void Edit(Output* pOut, Input* pIn);
	virtual string GetLHS() const;
	virtual double GetRHS() const;
	virtual void Draw(Output* pOut) const;
	virtual void Load(ifstream& Infile);
};


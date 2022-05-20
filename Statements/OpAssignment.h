#pragma once
#include"Statement.h"
class OpAssignment :public Statement
{
private:
	string LHS;
	string S_RHS1;
	Statement* RHSST1;
	char Operator;
	string S_RHS2;
	Statement* RHSST2;
	int width;
	double RHS1;
	double RHS2;
	Connector* pConn;	//Simple Assignment Stat. has one Connector to next statement
	Statement* Next;
	Point Inlet;	//A point where connections enters this statement 
	Point Outlet;	//A point a connection leaves this statement

	//Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:

	OpAssignment(Point Lcorner,Point P2, string LeftHS, string RightHS1, char op, string RightHS2, double R1, double R2);
	void Set_RHS_ST1(Statement* s);
	void Set_RHS_ST2(Statement* s);
	virtual void Save(ofstream& OutFile);
	virtual void getInletOutlet(Point& in, Point& ou1, Point& ou2)const;
	virtual void UpdateInletOutlet();
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2);
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const;
	virtual void setNext(Statement* NR, Statement* NL = NULL);
	virtual void Move(Point a);
	virtual void GetNext(Statement*& st1, Statement*& st2) const;
	virtual void SetLHS(string x) ;
	virtual void SetRHS(double x, double y) ;
	virtual void StepByStep(Output* pOut,Input* pIn);
	virtual void GenerateCode(ofstream& OutFile);
	virtual void Simulate();
	virtual string GetLHS() const;
	virtual char Getop() const;
	virtual double GetRHS() const; 
	virtual void Edit(Output* pOut, Input* pIn);
	virtual Statement* Copy(Point P);
	virtual void Draw(Output* pOut) const;
	virtual void Load(ifstream& Infile);

};


#pragma once
#include"Statement.h"
class EndS :public Statement
{
private:
	Connector* pConn;
	Statement* Next;
	Point Inlet;
	Point Outlet;
	virtual void UpdateStatementText() {};
public:
	EndS(Point c,Point d);
	virtual void getInletOutlet(Point& in, Point& ou1, Point& ou2)const;
	virtual void UpdateInletOutlet();
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2);
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const;
	virtual void setNext(Statement* NR, Statement* NL = NULL);
	virtual void Move(Point a);
	virtual void StepByStep(Output* pOut,Input* pIn);
	virtual void Draw(Output* pOut) const;
	virtual void GetNext(Statement*& st1, Statement*& st2) const;
	virtual void SetLHS(string x);
	virtual void SetRHS(double x, double y);
	virtual void Save(ofstream& OutFile);
	virtual void Simulate();
	virtual void GenerateCode(ofstream& OutFile);
	virtual double GetRHS() const;
	virtual string GetLHS() const;
	virtual void Edit(Output* pOut, Input* pIn);
	virtual void Load(ifstream& Infile);
};


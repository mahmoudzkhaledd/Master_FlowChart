#pragma once
#include"Condition.h"
#include "Statement.h"

class Condition :public Statement
{
	string LHS;	//Left Handside of the assignment (name of a variable)
	string S_RHS;
	double RHS;	//Right Handside (Value)
	double DLHS = 0.0;	//Right Handside (Value)

				//ex: x = 15
	Connector* RConn;
	Connector* LConn;
	Statement* RHSST;

	Statement* NextR;
	Statement* NextL;
	bool Saved = 0;
	int width;
	string op;
	Point Inlet;
	Point OutletR, OutletL;
	//Point LeftCorner;	//left corenr of the statement block.
	virtual void UpdateStatementText();
public:
	Condition(Point Lcorner,Point Pos ,string LeftHS,string rhs,string o = "", double RightHS = 0.0);

	virtual void getInletOutlet(Point& in, Point& ou1, Point& ou2)const ;
	virtual void UpdateInletOutlet();
	virtual void setNext(Statement* NR, Statement* NL = NULL);
	virtual void GetNext(Statement*& st1, Statement*& st2) const;
	bool IsSaved();
	void SetSaved(bool z);
	virtual void Save(ofstream& OutFile);
	virtual void Move(Point a);
	void setLHS(const string& L);
	void setRHS(double R);
	void setS_RHS(string x );
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2);
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const;
	virtual void GenerateCode(ofstream& OutFile);

	virtual void StepByStep(Output* pOut,Input* pIn);
	void SetLHSST(Statement* s);
	void SetRHSST(Statement* s);
	virtual void Simulate();
	virtual string GetLHS() const;
	//virtual string GetRHS1() const;
	virtual void Edit(Output* pOut, Input* pIn);
	Statement* Copy(Point P);
	virtual void Draw(Output* pOut) const;
	virtual double GetRHS() const;
	virtual void SetLHS(string x);
	virtual void SetCOP(string x);
	virtual void SetRHS(double x, double y);
	virtual void Load(ifstream& Infile);
};


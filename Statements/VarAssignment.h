#ifndef VAR_ASSIGNMENT_H
#define VAR_ASSIGNMENT_H

#include "Statement.h"

//Simple Assignment statement class
//The simple assignment statement assigns a variable to a value
class VarAssignment : public Statement {
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string S_RHS;
	double RHS;	//Right Handside (variable)
	//ex: x = y
	Statement* Next;
	Statement* RHSST;
	Connector* pConn;	//Simple Assignment Stat. has one Connector to next statement
	Point Inlet;
	Point Outlet;
	int width;
	//Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	VarAssignment(Point Lcorner, Point P2, string R, string LeftHS = "", double RightHS = 0.0);
	virtual void GetNext(Statement*& st1, Statement*& st2) const;
	void setLHS(const string& L);
	void setRHS(double R);
	virtual void setNext(Statement* NR, Statement* NL = NULL);
	virtual void getInletOutlet(Point& in, Point& ou1, Point& ou2)const;
	virtual void UpdateInletOutlet();
	virtual void Simulate();
	virtual void StepByStep(Output* pOut,Input* pIn);
	virtual void Save(ofstream& OutFile);
	void Set_RHS_ST(Statement* s);
	virtual void SetConnector(Connector* OutConn1, Connector* OutConn2);
	virtual void GetConnector(Connector*& OutConn1, Connector*& OutConn2) const;
	virtual void GenerateCode(ofstream& OutFile);
	virtual void Move(Point a);
	virtual void Draw(Output* pOut) const;
	virtual string GetLHS() const;
	virtual double GetRHS() const;
	virtual void SetLHS(string x);
	virtual void SetS_RHS(string x);
	virtual void SetRHS(double x, double y);
	virtual void Edit(Output* pOut, Input* pIn);
	virtual void Load(ifstream& Infile);
};

#endif
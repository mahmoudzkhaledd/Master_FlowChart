#include "Statement.h"

int Statement::initial_id = 1;
Statement::Statement()
{

	Type = "";
	Text = "";
	Selected = false;
	ID = initial_id++;
}
Statement::Statement(int a, int b, int c, int d)
{ 
	
	X1 = a, Y1 = b, X2 = c, Y2 = d;
	Text = "";
	Selected = false;	
	ID = initial_id++;
}

string Statement::GetType()
{
	return Type;
}

int Statement::getID()
{
	return ID;
}

void Statement::getCoordinates(Point& a, Point& b)
{
	a.x = X1;
	a.y = Y1;
	b.x = X2;
	b.y = Y2;
}





void Statement::setComment(string c)
{
	comment = c;
}





void Statement::SetLHSStatement(Statement* s)
{
	LHSStatement = s;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

void Statement::SetValid(bool v)
{
	valid = v;
}

bool Statement::IsValid()
{
	return valid;
}



bool Statement::IsSelected() const
{	return Selected; }

void Statement::SetId(int i)
{
	ID = i;
}





string Statement::GetComment()
{
	return comment;
}



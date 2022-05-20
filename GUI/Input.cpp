/*
	Name : Mahmoud khaled abdelatif el naggar
	ID : 1200263
	Name : Tarek emad eldin kotb
	ID : 1200031
	Name : Michael Boktor Abdullah Youssef
	ID : 1200236
	Name : ALEY ELDIN HISHAM MOHAMED MOSTAFA ABDELAZIM
	ID : 1200475


	**important note: if you want to copy the code don't forget to copy image.h and image .cpp as we have modified it
*/

#include "Input.h"
#include "Output.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include<iostream>
using namespace std;



Input::Input(window* pW, Output* out)
{
	pOut = out;
	pWind = pW; //point to the passed window
	//UI.MainInput = this;
	
}

void Input::WaitKeyPress(char& Key)
{
	pWind->WaitKeyPress(Key);
}



bool Input::GetPointClicked(int& x, int& y , bool tlBr) const
{ 
	int x1, y1;
	pWind->WaitMouseClick(x1, y1);
	if (!tlBr) { // 1 to allow the user to click in tool bar area and 
				//  0 to prevent the user to add statement in tool bar and status bar
		if ((x1 <= UI.TlBrWdth && y1 <= UI.height - UI.StBrWdth) || (y1 < UI.TlBrHeight) || y1 >= UI.height - UI.StBrWdth) {
			pOut->PrintMessage("Please Click on Drawing Area Only ! ");
			return 0;
		}
		 
	}
	x = x1;
	y = y1;
	return 1;
}


string Input::GetString(Output* pO, string T) const
{
	string Str = "";
	pO->PrintMessage(T + Str);
	char Key;
	
	while (1)	//ENTER key is pressed
	{
		pWind->WaitKeyPress(Key);
		if (Key == 13) {
			if (Str == ""){
				pO->PrintMessage("Empty Values are not allowed, Press any Key to Enter again.");
				char m;
				pWind->WaitKeyPress(m);
				Key = '\0';
				pO->PrintMessage(T+Str);
			}
			else break;
		}		
		else if (Key == 8 && Str.length() != 0 && Key != 13) {   //BackSpace is pressed
			Str.resize(Str.size() - 1);
		}
		else if (Key != 8 && Key != 13 && Key != 27 && Key != 1){
			Str += Key;
			pO->PrintMessage(T+Str);
		}
		pO->PrintMessage(T+Str);
		pWind->UpdateBuffer();
	}
	return Str;
}


double Input::GetValue(Output* pO,string a) const    // Reads a double value from the user 
{
	///TODO: add code to read a double value from the user and assign it to D
	double D;
	string s = "";
	char x;
	do
	{
		int n = 0;
		int dot = 0;
		bool num = 1;
		bool digits = 0;
		s = GetString(pO,a);
		for (int i = 0; unsigned(i) < s.length(); i++) {
			if (s[i] == '.')
				dot++;
			else if (s[i] == '-')
				n++;
			else if (isdigit(s[i]))
				digits = 1;
			else { 
				digits = 0; 
				break; 
			}
		}
		if (!digits || n > 1 || dot > 1) {

			pO->PrintMessage("Invalid value please enter numbers (only with one decimal ) , Press any key to Re-Enter");
			pWind->WaitKeyPress(x);
			s = "";
			pO->ClearStatusBar();
		}
		else break;
		pWind->UpdateBuffer();
	} while (1);

	D = stod(s);	//convert the string to double 
	
	return D;
	//Read a double value from the user
}

bool Input::isInRange(pair <pair<int, int>, pair<int, int>>* p, int x, int y) {
	if (x >= p->first.first && x <= p->second.first && y >= p->first.second && y <= p->second.second)
	{
		return 1;
	}
	return 0;
}

bool Input::CheckValue(Output* pO, string a) const
{
	do
	{
		int n = 0;
		int dot = 0;
		bool num = 1;
		bool digits = 0;
		for (int i = 0; unsigned(i) < a.length(); i++) {
			if (a[i] == '.')
				dot++;
			else if (a[i] == '-')
				n++;
			else if (isdigit(a[i]))
				digits = 1;
			else {
				digits = 0;
				return 0;
			}
		}
		if (!digits || n > 1 || dot > 1) {
			pO->PrintMessage("Invalid value please enter numbers (only with one decimal ) , Press any key to Re-Enter");
			return 0;
		}
		else {
			
			return 1;
		}
		pWind->UpdateBuffer();
	} while (1);
}

ActionType Input::GetUserAction(image* &hovered){
	int x, y;
	// GetPointClicked(x, y, 1);
	buttonstate b = pWind->GetButtonState(LEFT_BUTTON, x, y);
	if (b == BUTTON_DOWN) pWind->WaitMouseClick(x,y);
	ActionType action = NOACTION;
	image* hov = NULL;
	if ((x >= 0 && x < UI.TlBrWdth && y >= 0 && y < UI.height - UI.StBrWdth) || (x >= 0 && x < UI.width && y >= 0 && y < UI.TlBrWdth)) {

		if (UI.AppMode == DESIGN) {
			for (int i = 0; unsigned(i) < pOut->im.size(); i++)
			{
				if (isInRange(&pOut->arrowD->p, x, y) && pOut->arrowD->isDrawn && pOut->toolBarScope.second <= pOut->imV) { action = arrowDown; hov = pOut->arrowD; }
				else if (isInRange(&pOut->arrowU->p, x, y) && pOut->arrowU->isDrawn && pOut->toolBarScope.first >= 1) { action = arrowUp; hov = pOut->arrowU; }
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == simpleAssign && pOut->im[i]->isDrawn) action = ADD_SMPL_ASSIGN;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == start && pOut->im[i]->isDrawn) action = ADD_START;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == End && pOut->im[i]->isDrawn) action = ADD_END;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == read && pOut->im[i]->isDrawn) action = ADD_READ;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == write && pOut->im[i]->isDrawn) action = ADD_WRITE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == ConditionStatement && pOut->im[i]->isDrawn) action = ADD_CONDITION;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == ConnectorButton && pOut->im[i]->isDrawn) action = ADD_CONNECTOR;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == Exit && pOut->im[i]->isDrawn) action = EXIT;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == Copy && pOut->im[i]->isDrawn) action = COPY;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == Cut && pOut->im[i]->isDrawn) action = CUT;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == Paste && pOut->im[i]->isDrawn) action = PASTE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == Delete && pOut->im[i]->isDrawn) action = DEL;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == Redo && pOut->im[i]->isDrawn) action = REDO;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == Undo && pOut->im[i]->isDrawn) action = UNDO;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == zoomIn && pOut->im[i]->isDrawn) action = ZOOMIN;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == zoomOut && pOut->im[i]->isDrawn) action = ZOOMOUT;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == clear && pOut->im[i]->isDrawn) action = CLEARDRAWINGAREA;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == simulation && pOut->im[i]->isDrawn && UI.AppMode == DESIGN) action = SIMULATION_MODE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == resize && pOut->im[i]->isDrawn) action = RESIZE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == editStatement && pOut->im[i]->isDrawn) action = EDIT;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == varAssign && pOut->im[i]->isDrawn) action = ADD_VAR_ASSIGN;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == operatorassignment && pOut->im[i]->isDrawn) action = ADD_OP_ASSIGN;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == save && pOut->im[i]->isDrawn) action = SAVE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == load && pOut->im[i]->isDrawn) action = LOAD;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == editConnector && pOut->im[i]->isDrawn) action = EDITCONNECTOR;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == comment && pOut->im[i]->isDrawn) action = COMMENT;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == selection && pOut->im[i]->isDrawn) action = SELECT;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == moveObj && pOut->im[i]->isDrawn) action = MOVE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == multipleSelection && pOut->im[i]->isDrawn) action = MULTI_SELECT;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == complexassign && pOut->im[i]->isDrawn) action = COMPLEX;

				if (action != NOACTION && hov == NULL) hov = pOut->im[i];
			}
		}
		else if (UI.AppMode == SIMULATION) {
			for (int i = pOut->imH + pOut->imV + 2; unsigned(i) < pOut->im.size(); i++) {
				if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == designMode && pOut->im[i]->isDrawn) action = DESIGNMODE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == generateCode && pOut->im[i]->isDrawn) action = GENERATE;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == run && pOut->im[i]->isDrawn) action = RUN;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == step_by_step && pOut->im[i]->isDrawn) action = STEP;
				else if (isInRange(&pOut->im[i]->p, x, y) && pOut->im[i]->type == validate && pOut->im[i]->isDrawn) action = VALIDATE;
				if (action != NOACTION && hov == NULL) hov = pOut->im[i];
			}

		}

	}
	else
	{
		if(b == BUTTON_DOWN)
		return CLICK_ON_DRAWING_AREA;
	}
	if (b == BUTTON_DOWN){
		return action;
	}
		
	else {
		if (action != NOACTION)	hovered = hov;
		else return NOACTION;
		return HOVER; 
	}
}
Input::~Input()
{
}

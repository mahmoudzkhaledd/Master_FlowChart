#include "ApplicationManager.h"
#include "Actions\AddSmplAssign.h"
#include"Actions/AddStart.h"
#include"Actions/AddEnd.h"
#include "Actions/AddCondition.h"
#include "Actions/AddVarAssignment.h"
#include"Actions/AddRead.h"
#include"Actions/AddWrite.h"
#include "Actions/AddConnector.h"
#include "Actions/Select.h"
#include"Actions/Delete.h"
#include"Actions/Copy.h"
#include "Actions/AddOpAssignment.h"
#include "Actions/ClearDA.h"
#include"Actions/Comment.h"
#include"Actions/Move.h"
#include"Actions/Validate.h"
#include "Actions/Run.h"
#include"Actions/save.h"
#include "Actions/Generate.h"
#include"Actions/Load.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include"Actions/StepByStep.h"
#include"Statements/Statement.h"
#include<iostream>
#include<fstream>
using namespace std;
//Constructor
ApplicationManager::ApplicationManager()
{ 
	b = BUTTON_UP;
	//Create Input and output
	Validate = 0;
	simulate = 0;
	pOut = new Output;
	pIn =  new Input(pOut->pWind,pOut);
	pWind = pOut->pWind;
	lastX = lastY = 0;
	pWind->StoreImage(screen, 0, 0, UI.width, UI.height - UI.StBrWdth);
	pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);
	Head = NULL;
	Tail = NULL;
	lastHovered = NULL;
	HeighesitStat = NULL;
	//Create an array of Statement pointers and set them to NULL		
	
	pWind->UpdateBuffer();
}
void ApplicationManager::SetBuffering(bool x) {
	pWind->SetBuffering(x);
}
//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() 
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction(imHovered);
}
window* ApplicationManager::getWindow() {
	return pWind;
}
string ApplicationManager::getName(ImageFunction im,bool n) {
	switch (im)
	{
	case start:
		return (n == 0) ? "Start.JPG" : "Start";
		break;
	case End:
		return (n == 0) ? "Start.JPG" : "End";
		break;
	case read:
		return (n == 0) ? "Read.JPG" : "Read";
		break;
	case write:
		return (n == 0) ? "Read.JPG" : "Write";
		break;
	case simpleAssign:
		return (n == 0) ? "Assign.JPG" : "Simple Assign";
		break;
	case ConditionStatement:
		return (n == 0) ? "Condition.JPG" : "Condition";
		break;
	case ConnectorButton:
		return (n == 0) ? "Connector.JPG" : "Connector";
		break;
	case Exit:
		return (n == 0) ? "exit.JPG" : "Exit";
		break;
	case Copy:
		return"Copy.jpg";
		break;
	case Cut:
		return"Cut.jpg";
		break;
	case Paste:
		return"Paste.jpg";
		break;
	case Delete:
		return"Delete.jpg";
		break;
	case Redo:
		return"Redo.jpg";
		break;
	case Undo:
		return"Undo.jpg";
		break;
	case DownArrow:
		return (n == 0) ? "ArrowDown.JPG" : "Arrow Down";
		break;
	case UpArrow:
		return (n == 0) ? "ArrowUp.JPG" : "Arrow Up";
		break;
	case simulation:
		return (n == 0) ? "Simulation.JPG" : "Simulation Mode";
		break;
	case zoomIn:
		return (n == 0) ? "ZoomIN.jpg" : "Zoom In";
		return"ZoomIN.jpg";
		break;
	case zoomOut:
		return (n == 0) ? "ZoomOut.jpg" : "Zoom Out";
		break;
	case clear:
		return"Clean.jpg";
		break;
	case resize:
		return (n == 0) ? "Resize.jpg" : "Move";
		//return"Resize.jpg";
		break;
	case designMode:
		return (n == 0) ? "Simulation\\Design.jpg" : "Design Mode";
		break;
	case generateCode:
		return (n == 0) ? "Simulation\\Generate.jpg" : "Generate";
		break;
	case step_by_step:
		return (n == 0) ? "Simulation\\Step.jpg" : "Step By Step";
		break;
	case validate:
		return (n == 0) ? "Simulation\\Validate.jpg" : "Validate";
		break;
	case run:
		return (n == 0) ? "Simulation\\play.jpg" : "Run FlowChart";
		break;
	case editStatement:
		return (n == 0) ? "edit.jpg" : "Edit";
		break;
	case varAssign:
		return (n == 0) ? "Assign.jpg" : "Variable Assign";
		break;
	case operatorassignment:
		return (n == 0) ? "Assign.jpg" : "Operator Assign";
		break;
	case editConnector:
		return"";
		break;
	case comment:
		return"Comment.jpg";
		break;
	case selection:
		return"Select.jpg";
		break;
	case moveObj:
		return"";
		break;
	case multipleSelection:
		return"";
		break;
	case save:
		return"Save.jpg";
		break;
	case load:
		return"Load.jpg";
		break;
	case complexassign:
		return"Complex.jpg";
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it

void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	pWind->UpdateBuffer();
	Action* pAct = NULL;
	//According to ActioType, create the corresponding action object
	 b = pWind->GetButtonState(LEFT_BUTTON, pointer.x, pointer.y);
	 
	 Point po;
	 

	if (ActType != NOACTION && ActType != HOVER && ActType != arrowDown && ActType != arrowUp ) {
		pWind->DrawImage(lastscreen, 0, 0);
		if (UI.AppMode == DESIGN)
		{
			pWind->DrawImage(pOut->lastTlBr, 0, 0); 
		
		}
		pWind->UpdateBuffer();
	}
	switch (ActType)
	{
	case NOACTION: // unhover
		if (imHovered != NULL && lastHovered != NULL){
			
			string location ="images\\Icons\\"+ getName(imHovered->type);
			pWind->DrawImage(location, imHovered->p.first.first, imHovered->p.first.second);
			lastHovered = NULL;      //  drawing area
			if (b != BUTTON_DOWN && !(pointer.x > UI.TlBrWdth && pointer.x < UI.width && pointer.y > UI.TlBrHeight && pointer.y < UI.height - UI.StBrWdth)) {
				pWind->DrawImage(lastscreen, 0, 0); 
			}
		}
		break;
	case HOVER:
		if (lastHovered != imHovered) {
			
			pWind->DrawImage(lastscreen, 0, 0); 
			
			if (lastHovered != NULL){
				string location = "images\\Icons\\" + getName(lastHovered->type);
				pWind->DrawImage(location, lastHovered->p.first.first, lastHovered->p.first.second);
			}
			lastHovered = imHovered;
			string loc = "images\\hovered\\" + getName(imHovered->type);
			pWind->DrawImage(loc,imHovered->p.first.first, imHovered->p.first.second);
			
			pWind->StoreImage(screen, 0, 0, UI.width, UI.height - UI.StBrWdth); //screen after hover.
		}
		pWind->DrawImage(screen, 0, 0);
		
		pOut->drawName(&pointer, getName(imHovered->type,1));
		lastX = pointer.x; lastY = pointer.y;
		pWind->UpdateBuffer();
		break;

	case ADD_SMPL_ASSIGN:
		pAct = new AddSmplAssign(this);
		break;
	case arrowDown:
		pWind->DrawImage(lastscreen, 0, 0);
		pOut->ArrowDown();
		pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);		
		break;
	case arrowUp:
		pWind->DrawImage(lastscreen, 0, 0);
		
		pOut->ArrowUp();
		pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);		
		break;
	

	case ADD_CONDITION:
		pAct = new AddCondition(this);
		break;

	case ADD_CONNECTOR:
		
		pAct = new AddConnector(this);
		break;
	case ADD_VAR_ASSIGN:
		pAct = new AddVarAssignment(this);
		break;
	case ADD_OP_ASSIGN:
		pAct = new AddOPAssignment(this);
		break;
	case ADD_READ:
		pAct = new AddRead(this);
		break;
	case ADD_WRITE:
		pAct = new AddWrite(this);
		pOut->PrintMessage("Action: add a write , Click anywhere");
		break;
	case ADD_START:
		pAct = new AddStart(this);
		break;
	case ADD_END:
		pAct = new AddEnd(this);
		break;
	case EDIT:
		pOut->PrintMessage("Action: click on the object , Click anywhere");
		break;
	case RESIZE:
		pAct = new Move(this);
		break;
	case NEW:
		pOut->PrintMessage("Action:clearing the drawing area and creating new flowchart , Click anywhere");
		break;
	case CLEARDRAWINGAREA:
		pAct = new ClearDA(this);
		break;
	case DEL:
		pAct = new DeleteStat(this);
		break;
	case CUT:
		cout << StatList.size()<<" "<<SelectedStat.size()<<endl;
		cout << ConnList.size() << endl;
		cout << UnValidList.size() << endl;
		cout << VarList.size() << endl;
		pOut->PrintMessage("Action: click on the object to cut , Click anywhere");
		break;
	case COPY:
		pAct = new CopyStatement(this);
		break;
	case PASTE:
		pOut->PrintMessage("Action: click on the object to paste , Click anywhere");
		break;

	case COMMENT:
		pAct = new Comment(this);
		break;
	case MOVE:
		
		break;
	case ZOOMIN:
		
		break;
	case ZOOMOUT:
		pOut->PrintMessage("Action: click on the object to zoom out  , Click anywhere");
		break;
	case SAVE:
		pAct = new savechart(this);
		break;
	case LOAD:
		pAct = new loadchart(this);
		break;
	case MULTI_SELECT:
		pOut->PrintMessage("Action: click on the objects to select , Click anywhere");
		break;
	case SELECT:
		pOut->PrintMessage("Action: a click on the Drawing area, Click anywhere");
		break;
	case UNDO:
		pOut->PrintMessage("Action: undoing, Click anywhere");
	break;	

	case REDO:
		pOut->PrintMessage("Action: redoing , Click anywhere");
	break;	

	case  VALIDATE:
		cout << "Validate\n";
		pAct = new ValidateFlowChart(this);
	break;
	case GENERATE:
		pAct = new GenerateCode(this);
	break;

	case RUN:
		pAct = new RunFlowChart(this);
	break;

	case STEP:
		pAct = new StepByStep(this);
	break;

	case EDITCONNECTOR:
		pOut->PrintMessage("Action: a click on the first and last statement to edit connector, Click anywhere");
		break;

	case COMPLEX:
		pOut->PrintMessage("Action: ADD complex assignment, Click anywhere");
		break;
	case STATUS:
		pOut->PrintMessage("Action: a click on the Status Bar, Click anywhere");
		break;

	case DSN_TOOL:
		pOut->PrintMessage("Action: a click on the Design Tool Bar, Click anywhere");
		break;

	case SIMULATION_MODE:
		
		UI.AppMode = SIMULATION;
		pOut->ClearToolBar(1);
		pOut->ClearUpperToolBar(1);
		pOut->drawSimulationToolBar();
		pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);
		pOut->PrintMessage("Action: Switch to Simulation Mode, creating simualtion tool bar");

		break;
	case DESIGNMODE:
		Validate = 0;
		UI.AppMode = DESIGN;
		pOut->ClearUpperToolBar(1);
		pOut->drawToolBar();
		pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);
		pOut->PrintMessage("Action: Switch to Design Mode, creating Design tool bar");

		break;
	case CLICK_ON_DRAWING_AREA:
		pAct = new Select(this,pointer);
		break;
	case EXIT:
		exit(3);
		break;
	default:
		
		break;
	}
	/*if (ActType == ADD_START) {
		
		pWind->FlushMouseQueue();
		pWind->FlushKeyQueue();

		pWind->SetFont(20, BOLD, BY_NAME, "Arial");
		
		pWind->SetBuffering(true);

		int RectULX = pointer.x;
		int RectULY = pointer.y;
		int RectWidth = UI.Start_Width;
		int recH = UI.Start_Height;

		bool bDragging = false;

		
		int iXOld = 0;
		int iYOld = 0;
		
		image im;
		
		//pWind->StoreImage(im, 0, 0, pWind->GetWidth() - 1, pWind->GetHeight() - 1);
		// Loop until there escape is pressed
		while (pWind->GetButtonState(LEFT_BUTTON, pointer.x, pointer.y) == BUTTON_UP)
		{
			pWind->SetPen(WHITE);
			pWind->SetBrush(WHITE);
			pWind->DrawImage(lastscreen, 0, 0);
			
			if (bDragging == false) {
				if (pWind->GetButtonState(LEFT_BUTTON, pointer.x, pointer.y) == BUTTON_DOWN) {
					if (((pointer.x > RectULX) && (pointer.x < (RectULX + RectWidth))) && ((pointer.y > RectULY) && (pointer.y < (RectULY + RectWidth)))) {
						bDragging = true;
						iXOld = pointer.x; iYOld = pointer.y;
					}
				}
			}
			else {
				if (pWind->GetButtonState(LEFT_BUTTON, pointer.x, pointer.y) == BUTTON_UP) {
					bDragging = false;
				}
				else {
					if (pointer.x != iXOld) {
						RectULX = RectULX + (pointer.x - iXOld);
						iXOld = pointer.x;
					}
					if (pointer.y != iYOld) {
						RectULY = RectULY + (pointer.y - iYOld);
						iYOld = pointer.y;
					}
				}

			}
			pointer.x = pointer.x; pointer.y = pointer.y;
			pOut->DrawStart(&pointer, UI.Start_Width, UI.Start_Height, "Start", true);
			// Draw some info 
			pWind->SetPen(BLACK);
			// Update the screen buffer
			pWind->UpdateBuffer();
		}
		pIn->GetPointClicked(po.x, po.y, 0);
	}*/

	if(pAct != NULL)
	{
		pAct->ReadActionParameters();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
	if (ActType == CLEARDRAWINGAREA) {
		screen = pOut->lastscreen;
		lastscreen = pOut->lastscreen;
		pWind->UpdateBuffer();
	}
	if (ActType != NOACTION && ActType != HOVER && ActType != arrowDown && ActType != arrowUp ) {
		
		pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);
		pWind->StoreImage(screen, 0, 0, UI.width, UI.height - UI.StBrWdth);
		
		
		pWind->DrawImage(lastscreen, 0, 0);
		
		if (UI.AppMode == DESIGN)
			pWind->DrawImage(pOut->lastTlBr, 0, 0);
		pWind->UpdateBuffer();
	}
	pWind->UpdateBuffer();
	//Execute the created action
	
}

bool ApplicationManager::getSimulate()
{
	return simulate;
}

void ApplicationManager::setSimulate(bool x)
{
	simulate = x;
}

 

//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//
//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	StatList.push_back(pStat);
	if (pStat->GetType() == "Read") VarList.push_back(pStat);
	if (pStat->IsSelected())
		SelectedStat.push_back(pStat);
	
}


void ApplicationManager::SetHead(Statement* pStat)
{
	Head = pStat;
}

Statement* ApplicationManager::GetHead()
{
	return Head;
}

Statement* ApplicationManager::GetIDST(int s)
{
	for (int i = 0;i < StatList.size();i++) {
		if (StatList[i]->getID() == s)
		{
			return StatList[i];
		}
	}
	return NULL;
}

void ApplicationManager::SetTail(Statement* T)
{
	Tail = T;
}

Statement* ApplicationManager::GetTail()
{
	return Tail;
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point p1, Point p2) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	///Add your code here to search for a statement given a point P(x,y)	
	Point n1, n2;
	Point a1(p2.x, p1.y), a2(p1.x, p2.y);
	for (int i = 0; unsigned(i) < StatList.size(); i++) {
		StatList[i]->getCoordinates(n1, n2);
		if ((p1.x >= n1.x && p1.x <= n2.x && p1.y >= n1.y && p1.y <= n2.y)
			|| (p2.x >= n1.x && p2.x <= n2.x && p2.y >= n1.y && p2.y <= n2.y)
			|| (a1.x >= n1.x && a1.x <= n2.x && a1.y >= n1.y && a1.y <= n2.y)
			|| (a2.x >= n1.x && a2.x <= n2.x && a2.y >= n1.y && a2.y <= n2.y))
			return StatList[i];
	}
	return NULL;
}
Statement* ApplicationManager::GetStatement(Point p1) const {
	Point n1, n2;
	for (int i = 0; unsigned(i) < StatList.size(); i++) {
		StatList[i]->getCoordinates(n1, n2);
		if ((p1.x >= n1.x && p1.x <= n2.x && p1.y >= n1.y && p1.y <= n2.y)){
			return StatList[i];
		}
	}
	return NULL;
}
Statement* ApplicationManager::GetStatement(string L) const
{
	for (int i = 0; unsigned(i) < StatList.size(); i++) {
		if (StatList[i]->GetLHS() == L && StatList[i]->GetType() == "Read") return StatList[i];
	}
	return nullptr;
}
void ApplicationManager::PushConnector(Connector* pConn)
{
	ConnList.push_back(pConn);
}
void ApplicationManager::SetValidate(bool x)
{
	Validate = x;
}
bool ApplicationManager::GetValidate()
{
	return Validate;
}
Statement* ApplicationManager::GetHeighestState()
{
	return HeighesitStat;
}
Connector* ApplicationManager::GetConnector(Point P) const
{
	return nullptr;
}
void ApplicationManager::Save(ofstream& ofile)
{
	ofile << StatList.size() << endl;
	for (int i = 0; unsigned(i) < StatList.size(); i++)
	{
		StatList[i]->Save(ofile);

	}
	ofile << ConnList.size() << endl;
	
	for (int i = 0; unsigned(i) < ConnList.size(); i++)
	{
		
		if (ConnList[i]->getSrcStat()->GetType() == "Condition") {
			Condition* c = dynamic_cast<Condition*>(ConnList[i]->getSrcStat());
			if (!c->IsSaved()) {
				ConnList[i]->Save(ofile);
				c->SetSaved(1);
			}
			else {
				c->SetSaved(0);
			}
			
		}
		else {
			ConnList[i]->Save(ofile);
		}
	}

}
void ApplicationManager::DeleteConnector(Connector* conn)
{
	for (int i = 0; unsigned(i) < ConnList.size(); i++) {
		if (ConnList[i] == conn) {
			ConnList.erase(ConnList.begin() + i);
		}
	}
	delete conn;
}
vector<Statement*>* ApplicationManager::GetVarList()
{
	return &VarList;
}
vector<Statement*>* ApplicationManager::GetUnValidList()
{
	return &UnValidList;
}
vector<Statement*>* ApplicationManager::GetStateList()
{
	return &StatList;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
vector<Statement*>* ApplicationManager::GetSelectedStatement() 
{	
	return &SelectedStat;
}

vector<Connector*>* ApplicationManager::GetConnectorList()
{
	return &ConnList;
}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user

void ApplicationManager::SetSelectedStatement(Statement* pStat, int index)
{
	if (SelectedStat.size() == 0)
	{
		SelectedStat.push_back(pStat);
		return;
	}
	Point ArrBack,c;
	Point PS;
	SelectedStat.back()->getCoordinates(ArrBack, c);
	pStat->getCoordinates(PS, c);
	if (PS.y > ArrBack.y) {
		SelectedStat.push_back(pStat);
		return;
	}
	Point curr, prev;
	for (int i = 0; unsigned(i) < SelectedStat.size();) {
		SelectedStat[i]->getCoordinates(curr, c);
		//SelectedStat[i - 1]->getCoordinates(prev, c);
		if (PS.y < curr.y) {
			SelectedStat.insert(SelectedStat.begin() + i, pStat);
			return;
		}
		else {
			i++;
		}
	}
}

void ApplicationManager::SetValidStatement(Statement* S,bool v)
{
	S->SetValid(v);
	if (!v) {
		UnValidList.push_back(S);
	}
	else {
		for (int i = 0; unsigned(i) < UnValidList.size(); i++) {
			if (UnValidList[i] == S) {
				UnValidList.erase(UnValidList.begin() + i);
				return;
			}
		}
	}
}

void ApplicationManager::SetAllUnValid(Statement* S)
{
	string x = S->GetLHS();
	for (int i = 0; unsigned(i) < StatList.size(); i++)
	{
		if (StatList[i]->GetLHS() == x && StatList[i] != S) {
			SetValidStatement(StatList[i], 0);
		}
	}
}

void ApplicationManager::CheckUnValidList(string L)
{
	for (int i = 0; unsigned(i) < UnValidList.size(); i++) {
		if (UnValidList[i]->GetLHS() == L) {
			SetValidStatement(UnValidList[i], 1);
		}
	}
	UpdateInterface();
}

void ApplicationManager::unSelectStatement(Statement* pStat, bool allststements)
{
	if (allststements) {
		for (int i = 0; unsigned(i) < StatList.size(); i++) StatList[i]->SetSelected(0);
		while (SelectedStat.size()!=0) SelectedStat.pop_back();
		HeighesitStat = NULL;
		return;
	}
	else {
		Statement* SecHi = NULL;
		Point curr,b;
		Point Hi(-2,-2), c;
		for (int i = 0; unsigned(i) < SelectedStat.size(); i++) {
			if (SelectedStat[i] == pStat)
			{
				SelectedStat.erase(SelectedStat.begin() + i);
				if (pStat == HeighesitStat) {
					if (SelectedStat.size() == 0) HeighesitStat = NULL;
					else {
						HeighesitStat = SecHi;
					}
				}
				return;
			}
		}
	}
	
}

void ApplicationManager::deleteStatement(Statement* pStat)
{
	for (int i = 0; unsigned(i) < StatList.size(); i++) {
		if (StatList[i] == pStat) {
			StatList.erase(StatList.begin() + i);
			break;
		}
	}
	for (int i = 0; unsigned(i) < VarList.size(); i++) {
		if (VarList[i] == pStat) {
			VarList.erase(VarList.begin() + i);
			break;
		}
	}

	for (int i = 0; unsigned(i) < SelectedStat.size(); i++) {
		if (SelectedStat[i] == pStat) {
			SelectedStat.erase(SelectedStat.begin() + i);
			break;
		}
	}

	delete pStat;
}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	//Draw all statements
	for(int i=0; unsigned(i) <StatList.size(); i++)
		StatList[i]->Draw(pOut);
	


	//Draw all connections
	for(int i=0; unsigned(i) < ConnList.size(); i++)
		ConnList[i]->Draw(pOut);

}
void ApplicationManager::setcpy(Statement* P)
{
	/*pcpy = p;*/
}
Statement* ApplicationManager::getcpy()
{
	return pcpy;
}
void ApplicationManager::setcpytype(int c)
{
	cpyt = c;
}
int ApplicationManager::getcpytype()
{
	return cpyt;
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
// 
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; unsigned(i) < StatList.size(); i++)
		delete StatList[i];
	for(int i=0; unsigned(i) < ConnList.size(); i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
}
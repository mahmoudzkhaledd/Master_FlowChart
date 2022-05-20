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
	** please use display 100% in display layout in windows settings as our program window is too wide
*/

#include<sstream>
#include "Output.h"
#include<string>
#include<iostream>
Output::Output()
{
	
	cleanStBr = 1;


	
	maxiconsH = 10;
	maxToolBar = 9;
	toolBarScope.first = 0;
	toolBarScope.second = -1;

	arrowUPExist = 0;
	arrowDownExist = 0;
	
	arrowD = new image("images\\Icons\\ArrowDown.JPG", JPEG);
	arrowU = new image("images\\Icons\\ArrowUp.JPG", JPEG);
	
	imH = -1;
	imV = -1;
	imS = -1;

	im.resize(0);
	//Initialize user interface parameters
	UI.TlBrHeight = 60;
	UI.width = 1400;
	UI.height = 800;
	UI.wx = 5;
	UI.wy = 5;

	UI.AppMode = DESIGN;	//Design Mode is the default mod

	UI.StBrWdth = 50;
	UI.TlBrWdth = 50;
	UI.MnItWdth = 80;

	UI.shapesColor = ORANGE;
	UI.DrawClr =	RED ;
	UI.HiClr =	BLUE ;

	UI.MsgClr = RED;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;

	UI.Start_Width = 150;
	UI.Start_Height = 65;

	UI.read_width = 150;
	UI.read_height = 50;

	UI.CondWidth = 100;
	UI.CondHeight = 80;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	
	//HWindow->HelloWindow();
	pWind->DrawRectangle(0, 0, UI.width, UI.height);
	
	//Change the title
	pWind->ChangeTitle("Master Flow Chart");
	pWind->SetPen(RED, 3);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	
	pWind->SetBuffering(1);
	
	CreateDesignToolBar();
	CreateStatusBar();
	
	arrowD->type = DownArrow;
	arrowU->type = UpArrow;
	UI.MainWindow = pWind;
	pWind->StoreImage(lastTlBr, 0, 0, UI.TlBrWdth - 1, UI.height - UI.StBrWdth);
	pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);

	pWind->StoreImage(cleanDA, UI.TlBrWdth, UI.TlBrHeight, UI.width - UI.TlBrWdth, UI.height - UI.StBrWdth- UI.TlBrHeight);
	//UI.MainOutpot = this;
}

void Output::drawName(Point* Left,string Text){
	pWind->SetBrush(UI.shapesColor);
	pWind->SetPen(BLACK, 0);
	stringstream ss(Text);
	getline(ss, Text, '.');
	int strw = 0, strh = 0;
	pWind->GetStringSize(strw, strh, Text);
	if (Left->y + strh + 20 < UI.height - UI.StBrWdth && Left->x + strw + 20 < UI.width - 20) {
		pWind->DrawRectangle(Left->x, Left->y, Left->x + strw + 20, Left->y + strh+20);
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(Left->x + (strw + 20)/2 - strw / 2 , Left->y+(strh + 20)/2 - strh / 2 , Text);
	}
	else if (Left->x + strw + 20 >= UI.width - 20) {
		pWind->DrawRectangle(Left->x, Left->y, Left->x - strw - 20, Left->y + strh + 20);
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(Left->x - (strw + 20) / 2 - strw / 2, Left->y + (strh - 20) / 2 + strh / 2, Text);
	}
	else if(Left->y + strh + 20 >= UI.height - UI.StBrWdth) {
		pWind->DrawRectangle(Left->x, Left->y, Left->x + strw + 20, Left->y - strh - 20);
		pWind->SetPen(BLACK, 2);
		pWind->DrawString(Left->x + (strw + 20) / 2 - strw / 2, Left->y - (strh + 20) / 2 - strh / 2, Text);
	}
	



}

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	UI.StBrWdth -= 2;
	pWind->DrawLine(0, UI.height - UI.StBrWdth, UI.width, UI.height - UI.StBrWdth);
	UI.StBrWdth += 2;
}
//////////////////////////////////////////////////////////////////////////////////////////
//======================================================================================//
//								Interface Functions										//
//======================================================================================//

//Draws the Design Menu
//Arrow Up and Down Draw and Function

void Output::ArrowDown() {
	
	ClearToolBar(1);
	DrawArrowUp();

	toolBarScope.second++;
	toolBarScope.first++;
	for (int j = 0; j <= imV; j++) {
		setCoordinates(im[j], im[j]->p.first.first, im[j]->p.first.second - im[j]->GetHeight() - 20, im[j]->p.second.first, im[j]->p.second.second - im[j]->GetHeight() - 20);
		if (j < toolBarScope.second && j>toolBarScope.first)
			im[j]->isDrawn = 1;
	}
	drawToolBar();
	pWind->StoreImage(lastTlBr, 0, 0, UI.TlBrWdth - 1, UI.height - UI.StBrWdth);
	
}
void  Output::ArrowUp() {
	ClearToolBar(1);
	toolBarScope.first--;
	toolBarScope.second--;
	int shift = 20;
	for (int j = 0; j <= imV; j++) {
		setCoordinates(im[j], im[j]->p.first.first, im[j]->p.first.second + im[j]->GetHeight() + shift, im[j]->p.second.first, im[j]->p.second.second + im[j]->GetHeight() + shift);
		if (j < toolBarScope.second && j>toolBarScope.first)
			im[j]->isDrawn = 1;
	}
	drawToolBar();
	pWind->StoreImage(lastTlBr, 0, 0, UI.TlBrWdth - 1, UI.height - UI.StBrWdth);
	
}
void Output::DrawArrowDown() {
	arrowD->isDrawn = 1;
	arrowDownExist = 1;
	setCoordinates(arrowD, 0, UI.height - UI.StBrWdth - arrowD->GetHeight(), arrowD->GetWidth(), UI.height - UI.StBrWdth);
	pWind->DrawImage(arrowD, arrowD->p.first.first, arrowD->p.first.second);
}
void Output::SetBrush(color C)
{
	pWind->SetBrush(C);
}
void Output::DrawArrowUp() {
	arrowU->isDrawn = 1;
	arrowUPExist = 1;
	setCoordinates(arrowU, 0, 90 - arrowU->GetHeight(), arrowD->GetWidth(), 90);
	pWind->DrawImage(arrowU, 0, 90 - arrowU->GetHeight());
}
/////////////////////////////////////
void Output::DrawingArea() {
	int space = 15;
	for (int i = UI.TlBrWdth; i < UI.width; i+=space) {
		for (int j = UI.TlBrHeight; j < UI.height - UI.StBrWdth; j += space) {
			pWind->DrawPixel(i, j);
		}
	}
	int width = UI.width - UI.TlBrWdth;
	int height = UI.height - UI.StBrWdth - UI.TlBrHeight;

	pWind->StoreImage(cleanDA, UI.TlBrWdth+1, UI.TlBrHeight+1, width-1, height-1);
}
void Output::drawToolBar() {
	ClearToolBar(0);
	DrawingArea();
	if (arrowDownExist || arrowD->isDrawn) DrawArrowDown();
	if (arrowUPExist) DrawArrowUp();
	for (int i = toolBarScope.first; i <= imV + imH + 1; i++) {
		if (im[i]->t == 1 && i <= toolBarScope.second) {
			if (im[i]->p.second.second + 10 <= UI.height - UI.StBrWdth) {
				pWind->DrawImage(im[i], 0, im[i]->p.first.second);
				im[i]->isDrawn = 1;
			}
			else {
				im[i]->isDrawn = 0;

				if ((im.size() - i >= 1 && !arrowD->isDrawn) || arrowDownExist) DrawArrowDown();
			}
		}
		else if (im[i]->t == 0) {
			pWind->DrawImage(im[i], im[i]->p.first.first, 0);
			im[i]->isDrawn = 1;
		}
	}
}
void Output::drawSimulationToolBar() {
	for (int i = imV + imH + 2; unsigned(i) < im.size(); i++) {
		pWind->DrawImage(im[i], im[i]->p.first.first, 0);
		im[i]->isDrawn = 1;
	}
}
void Output::setCoordinates(image* IM, int x, int y, int z, int w) {
	IM->p.first.first = x;
	IM->p.first.second = y;
	IM->p.second.first = z;
	IM->p.second.second = w;
}
void Output::CreateArrangedImage(image* IM, ImageFunction i, bool x, MODE appMODE) {
	int toolBarY = (imV == -1) ? 90 : im.back()->p.second.second + 20;
	int toolBarX = (imH == -1) ? 90 : im.back()->p.second.first + 25;
	int toolBarS = (imS == -1) ? 90 : im.back()->p.second.first + 20;
	IM->type = i;
	if (appMODE == DESIGN) {
		IM->t = x;
		if (x) {
			imV++;
			setCoordinates(IM, 0, toolBarY, IM->GetWidth(), toolBarY + IM->GetHeight());
			if (toolBarScope.second <= maxToolBar)
				toolBarScope.second++;
			if(IM->GetWidth() + 10 > unsigned(UI.TlBrWdth))
				UI.TlBrWdth = IM->GetWidth() + 10;
		}
		else {
			imH++;
			setCoordinates(IM, toolBarX, 0, toolBarX + IM->GetWidth(), IM->GetHeight());
			if(IM->GetHeight() + 10 > unsigned(UI.TlBrHeight))
				UI.TlBrHeight = IM->GetHeight() + 10;
		}
	}
	else if (appMODE == SIMULATION) {
		imS++;
		setCoordinates(IM, toolBarS, 0, toolBarS + IM->GetWidth(), IM->GetHeight());
		
	}
	
	
	im.push_back(IM);
}
void Output::CreateDesignToolBar()
{
	UI.AppMode = DESIGN;	//Design Mode
	ClearToolBar(0);
	//fill the tool bar//
	//You can draw the tool bar icons in any way you want.
	//Here add left ToolBar items 
	CreateArrangedImage(new image("images\\Icons\\Start.jpg", JPEG), start, 1);
	CreateArrangedImage(new image("images\\Icons\\Start.jpg", JPEG), End, 1);
	CreateArrangedImage(new image("images\\Icons\\Read.jpg", JPEG), read, 1);
	CreateArrangedImage(new image("images\\Icons\\Read.jpg", JPEG), write, 1);
	CreateArrangedImage(new image("images\\Icons\\Assign.jpg", JPEG), simpleAssign, 1);
	CreateArrangedImage(new image("images\\Icons\\Assign.jpg", JPEG), varAssign, 1);
	CreateArrangedImage(new image("images\\Icons\\Assign.jpg", JPEG), operatorassignment, 1);
	CreateArrangedImage(new image("images\\Icons\\Condition.jpg", JPEG), ConditionStatement, 1);
	CreateArrangedImage(new image("images\\Icons\\Connector.jpg", JPEG), ConnectorButton, 1);
	CreateArrangedImage(new image("images\\Icons\\exit.jpg", JPEG), Exit, 1);
	
	CreateUpperToolBar();

	drawToolBar();
	CreateSimulationToolBar();
	//Draw a line behiend the toolbar
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(UI.TlBrWdth, UI.TlBrHeight, UI.TlBrWdth, UI.height - UI.StBrWdth);
	pWind->DrawLine(UI.TlBrWdth, UI.TlBrHeight, UI.width, UI.TlBrHeight);
}
void Output::CreateSimulationToolBar()
{
	//Here add Simulation ToolBar items
	CreateArrangedImage(new image("images\\Icons\\Simulation\\Design.jpg", JPEG), designMode, 0, SIMULATION);
	CreateArrangedImage(new image("images\\Icons\\Simulation\\play.jpg", JPEG), run, 0, SIMULATION);
	CreateArrangedImage(new image("images\\Icons\\Simulation\\Generate.jpg", JPEG), generateCode, 0, SIMULATION);
	CreateArrangedImage(new image("images\\Icons\\Simulation\\Step.jpg", JPEG), step_by_step, 0, SIMULATION);
	CreateArrangedImage(new image("images\\Icons\\Simulation\\Validate.jpg", JPEG), validate, 0, SIMULATION);
}
void Output::CreateUpperToolBar() {
	//Here Add Upper ToolBar Items//
	CreateArrangedImage(new image("images\\Icons\\Simulation.jpg", JPEG), simulation, 0);
	CreateArrangedImage(new image("images\\Icons\\copy.jpg", JPEG), Copy, 0);
	CreateArrangedImage(new image("images\\Icons\\cut.jpg", JPEG), Cut, 0);
	CreateArrangedImage(new image("images\\Icons\\paste.jpg", JPEG), Paste, 0);
	CreateArrangedImage(new image("images\\Icons\\delete.jpg", JPEG), Delete, 0);
	CreateArrangedImage(new image("images\\Icons\\redo.jpg", JPEG), Redo, 0);
	CreateArrangedImage(new image("images\\Icons\\undo.jpg", JPEG), Undo, 0);
	CreateArrangedImage(new image("images\\Icons\\ZoomIN.jpg", JPEG), zoomIn, 0);
	CreateArrangedImage(new image("images\\Icons\\ZoomOut.jpg", JPEG), zoomOut, 0);
	CreateArrangedImage(new image("images\\Icons\\Resize.jpg", JPEG), resize, 0);
	CreateArrangedImage(new image("images\\Icons\\clean.jpg", JPEG), clear, 0);
	CreateArrangedImage(new image("images\\Icons\\edit.jpg", JPEG), editStatement, 0);
	CreateArrangedImage(new image("images\\Icons\\Comment.jpg", JPEG), comment, 0);
	CreateArrangedImage(new image("images\\Icons\\Save.jpg", JPEG), save, 0);
	CreateArrangedImage(new image("images\\Icons\\Select.jpg", JPEG), selection, 0);
	CreateArrangedImage(new image("images\\Icons\\Load.jpg", JPEG), load, 0);
	CreateArrangedImage(new image("images\\Icons\\Complex.jpg", JPEG), complexassign, 0);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	if (cleanStBr == 0) {
		pWind->SetPen(WHITE, 0);
		pWind->SetBrush(WHITE);
		pWind->DrawRectangle(0, UI.height - UI.StBrWdth + 4, UI.width, UI.height);
		pWind->SetPen(RED, 3);
		cleanStBr = 1;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{ 
	pWind->DrawImage(lastscreen, 0, 0);
	pWind->DrawImage(lastTlBr, 0, 0);
	pWind->StoreImage(lastscreen, 0, 0, UI.width, UI.height - UI.StBrWdth);
	
}
void Output::ClearToolBar(bool x) {
	if (x) { // to clear tool bar and disable toolbar icons for simulation mode and arrows
		for (int i = toolBarScope.first; i < toolBarScope.second; i++) {
			im[i]->isDrawn = 0;
		}
	}
	pWind->SetPen(WHITE, 0);
	pWind->SetBrush(WHITE);
	int x1, y1, x2, y2;

	x1 = 0;
	x2 = UI.TlBrWdth - 1;
	if (UI.AppMode == DESIGN) {
		y1 = (arrowU->isDrawn == 0) ? 0 : arrowU->p.second.second - 1;
		y2 = (arrowD->isDrawn == 0) ? UI.height - UI.StBrWdth - 1 : UI.height - UI.StBrWdth - arrowD->GetHeight() - 1;
	}
	else if (UI.AppMode == SIMULATION) {
		y1 = 0;
		y2 = UI.height - UI.StBrWdth - 3;
		arrowU->isDrawn = 0;
		arrowD->isDrawn = 0;
	}
	pWind->DrawRectangle(x1, y1, x2, y2);
	pWind->SetPen(RED, 3);
}
void Output::ClearUpperToolBar(bool x) {
	//to clear upper toolbar 0 for design mode 1 for simulation mode
	if (x) {
		if (UI.AppMode == DESIGN) {
			for (int i = imV + 1; unsigned(i) < im.size(); i++) {
				im[i]->isDrawn = 0;
			}
		}
		else if (UI.AppMode == SIMULATION) {
			for (int i = imV + imH + 2; unsigned(i) < im.size(); i++) {
				im[i]->isDrawn = 0;
			}
		}
	}
	else {
		NULL;
	}
	pWind->SetPen(WHITE, 0);
	pWind->SetBrush(WHITE);
	int x1, y1, x2, y2;
	x1 = 0;
	y1 = 0;
	x2 = UI.width;
	y2 = UI.TlBrHeight - 3;
	pWind->DrawRectangle(x1, y1, x2, y2);
	pWind->SetPen(RED, 3);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	pWind->SetPen(UI.MsgClr, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StBrWdth / 1.5) - 6, msg);
	pWind->SetPen(RED, 3);
	pWind->UpdateBuffer();
	cleanStBr = 0;
}
//======================================================================================//
//								Statements Drawing Functions							//
//======================================================================================//
//Draw assignment statement and write the "Text" on it

void Output::DrawAssign(Point* Left, string Text, bool Selected, int width, int height)
{
	

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	//Draw the statement block rectangle

	int strw = 0, strh = 0;
	pWind->GetStringSize(strw, strh, Text);

	pWind->GetStringSize(strw, strh, Text);
	

	pWind->DrawRectangle(Left->x, Left->y, Left->x + width, Left->y + height, FILLED);
	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left->x + width / 2 - strw / 2, Left->y + height / 2 - strh / 2, Text);
	
}
void Output::DrawStart(Point* Left, string TEXT, bool Selected, int width, int height)
{
	
	//pWind->SetPen(WHITE, 0);
	

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	//Draw the statement block rectangle
	
	int strw = 0, strh = 0;
	pWind->GetStringSize(strw, strh, TEXT);



	//pWind->DrawEllipse(Left->x, Left->y, Left->x + r1, Left->y + r2);
	pWind->DrawRectangle(Left->x, Left->y, Left->x + width, Left->y + height, FILLED, 30, 30);
	//Write statement text
	pWind->SetPen(BLACK, 20);
	pWind->DrawString(Left->x + width / 2 - strw / 2, Left->y + height / 2 - strh / 2, TEXT);
	
}
void Output::DrawReadWrite(Point* Left, string TEXT, bool Selected, int width, int height) {
	int w = width, h = height, space = 20;
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color
	int strw = 0, strh = 0;

	pWind->GetStringSize(strw, strh, TEXT);


	int cw = (2 * Left->x + space) / 2 + w / 2 - strw / 2;
	int ch = (2 * Left->y + h) / 2 - strh / 2;
	
	/*if (strw / 2 + 20 > width) {
		w = strw + 40;
		cw = (2 * Left->x + space) / 2 + 20;
	}*/
	
	/*int boardX[] = { Left->x + space , Left->x + w + space , Left->x + w , Left->x + space + w };
	int boardY[] = { Left->y         , Left->y             , Left->y + h , Left->y             };*/


	int boardX[] = { Left->x         , Left->x + w , Left->x + space + w , Left->x + space };
	int boardY[] = { Left->y         , Left->y             , Left->y + h , Left->y + h };
	pWind->DrawPolygon(boardX, boardY, 4, FILLED);

	/*pWind->DrawLine(Left->x + space, Left->y , Left->x + w + space, Left->y);
	pWind->DrawLine(Left->x + w, Left->y+h, Left->x + space + w, Left->y );


	pWind->DrawLine(Left->x , Left->y+h , Left->x + w, Left->y + h);
	pWind->DrawLine(Left->x, Left->y+h, Left->x + space, Left->y );*/



	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(cw, ch, TEXT);
}
void Output::drawCondition(Point* Left, string TEXT, bool Selected, int width, int height) {
	int strw, strh;
	pWind->GetStringSize(strw, strh, TEXT);
	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);	//use normal color

	
	int boardX[] = { Left->x  , Left->x + width / 2 , Left->x + width , Left->x + width / 2 };
	int boardY[] = { Left->y + height / 2, Left->y , Left->y + height / 2, Left->y + height };

	pWind->DrawPolygon(boardX, boardY, 4, FILLED);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString((2 * Left->x + width) / 2 - strw / 2 + 5, (2 * Left->y + height) / 2 - strh / 2, TEXT);
}
void Output::DrawConnector(Point* start, Point* end, bool Selected)
{
	
	if (Selected)    //if stat is selected, it should be highlighted
		pWind->SetPen(UI.HiClr, 3);    //use highlighting color
	else
		pWind->SetPen(UI.DrawClr, 3);    //use normal color
	
	//pWind->DrawLine(start->x,start->y,end->x,end->y);


	pWind->DrawLine(start->x, start->y, end->x, start->y);
	pWind->DrawLine(end->x, start->y, end->x, end->y);

	if (start->y == end->y && (start->x > end->x)) {
		pWind->DrawLine(end->x, end->y, end->x + 10, end->y + 10);
		pWind->DrawLine(end->x, end->y, end->x + 10, end->y - 10);
	}
	else if ((start->y == end->y && (start->x < end->x))) {
		pWind->DrawLine(end->x - 10, end->y + 10, end->x, end->y);
		pWind->DrawLine(end->x - 10, end->y - 10, end->x, end->y);
	}
	// Arrow
	if (start->y <= end->y && start->y != end->y)
	{
		pWind->DrawLine(end->x - 10, end->y - 10, end->x, end->y);
		pWind->DrawLine(end->x + 10, end->y - 10, end->x, end->y);
	}
	else if (start->y > end->y && start->y != end->y)
	{
		pWind->DrawLine(end->x, end->y, end->x - 10, end->y + 10);
		pWind->DrawLine(end->x, end->y, end->x + 10, end->y + 10);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

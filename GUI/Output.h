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

#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"
#include"AnotherWindow.h"
#include<algorithm>
#include <utility>
#include<vector>

class Output	//The application manager should have a pointer to this class
{
private:
	int maxToolBar ;
	image cleanDA;
	int maxiconsH;
	bool cleanStBr; // 1 for cleaned stBr
public:
	bool arrowUPExist;
	bool arrowDownExist;
	pair<int, int> toolBarScope;
	image* arrowD ;
	image* arrowU ;
	image lastscreen;
	image lastTlBr;
	window* pWind; //Pointer to the Graphics Window
	vector<image*> im;

	int imH ;
	int imV ;
	int imS ;

	Output();
	

	void ArrowUp();
	void ArrowDown();
	void setCoordinates(image* IM, int x, int y, int z, int w);
	void CreateArrangedImage(image* IM, ImageFunction i, bool x, MODE appMODE = DESIGN);
	window* CreateWind(int, int, int, int);
	void CreateDesignToolBar();	//Tool bar of the design mode
	void CreateSimulationToolBar();
	void CreateUpperToolBar();


	void drawToolBar();
	void drawSimulationToolBar();
	void drawName(Point* Left, string Text);
	void DrawingArea();
	void DrawArrowUp();
	void DrawArrowDown();

	void SetBrush(color C);
	//Tool bar of the simulation mode
	void ClearToolBar(bool x);
	void CreateStatusBar();
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea();	//Clears the drawing area
	void ClearUpperToolBar(bool x);
	// -- Statements Drawing Functions

	void DrawConnector(Point *start, Point *end, bool Selected = 0);
	void DrawReadWrite(Point* Left, string TEXT, bool Selected = 0, int width = UI.read_width, int height = UI.read_height);
	void drawCondition(Point* Left, string TEXT = "", bool Selected = 0, int width = UI.CondWidth, int height = UI.CondHeight);
	void DrawStart(Point* Left, string TEXT, bool Selected = 0, int width = UI.Start_Width, int height = UI.Start_Height);
	void DrawAssign(Point* Left, string Text, bool Selected = false,  int width = UI.ASSGN_WDTH, int height = UI.ASSGN_HI);


	//TODO: Add similar functions for drawing all other statements.
	//		e.g. DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc.
	//		Decide the parameters that should be passed to each of them.


	void PrintMessage(string msg);	//Prints a message on Status bar

	~Output();
};

#endif
#pragma once
#include"AnotherWindow.h"
#include"../CMUgraphicsLib/CMUgraphics.h"
#include"../CMUgraphicsLib/image.h"
enum DialogAction {
	YES,NO, HOVERYES, HOVERNO,UNHOVER,
};
class MyWindow 
{
private:
	window* pWind;
	window* old;
	image* im;
	// HELLO WINDOW :
	int hWidth;
	int hHeight;
	// EXIT WINDOW
	bool hYES = 0;
	bool hNO = 0;
	bool unH = 0;
	int EWidth;
	int Eheight;
	int ButtonX1 = 25;
	int ButtonY1 = 90;
	int ButtonX2 = 125;
	int ButtonY2 = 120;
	DialogAction d;

public:
	MyWindow(window* p);
	DialogAction getAction();
	void DrawWindow();
	void ExitWindow();
};


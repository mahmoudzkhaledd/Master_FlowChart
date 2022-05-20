#include "AnotherWindow.h"
#include<iostream>
using namespace std;
#include<time.h>
MyWindow::MyWindow(window* p) {
	hWidth = 974;
	hHeight = 566;
	// EXIT WINDOW
	EWidth = 320;
	Eheight = 165;
	old = pWind;
	pWind = p;
	
}

DialogAction MyWindow::getAction()
{
	int x = 0, y = 0;
	buttonstate b{};
	b= pWind->GetButtonState(LEFT_BUTTON, x, y);
	if (x >= ButtonX1 && x <= ButtonX2 && y >= ButtonY1 && y <= ButtonY2 && b == BUTTON_DOWN)
		return YES;

	else if (x >= ButtonX1 && x <= ButtonX2 && y >= ButtonY1 && y <= ButtonY2)
		return HOVERYES;
	else if (x >= 150 && x <= 250 && y >= 90 && y <= 120 && b == BUTTON_DOWN)
		return NO;
	else if (x >= 150 && x <= 250 && y >= 90 && y <= 120)
		return HOVERNO;
	else return UNHOVER;
}

void MyWindow::DrawWindow(){
	pWind = new window(EWidth, Eheight, 200, 200);
	pWind->SetBuffering(1);
	pWind->ChangeTitle("");
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	
	ExitWindow();
}

void MyWindow::ExitWindow(){
	
	
	
	pWind->DrawRectangle(0, 0, EWidth, Eheight);
	pWind->SetPen(BLACK, 0);
	pWind->DrawString(ButtonX1+30, ButtonY1-50,"Do You Want to Exit ?");
	//Draw YES
	pWind->SetBrush(ORANGE);
	pWind->DrawRectangle(ButtonX1, ButtonY1, ButtonX2, ButtonY2,FILLED);
	pWind->SetPen(WHITE);
	pWind->DrawString(25 + 34, 97, "YES");
	//Draw NO

	pWind->SetBrush(ORANGE);
	pWind->DrawRectangle(150, 90, 250, 120);
	pWind->SetPen(WHITE);
	pWind->DrawString(100 + 2 * 25 + 38, 90 + 5, "NO");
	DialogAction d = getAction();
	while (1) { 
		
		if (d == YES) {
			exit(3);
			break;
		}
		else if (d == NO) { 
			delete pWind;
			pWind = old;
			return;
		}
		else if (d == HOVERYES && !hNO) {
			hNO = 1;
			unH = 0;
			pWind->SetBrush(YELLOW);
			pWind->DrawRectangle(ButtonX1, ButtonY1, ButtonX2, ButtonY2, FILLED);
			pWind->SetPen(WHITE);
			pWind->DrawString(25 + 34, 97, "YES");
		}
		else if (d == HOVERNO && !hYES) {
			hYES = 1;
			unH = 0;
			pWind->SetBrush(YELLOW);
			pWind->DrawRectangle(150, 90, 250, 120);
			pWind->SetPen(WHITE);
			pWind->DrawString(100 + 2 * 25 + 38, 90 + 5, "NO");
		}
		else if (d == UNHOVER && !unH) {
			hYES = hNO = 0;
			unH = 1;
			//Draw YES
			pWind->SetBrush(ORANGE);
			pWind->DrawRectangle(ButtonX1, ButtonY1, ButtonX2, ButtonY2, FILLED);
			pWind->SetPen(WHITE);
			pWind->DrawString(25 + 34, 97, "YES");
			//Draw NO

			pWind->SetBrush(ORANGE);
			pWind->DrawRectangle(150, 90, 250, 120);
			pWind->SetPen(WHITE);
			pWind->DrawString(100 + 2 * 25 + 38, 90 + 5, "NO");
		}
		d = getAction();
		pWind->UpdateBuffer(); 
	}
}




//void MyWindow::HelloWindow()
//{
//	pWind = new window();
//	pWind->ChangeTitle("");
//	im = new image("images\\Hello.jpg", JPEG);
//	pWind->DrawImage(*im, 0, 0);
//	Sleep(3000);
//}
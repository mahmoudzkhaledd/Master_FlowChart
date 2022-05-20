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
#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "Output.h"
class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
	Output* pOut;
	
public:
	
	Input(window *pW,Output* out);		//Consturctor
	void WaitKeyPress(char &Key);
	bool GetPointClicked(int& x, int& y,bool tlBr) const;//Gets coordinate where user clicks
	bool isInRange(pair <pair<int, int>, pair<int, int>>* p, int x, int y);
	bool CheckValue(Output* pO, string a = "") const;
	double GetValue(Output* pO, string a = "") const;	// Reads a double value from the user 

	string GetString(Output* pO,string T = "") const; //Returns a string entered by the user

	ActionType GetUserAction(image* &hovered); //Reads the user click and maps it to an action

	~Input();
};

#endif
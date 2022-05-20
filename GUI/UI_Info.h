#ifndef UI_INFO_H
#define UI_INFO_H
#include<iostream>
using namespace std;
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\DEFS.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode{};		//Application Mode (design or simulation)
	window *MainWindow {};
	int width {}, height{};	//Window width and height
	int wx {}, wy{};			//Window starting coordinates
	int TlBrHeight {};
	int StBrWdth {};		//Status Bar Width
	int TlBrWdth {};		//Tool Bar Width
	int MnItWdth {};		//Menu Item Width


	color shapesColor {};
	color DrawClr {};		//Drawing color
	color HiClr {};		//Highlighting color
	color MsgClr {};		//Messages color
	color BackgroundColor {};
	color DarkColor {};

	int ASSGN_WDTH {};		//Assignment statement default width
	int ASSGN_HI {};		//Assignment statement default height

	int Start_Width {};
	int Start_Height {};

	int read_width {};
	int read_height {};

	int CondWidth {};
	int CondHeight {};
	

}UI;	//create a single global object UI

struct Point	
{
	int x,y;
	Point(int a=0, int b=0)	//constructor
	{ x=a;	y=b;}
	
};

#endif
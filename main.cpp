#include "ApplicationManager.h"

#include<iostream>
using namespace std;

int main()
{
	ActionType ActType{};
	//Create an object of ApplicationManager
	ApplicationManager AppManager;
	AppManager.SetBuffering(1);
	do   
	{	
		//Step I - Read user input (action)
		ActType = AppManager.GetUserAction();

		//Steps II & III - Create & Exexute the action
		AppManager.ExecuteAction(ActType);
		
		//Step IV - Update the interface
		//AppManager.UpdateInterface();
	}while(1);
	AppManager.SetBuffering(0);

	return 0;
}


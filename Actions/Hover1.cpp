#include "Hover1.h"
#include"Action.h"
#include<iostream>
using namespace std;
void hover::setHover(image* im){
	imHovered = im;
}
void hover::setLastHover(image* im){
	lastHovered = im;
}
void hover::ReadActionParameters() {

}
void hover::HoverImage() {

}
void hover::UnHoverImage() {
	if (imHovered != NULL && lastHovered != NULL) {
		cout << "Unhover " << getName(imHovered->type) << endl;
		string location = "images\\Icons\\" + getName(imHovered->type);
		pManager->getWindow()->DrawImage(location, imHovered->p.first.first, imHovered->p.first.second);
		lastHovered = NULL;
	}
}
string hover::getName(ImageFunction im) {
	switch (im)
	{
	case start:
		return "Start.JPG";
		break;
	case End:
		return "Start.JPG";
		break;
	case read:
		return "Read.JPG";
		break;
	case write:
		return "Read.JPG";
		break;
	case simpleAssign:
		return "Assign.JPG";
		break;
	case Condition:
		return"Condition.jpg";
		break;
	case ConnectorButton:
		return "Connector.JPG";
		break;
	case Exit:
		return "exit.JPG";
		break;
	case Copy:
		return"copy.jpg";
		break;
	case Cut:
		return"cut.jpg";
		break;
	case Paste:
		return"paste.jpg";
		break;
	case Delete:
		return"delete.jpg";
		break;
	case Redo:
		return"redo.jpg";
		break;
	case Undo:
		return"undo.jpg";
		break;
	case DownArrow:
		return"ArrowDown.jpg";
		break;
	case UpArrow:
		return"ArrowUp.jpg";
		break;
	case simulation:
		return"Simulation.jpg";
		break;
	case zoomIn:
		return"ZoomIN.jpg";
		break;
	case zoomOut:
		return"ZoomOut.jpg";
		break;
	case clear:
		return"Clean.jpg";
		break;
	case resize:
		return"Resize.jpg";
		break;
	case designMode:
		return"Simulation\\Design.jpg";
		break;
	case generateCode:
		return"Simulation\\Generate.jpg";
		break;
	case step_by_step:
		return"Simulation\\Step.jpg";
		break;
	case validate:
		return"Simulation\\Validate.jpg";
		break;
	case run:
		return"Simulation\\play.jpg";
		break;
	case editStatement:
		return"edit.jpg";
		break;
	case varAssign:
		return"Assign.jpg";
		break;
	case operatorassignment:
		return"Assign.jpg";
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
		return"save.jpg";
		break;
	case load:
		return"load.jpg";
		break;
	case complexassign:
		return"Complex.jpg";
		break;
	default:
		break;
	}
}
void hover::Execute() {
	if (lastHovered != imHovered) {
		if (lastHovered != NULL) {
			cout << "Unhover " << getName(lastHovered->type) << endl;
			string location = "images\\Icons\\" + getName(lastHovered->type);
			pManager-> getWindow()->DrawImage(location, lastHovered->p.first.first, lastHovered->p.first.second);
		}
		cout << "hover " << getName(imHovered->type) << endl;
		lastHovered = imHovered;
		string loc = "images\\hovered\\" + getName(imHovered->type);
		pManager->getWindow()->DrawImage(loc, imHovered->p.first.first, imHovered->p.first.second);
	}
}
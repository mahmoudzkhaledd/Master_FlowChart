#pragma once
#include"Action.h"
#include"../ApplicationManager.h"
class hover : public Action
{
	image* imHovered = NULL;
	image* lastHovered = NULL;
public:
	void setHover(image* im);
	void setLastHover(image* im);
	void ReadActionParameters();
	void HoverImage();
	void UnHoverImage();
	string getName(ImageFunction im);
	void Execute();
};


#ifndef __WINDOW_OPTION_H_
#define __WINDOW_OPTION_H_

#include "Child.h"

class ParentWindow;

class OptionWindow : public Child{
public :
	OptionWindow();
	~OptionWindow();
	void update(ParentWindow*);
	void render();
private:
	int key[256];
	int frame;	//フレームをカウントする用
};

#endif
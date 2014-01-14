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
	enum packet{ICMP = 0,HTTP=1,TITLE=2};
	packet select;
	int select_num;
	int Nyan[6];
	int NyanBig[6];
	int i;

};

#endif
#ifndef __WINDOW_TITLE_H_
#define __WINDOW_TITLE_H_

#include "Child.h"
#include "PrintPicture.h"

class ParentWindow;

class TitleWindow : public Child{
public:
	TitleWindow();
	~TitleWindow();
	void update(ParentWindow* parent);
	void render();
	int GetHitKeyStateAll_2(int[]);
private:
	int key[256];
	float arrow_y;
	enum STAT {START = 0, OPTION = 1, EXIT = 2};
	STAT select;
	int select_num;
	int Nyan[6];
	int TitleLogo;
	int NyanTitle[6];
	int frame;
	int team;
	int untitti;
	int BGM;
};

#endif
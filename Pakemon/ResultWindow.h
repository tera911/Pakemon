#ifndef __WINDOW_RESULT_H_
#define __WINDOW_RESULT_H_

#include "Child.h"

class ParentWindow;

class ResultWindow : public Child{
public :
	ResultWindow();
	~ResultWindow();
	void update(ParentWindow*);
	void render();
private:
	int key[256];
	int frame;	//フレームをカウントする用
	enum TRY {RETRY = 0, TITLE = 1};
    TRY select;
    int select_num;
    int Nyan[6];
	int score;
	int remainingTime;
	bool goal;
	int length;	//スコアの桁数
	int staffs;
};

#endif
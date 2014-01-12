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
	int frame;	//�t���[�����J�E���g����p
	enum YES {YES = 0, NO = 1};

};

#endif
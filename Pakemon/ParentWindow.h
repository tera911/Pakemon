#ifndef __WINDOW_PARENT_H_
#define __WINDOW_PARENT_H_

class Child;

class ParentWindow{
public:
	enum STAT {TITLE, PLAY, RESULT, OPTION, EXIT};
	ParentWindow();
	~ParentWindow();
	int update();
	void moveTo(STAT);
private:
	Child* mChild;
	STAT nextSequence;

};


#endif
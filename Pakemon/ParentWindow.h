#ifndef __WINDOW_PARENT_H_
#define __WINDOW_PARENT_H_

class Child;

class ParentWindow{
private:
	Child* mChild;
public:
	ParentWindow();
	~ParentWindow();
	void update();
};


#endif
#ifndef __WINDOW_CHILD_
#define __WINDOW_CHILD


class ParentWindow;

class Child{
public:
	virtual ~Child(){}
	virtual void update(ParentWindow*) = 0;
	//virtual void render() = 0;
};

#endif

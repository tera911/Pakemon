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
	void registScore(int score, int time, bool goal);
	int getScore();
	int getRemainingTime();
	bool isGoal();
	int getTITLEBGM();
	int getGAMEBGM();
private:
	Child* mChild;
	STAT nextSequence;
	int score;
	int time;
	bool goal;
	int TITLEBGM;
	int GAMEBGM;
};


#endif
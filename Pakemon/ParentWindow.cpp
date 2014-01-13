#include "ParentWindow.h"
#include "TitleWindow.h"
#include "Nyancat.h"
#include "ResultWindow.h"
#include "OptionWindow.h"

#define SAFE_DELETE(x)	{\
	delete (x);\
	(x) = 0;\
}

ParentWindow::ParentWindow(){
	moveTo(TITLE);
	mChild = new TitleWindow();
	score = 0;
	time = 0;
	goal = false;
}
ParentWindow::~ParentWindow(){

}

	//ŒJ‚è•Ô‚µŽÀs‚³‚ê‚é
int ParentWindow::update(){
	STAT next = nextSequence;
	mChild->update(this);

	if(nextSequence != next){
		switch(nextSequence){
			case TITLE:
				SAFE_DELETE(mChild);
				mChild = new TitleWindow();
			break;
			case PLAY:
				SAFE_DELETE(mChild);
				mChild = new Nyancat();
			break;
			case RESULT:
				SAFE_DELETE(mChild);
				mChild = new ResultWindow();
			break;
			case OPTION:
				SAFE_DELETE(mChild);
				mChild = new OptionWindow();
			break;
			case EXIT:
				return 1;
			break;
		}
	}
	return 0;
}

void ParentWindow::moveTo(STAT stat){
	nextSequence = stat;
}

void ParentWindow::registScore(int score, int time, bool goal){
	this->score = score;
	this->time = time;
	this->goal = goal;
}

int ParentWindow::getScore(){
	return score;
}

int ParentWindow::getRemainingTime(){
	return time;
}

bool ParentWindow::isGoal(){
	return goal;
}
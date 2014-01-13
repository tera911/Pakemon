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
}
ParentWindow::~ParentWindow(){

}

	//�J��Ԃ����s�����
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
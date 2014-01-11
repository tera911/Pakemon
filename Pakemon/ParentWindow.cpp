#include "ParentWindow.h"
#include "TitleWindow.h"


ParentWindow::ParentWindow(){
	moveTo(TITLE);
	mChild = new TitleWindow();
}
ParentWindow::~ParentWindow(){

}

	//�J��Ԃ����s�����
int ParentWindow::update(){
	mChild->update(this);

	switch(nextSequence){
		case TITLE:

		break;
		case PLAY:

		break;
		case RESULT:

		break;
		case OPTION:

		break;
		case EXIT:
			return 1;
		break;
	}
	return 0;
}

void ParentWindow::moveTo(STAT stat){
	nextSequence = stat;
}
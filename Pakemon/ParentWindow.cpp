#include "ParentWindow.h"
#include "TitleWindow.h"


ParentWindow::ParentWindow(){
	mChild = new TitleWindow();
}
ParentWindow::~ParentWindow(){

}

	//�J��Ԃ����s�����
void ParentWindow::update(){
	mChild->update(this);
}

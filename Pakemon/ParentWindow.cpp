#include "ParentWindow.h"
#include "TitleWindow.h"


ParentWindow::ParentWindow(){
	mChild = new TitleWindow();
}
ParentWindow::~ParentWindow(){

}

	//繰り返し実行される
void ParentWindow::update(){
	mChild->update(this);
}

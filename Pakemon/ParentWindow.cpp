#include "ParentWindow.h"
#include "TitleWindow.h"


ParentWindow::ParentWindow(){
	mChild = new TitleWindow();
}
ParentWindow::~ParentWindow(){

}

	//ŒJ‚è•Ô‚µŽÀs‚³‚ê‚é
void ParentWindow::update(){
	mChild->update(this);
}

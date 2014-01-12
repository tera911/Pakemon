#include "ResultWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"

//コンストラクタ
ResultWindow::ResultWindow(){
	ZeroMemory(key, sizeof(int) * 256);
	frame = 0;
}

//アップデータ　親から呼び出される関数
//画面遷移時はこの関数上でparent->moveTo(ParentWindow::STAT);を呼び出す
void ResultWindow::update(ParentWindow* parent){
	if(frame > 10){
		KeyBoardTools::GetHitKeyStateAll_2(key);
	}

	if(key[KEY_INPUT_SPACE] == 1){
		parent->moveTo(ParentWindow::TITLE);
	}
	if(frame < 60){
		frame++;
	}
	render();//描画
}

//描画用処理
void ResultWindow::render(){
	DrawString(200, 200, "MIKAN RESULT", GetColor(255,255,255));
}

//デストラクタ いろいろ開放させたりする
ResultWindow::~ResultWindow(){
	//んぉほお゛お゛っぉぉォォ　らめぇー、わたしかいぃほお゛お゛っうしゃれひゃう＞＜

}
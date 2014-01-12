#include "OptionWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"

//これはコンストラクタでゲソ
//変数の初期化など使いますでゲソ
OptionWindow::OptionWindow(){
	ZeroMemory(key, sizeof(int) * 256);
	frame = 0;
}

//親クラス（スーパクラス）から呼び出される関数でゲソ
//予測される処理は 1/60秒で実行されますでゲソ
//画面遷移などする際はparentWindowに対してmoveToを実行しますでゲソ
//ex. parent->moveTo(ParentWindow::TITLE);		//タイトルに移動するじゃなイカ
void OptionWindow::update(ParentWindow* parent){
	if(frame > 10){
		KeyBoardTools::GetHitKeyStateAll_2(key);
	}

	if(key[KEY_INPUT_SPACE] == 1){
		parent->moveTo(ParentWindow::TITLE);
	}
	if(frame < 60){
		frame++;
	}
	render();
}

//描画用クラスじゃなイカ
//ここに描画などの処理を書くでゲソ
void OptionWindow::render(){
	DrawString(200, 200, "MIKAN OPTION", GetColor(255,255,255));
}

//デストラクタじゃなイカ？
OptionWindow::~OptionWindow(){

}
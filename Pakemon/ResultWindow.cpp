#include "ResultWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>
#include "KeyBoardTools.h"
#include "PrintPicture.h"

//コンストラクタ
ResultWindow::ResultWindow(){
	ZeroMemory(key, sizeof(int) * 256);
	frame = 0;
	score = -1;
	length = 0;
	select = RETRY;
	select_num = 0;
	LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 20, Nyan);
}

//アップデータ　親から呼び出される関数
//画面遷移時はこの関数上でparent->moveTo(ParentWindow::STAT);を呼び出す
void ResultWindow::update(ParentWindow* parent){
	if(frame > 10){
		KeyBoardTools::GetHitKeyStateAll_2(key);
	}
	if(frame < 60){
		frame++;
	}

	//キー処理
	if(key[KEY_INPUT_UP] == 1){
			select_num--;
	}
	if(key[KEY_INPUT_DOWN] == 1){
			select_num++;
	}

	//選択肢処理
	if(select_num < 0){
		select_num = 1;
	}else if(select_num > 1){
		select_num = 0;
	}
	select = static_cast<TRY>(select_num);
	if(key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_RETURN] == 1){
		switch(select){
			case RETRY:
				//リスタート
				parent->moveTo(ParentWindow::PLAY);
			break;
			case TITLE:
				//TITLE
				parent->moveTo(ParentWindow::TITLE);
			break;
		}
	}
	//スコア計算
	if(score == -1){
		score = parent->getScore() + (parent->getRemainingTime() * 100);
		score = score + (parent->isGoal() ? 1000 : 0);	//ゴールなら+1000P
		for(int i = score; i > 0; i = i / 10){
			length++;
		}
	}
	render();//描画
}

//描画用処理
void ResultWindow::render(){
	PrintPicture::instance()->StringDraw("PLAYSCORE",270,100,3);
	PrintPicture::instance()->NumDraw(score, (800 + 28 * (10 - length)) / 2, 170,3);

	PrintPicture::instance()->StringDraw("RETRY",370,400,2);
	PrintPicture::instance()->StringDraw("TITLE",370,440,2);
	switch(select){
			//矢印の場所
		case RETRY:
			DrawGraph(320, 400, Nyan[3], true);
		break;
		case TITLE:
			DrawGraph(320, 440, Nyan[3], true);
		break;
		}
}

//デストラクタ いろいろ開放させたりする
ResultWindow::~ResultWindow(){
	//んぉほお゛お゛っぉぉォォ　らめぇー、わたしかいぃほお゛お゛っうしゃれひゃう＞＜

}
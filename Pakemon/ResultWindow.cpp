    //////////////////////////////////////////////////////
   //////										  ///////
  //////	製作者　卍鈍き俊足のドーベルマン卍	 ///////
 //////											///////
//////////////////////////////////////////////////////
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
	remainingTime = 0;
	goal = false;
	select = RETRY;
	select_num = 0;
	LoadDivGraph("item/Nyan_s.png", 6, 6, 1, 32, 20, Nyan);
	staffs=LoadGraph("item/staffs_oic.png");
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
				parent->moveTo(ParentWindow::OPTION);
			break;
			case TITLE:
				//TITLE
				parent->moveTo(ParentWindow::TITLE);
			break;
		}
	}
	//スコア計算
	if(score == -1){
		goal = parent->isGoal();
		remainingTime = parent->getRemainingTime();
		score = parent->getScore() + (remainingTime * 100);
		score = score + (goal ? 1000 : 0);	//ゴールなら+1000P
		for(int i = score; i > 0; i = i / 10){
			length++;
		}
	}
	render();//描画
}

//描画用処理
void ResultWindow::render(){
	PrintPicture *print = PrintPicture::instance();
	print->StringDraw("PLAYSCORE",270,100,3);
	print->NumDraw(score, (800 + 28 * (10 - length)) / 2, 170,3);
	print->StringDraw("REMAINING TIME",300, 280, 2);
	print->NumDraw(remainingTime, 530, 280, 2);
	DrawGraph(500,400,staffs,true);
	if(!goal){
		PrintPicture::instance()->StringDraw("NYAN IS DEAD!!", 400, 300, 2);
	}
	print->StringDraw("RETRY?",370,400,2);
	print->StringDraw("TITLE",370,440,2);
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
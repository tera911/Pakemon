#include "TitleWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>

	//コンストラクタ
	TitleWindow::TitleWindow(){
		ZeroMemory(key, 256);
		arrow_y = 200;
		select = START;
		select_num = 0;
		//画像読み込み

	}

	//繰り返し実行される
	void TitleWindow::update(ParentWindow* parent){
		//画面切り替えについて書<

		//キー入力
		GetHitKeyStateAll(key);
		if(key[KEY_INPUT_UP] ==1){
			select_num++;
		}else if(key[KEY_INPUT_DOWN] ==1){
			select_num--;
		}else if(key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_RETURN] == 1){
			switch(select){
				case START:
					//スタート
					parent->moveTo(ParentWindow::PLAY);
				break;
				case OPTION:
					//オプション
					parent->moveTo(ParentWindow::OPTION);
				break;
				case EXIT:
					//おしり
					parent->moveTo(ParentWindow::EXIT);
				break;
			}
		}
		if(select_num < 0){
			select_num = 2;
		}else if(select_num > 2){
			select_num = 0;
		}
		select = static_cast<STAT>(select_num);

		//Enter, Spaceが押されたら確定
		
		
		//描画
		render();
	}
	//描画用
	void TitleWindow::render(){
		DrawString(200,200,"みかん",GetColor(255,255,255));
        DrawString( 330 , 420 , "START" , GetColor(255,255,255) );
        DrawString( 330 , 440 , "OPTION" , GetColor(255,255,255) );
        DrawString( 330 , 460 , "EXIT"   , GetColor(255,255,255) );
		switch(select){
			//矢印の場所
		case START:
			DrawString( 300 , 420   , "→"    , GetColor(255,255,255) );
		break;
		case OPTION:
			DrawString( 300 , 440   , "→"    , GetColor(255,255,255) );
		break;
		case EXIT:
			DrawString( 300 , 460   , "→"    , GetColor(255,255,255) );
		break;
		}
	}

	//デストラクタ
	TitleWindow::~TitleWindow(){

	}

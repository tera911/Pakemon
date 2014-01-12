#include "TitleWindow.h"
#include "ParentWindow.h"
#include <DxLib.h>

	//コンストラクタ
	TitleWindow::TitleWindow(){
		ZeroMemory(key, sizeof(int)*256);
		arrow_y = 200;
		select = START;
		select_num = 0;
		//画像読み込み
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 20, Nyan);
		TitleLogo=LoadGraph("titlelogo_oic.png");
		NyanTitle=LoadGraph("title_nyancat_oic.png");

	}

	//繰り返し実行される
	void TitleWindow::update(ParentWindow* parent){
		//画面切り替えについて書<
		//キー入力
		GetHitKeyStateAll_2(key);
		if(key[KEY_INPUT_UP] == 1){
			select_num--;
		}
		if(key[KEY_INPUT_DOWN] == 1){
			select_num++;
		}
		if(key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_RETURN] == 1){
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
		DrawGraph(125,125,TitleLogo,true);
		//DrawString(200,200,"みかん",GetColor(255,255,255));
		PrintPicture::instance()->StringDraw("START",330,420);
        PrintPicture::instance()->StringDraw("OPTION",330,440);
		PrintPicture::instance()->StringDraw("EXIT",330,460);
		switch(select){
			//矢印の場所
		case START:
			DrawGraph(290, 417, Nyan[3], true);
		break;
		case OPTION:
			DrawGraph(290, 437, Nyan[3], true);
		break;
		case EXIT:
			DrawGraph(290, 457, Nyan[3], true);
		break;
		}
	}

int TitleWindow::GetHitKeyStateAll_2(int KeyStateBuf[]){
    char GetHitKeyStateAll_Key[256];
    GetHitKeyStateAll( GetHitKeyStateAll_Key );
    for(int i=0;i<256;i++){
            if(GetHitKeyStateAll_Key[i]==1) KeyStateBuf[i]++;
            else                            KeyStateBuf[i]=0;
    }
    return 0;
}

	//デストラクタ
	TitleWindow::~TitleWindow(){

	}

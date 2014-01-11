#include "Nyancat.h"
#include "GameMap.h"
#include <DxLib.h>
#include <time.h>
#include "PrintPicture.h"
#include "ParentWindow.h"

#define SAFE_DELETE(x)	{\
	delete (x);\
	(x) = 0;\
}

Nyancat::Nyancat(){
		//Nyanの描画
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 20, handle);

		//デフォルトの座標
		nyan_x = 200;
		nyan_y = 0;

		//1フレームごとの移動量
		top = 0;
		left = 0;
		right = 0;

		//ポート番号
		nyan_port = 0;

		fall = true;
		GA = 0;

		//マップの初期化
		nowMap = new GameMap();
	
		//音楽のロード
		sound[0]	=	LoadSoundMem( "nyanVoice\\nyan01.wav" ) ;
		sound[1]	=	LoadSoundMem( "nyanVoice\\nyan02.wav" ) ;
		sound[2]	=	LoadSoundMem( "nyanVoice\\nyan03.wav" ) ;
		sound[3]	=	LoadSoundMem( "nyanVoice\\nyan04.wav" ) ;
		sound[4]	=	LoadSoundMem( "nyanVoice\\nyan05.wav" ) ;
		sound[5]	=	LoadSoundMem( "nyanVoice\\nyan06.wav" ) ;
//		printPic=new PrintPicture();
		score = 0;
		leftflag = false;
		goalFlag = false;
		deadFlag = false;
	}
	void Nyancat::update(ParentWindow* parent){
		if(goalFlag){
			parent->moveTo(ParentWindow::TITLE);
		}
		GetHitKeyStateAll(key);
		if(key[KEY_INPUT_C] == 1){
			jump();
		}
		if(key[KEY_INPUT_LEFT] == 1){
			moveLeft();
		}
		if(key[KEY_INPUT_RIGHT] == 1){
			moveRight();
		}
		render();
	}
	void Nyancat::render(){
		if(nowMap == NULL){
			return;
		}
		nowMap->render();
		nowMap->checkMapHit(this);
		if(left){
			DrawTurnGraph(nyan_x,nyan_y,handle[3],true);
		}
		else
		{
			DrawGraph(nyan_x, nyan_y, handle[3], true);
		}
		
		nyan_x -= left;
		nyan_x += right;
		nyan_y -= top;
		
		
		grabity();
		//nyan_y += map->checkMapHit1(nyan_x, nyan_y, 0, GA);
		nyan_y += GA;
		if(left > 0){
			left -= 0.5;
			
		}
		if(right > 0){
			right -= 0.5;
		}
		if(top > 0){
			onFall();
			top -= 1.0f;
		}else{
			top = 0;
		}
		
		//y座標位置調整
		DrawFormatString(500, 100, 0, "nyan_y = %f", nyan_y);
		//スコア表示
		//DrawFormatString(100, 50, GetColor(255,255,255), "SCORE : %d", score);
		PrintPicture::instance()->NumDraw(score,400,0);
		//自キャラのポート番号表示
		if(nyan_port != 0){
			if(nyan_port==443){
			PrintPicture::instance()->NumDraw(nyan_port,nyan_x+20,nyan_y-10);
			}else{
			PrintPicture::instance()->NumDraw(nyan_port,nyan_x+15,nyan_y-10);
				}
			}
	}
	void Nyancat::jump(){
		if(!fall){
		//	top = 15.0f;
			for(int i=0;i<20;i++){
			top+=1;
			}
			srand((unsigned) time(NULL));
			voice=rand();
			voice%=5;

			/*printfDx("%d",voice);
			voice=GetRand(6);*/
			if(CheckSoundMem(sound[voice])==0){ 
				PlaySoundMem(sound[voice],DX_PLAYTYPE_BACK);
				
			}
		}
		
	}
	void Nyancat::moveDown(){
		nyan_y +=1;
	}
	void Nyancat::moveLeft(){
		left = 3;
		leftflag=true;

	}
	void Nyancat::moveRight(){
		right = 3;
		leftflag=false;
	}
	void Nyancat::grabity(){
		if(fall){
			GA  = 4.9f;
		}else{
			GA = 0 ;
		}
		
	}
	void Nyancat::reset(){
		SAFE_DELETE(nowMap);
		nowMap = new GameMap();
		//デフォルトの座標
		nyan_x = 200;
		nyan_y = 0;

		//1フレームごとの移動量
		top = 0;
		left = 0;
		right = 0;

		//ポート番号
		nyan_port = 0;

				fall = true;
		GA = 0;
		score = 0;
	}
	//ゴール
	void Nyancat::goal(){
		goalFlag = true;
	}
	//自由落下開始
	void Nyancat::onFall(){
		fall = true;
	}
	//自由落下終了
	void Nyancat::offFall(){
		fall = false;
	}
	//接地判定ON
	void Nyancat::onground(){
		ground=true;
	}
	//接地判定OFF
	void Nyancat::offground(){
		ground=false;
	}
	bool Nyancat::isMoveNyan(){
		return (fall);
	}

	//座標修正
	// 0 = 上、 1 = 右、 2 = 下、 3 = 左
	void Nyancat::revisePosition(int direction, int value){
		char test[40];
		wsprintf(test, "%d\n",value);
		OutputDebugString(test);
		switch(direction){
		case 0:
			nyan_y = nyan_y + value;
		break;
		case 1:
			nyan_x = nyan_x + value;
		break;
		case 2:
			nyan_y = nyan_y - value;
		break;
		case 3:
			nyan_x = nyan_x - value;
		break;
		}
	}
	//ニャンがいるX座標を取得
	float Nyancat::getNyanX(){
		return nyan_x;
	}
	//ニャンがいるY座標を取得
	float Nyancat::getNyanY(){
		return nyan_y;
	}

	//スコアを加算する
	void Nyancat::sumScore(int value){
		score = score + value;
	}

	//自キャラのポート番号を変更
	void Nyancat::changePortNumber(int port){
		nyan_port = port;
	}
	Nyancat::~Nyancat(){
		SAFE_DELETE(nowMap);
	}
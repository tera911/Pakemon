#include "Nyancat.h"

Nyancat::Nyancat(){
		LoadDivGraph("Nyan_s.png", 6, 6, 1, 32, 20, handle);
		nyan_x = 200;
		nyan_y = 0;
		top = 0;
		left = 0;
		right = 0;
		fall = true;
		GA = 0;
		map = new GameMap();
		
		sound[0]=LoadSoundMem( "nyanVoice\\nyan01.wav" ) ;
		sound[1]=LoadSoundMem( "nyanVoice\\nyan02.wav" ) ;
		sound[2]=LoadSoundMem( "nyanVoice\\nyan03.wav" ) ;
		sound[3]=LoadSoundMem( "nyanVoice\\nyan04.wav" ) ;
		sound[4]=LoadSoundMem( "nyanVoice\\nyan05.wav" ) ;
		sound[5]=LoadSoundMem( "nyanVoice\\nyan06.wav" ) ;

	}

	void Nyancat::render(){
		if(map == NULL){
			return;
		}
		map->render();
		map->checkMapHit(this);
		DrawGraph(nyan_x, nyan_y, handle[3], true);
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
		//nyan_y = floor(nyan_y / 32) * 32 + 10;
		DrawFormatString(500, 100, 0, "nyan_y = %f", nyan_y);
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
	}
	void Nyancat::moveRight(){
		right = 3;
	}
	void Nyancat::grabity(){
		if(fall){
			GA  = 4.9f;
		}else{
			GA = 0 ;
		}
		
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
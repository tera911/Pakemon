#include "GameMap.h"
#include "Nyancat.h"

int GameMap::checkMapHit(Nyancat* nyan){
		float nyan_x = nyan->getNyanX();
		float nyan_y = nyan->getNyanY();
		int tb[2], bb[2], cb[2],lb[2], rb[2];		//上、下、中央、左、右ブロック [x,y] 

		//ブロックにめり込むのを防ぐ
		cb[0] = round(nyan_x / 32.0f);	//自キャラのX座標
		cb[1] = round(nyan_y / 32.0f);	//自キャラのY座標

		tb[0] = cb[0];		//自キャラの上ブロックの座標
		tb[1] = cb[1] -1;	//自キャラの上ブロックの座標
		
		bb[0] = cb[0];		//自キャラの上ブロックの座標
		bb[1] = cb[1] +1;	//自キャラの上ブロックの座標
		DrawFormatString(600,70, GetColor(0,0,0), "x = %d",cb[0]);
		DrawFormatString(600,90, GetColor(0,0,0), "y = %d",cb[1]);
		
		//キャラクターがマップブロックから飛び出た場合
		//上に飛び出てるか
		if(cb[1] * 32 > nyan_y){
			if(map[tb[0]][tb[1]] == 'A' || map[tb[0]][tb[1]] == 'S' || map[tb[0]][tb[1]] == 'I'){
				nyan->revisePosition(2, nyan_y - cb[1] * 32);	//位置修正
			}
		}
		//下方向に飛び出た場合
		if(cb[1] * 32 + 11 < nyan_y){	//本当は cb[1] * 32 + 32 < nyan_y + 32だけど高速化のため ;キャラクタのサイズが20のため + 12
			DrawFormatString(600,120, GetColor(0,0,0), "抜けでたぁ！");
			if(map[bb[0]][bb[1]] == 'A' || map[bb[0]][bb[1]] == 'S' || map[bb[0]][bb[1]] == 'I'){
				nyan->revisePosition(0, (cb[1] * 32 + 12) - nyan_y);	//位置修正
				nyan->offFall();
				nyan->onground();
			}else{
				nyan->onFall();
				nyan->offground();
			}
		}
		
		//自キャラがブロックにめり込んだ場合　
		/*if(map[cb[0]][cb[1]] == 'A' || map[cb[0]][cb[1]] == 'S' || map[cb[0]][cb[1]] == 'I'){
			float block_pos[2];
			block_pos[0] = cb[0] * 32 + 16;	//ブロックの中心座標 x
			block_pos[1] = cb[1] * 32 + 16;	//ブロックの中心座標 y
		
			if(block_pos[1] > nyan_y){
				nyan->revisePosition(0, block_pos[1] - nyan_y);
			}else if(block_pos[1] < nyan_y){
				nyan->revisePosition(2, nyan_y - block_pos[1]);
			}else if(block_pos[0] > nyan_x){
				nyan->revisePosition(3, block_pos[0] - nyan_x);
			}else if(block_pos[0] < nyan_x){
				nyan->revisePosition(1, nyan_x - block_pos[0]);
			}
		}
		*/

		//まずは上から
		if(map[tb[0]][tb[1]] == 'A' || map[tb[0]][tb[1]] == 'S' || map[tb[0]][tb[1]] == 'I'){
		//	nyan->revisePosition(0, nyan_y - tb[1] * 32);
		}

		int block_x = (nyan_x / 32) + 1;
		int block_y = (nyan_y / 32) + 1;
		DrawBox(cb[0] * 32, cb[1] * 32, (cb[0] * 32) + 32,(cb[1] * 32) +  32, GetColor(255,0,0), true);
		if(map[cb[0]][cb[1]] != 0){
			DrawString(500, 100, "接触", GetColor(255,255,255));
		}
		return 0;
	}
int GameMap::checkMapHit1(float nyan_x, float nyan_y, int direction, float value){
		int tb[2], bb[2], cb[2],lb[2], rb[2];		//上、下、中央、左、右ブロック [x,y] 
		cb[0] = round(nyan_x / 32.0f);	//自キャラのX座標
		cb[1] = round(nyan_y / 32.0f);	//自キャラのY座標
		
		tb[0] = cb[0];		//自キャラの上ブロックの座標
		tb[1] = cb[1] -1;	//自キャラの上ブロックの座標
		
		bb[0] = cb[0];		//自キャラの上ブロックの座標
		bb[1] = cb[1] +1;	//自キャラの上ブロックの座標

		switch(direction){
		case 0:
			//上
			if(map[tb[0]][tb[1]] == 'A' || map[tb[0]][tb[1]] == 'S' || map[tb[0]][tb[1]] == 'I'){
					int next_value = nyan_y - cb[1] * 32;
					if(next_value > value){
						return next_value;
					}else{
						return value;
					}
				}
		break;
		}
		return value;
	}
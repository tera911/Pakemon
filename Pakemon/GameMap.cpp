#include "GameMap.h"
#include "Nyancat.h"

void GameMap::render(){
	for(int x = 0; x < MAP_WIDTH; x++){
		for(int y = 0; y < MAP_HEIGHT; y++){
			render_block(map[x][y], x, y);		
		}
	}
	screenScroll_x(0.005f);
}
void GameMap::render_block(int block_type, int x, int y){
	if(block_type == 0){
		//return;
	}
	int block_x, block_y;
	block_x =  x * 32 - screen_x * 32;
	block_y  = y * 32;
	switch(block_type){
		case 'A':
			DrawGraph(block_x, block_y, block_brick, true);
		break;
		case 'S':
			DrawGraph(block_x, block_y, block_ware, true);
		break;
		case 'I':
			DrawGraph(block_x, block_y, block_hatena, true);
		break;
		case 'C':
			DrawGraph(block_x, block_y, block_packet, true);
		break;
		case 'N':
			DrawGraph(block_x, block_y, block_normal, true);
		break;
		default:
			DrawString(block_x + 16, block_y + 16, "1", GetColor(255,255,255));
			return;
		break;
	}
}

int GameMap::checkMapHit(Nyancat* nyan){
		float nyan_x = nyan->getNyanX();
		float nyan_y = nyan->getNyanY();
		int tb[2], bb[2], cb[2],lb[2], rb[2];		//上、下、中央、左、右ブロック [x,y] 

		//ブロックにめり込むのを防ぐ
		cb[0] = round((nyan_x + screen_x * 32) / 32.0f);	//自キャラのX座標
		cb[1] = round((nyan_y) / 32.0f);	//自キャラのY座標

		tb[0] = cb[0];		//自キャラの上ブロックのx座標
		tb[1] = cb[1] -1;	//自キャラの上ブロックのy座標
		
		bb[0] = cb[0];		//自キャラの上ブロックのx座標
		bb[1] = cb[1] +1;	//自キャラの上ブロックのy座標

		lb[0] = cb[0] -1;	//自キャラの左ブロックのx座標
		lb[1] = cb[1];		//自キャラの左ブロックのy座標

		rb[0] = cb[0] + 1;	//自キャラの左ブロックのx座標
		rb[1] = cb[1];		//自キャラの左ブロックのy座標

		DrawFormatString(600,70, GetColor(0,0,0), "x = %d",cb[0]);
		DrawFormatString(600,90, GetColor(0,0,0), "y = %d",cb[1]);
		
		//キャラクターがマップブロックから飛び出た場合

		//上に飛び出てるか
		if(cb[1] * 32 > nyan_y){
			if(map[tb[0]][tb[1]] == 'A' || map[tb[0]][tb[1]] == 'S' || map[tb[0]][tb[1]] == 'I' || map[tb[0]][tb[1]] == 'N'){
				nyan->revisePosition(2, nyan_y - cb[1] * 32);	//位置修正
			}
			if(map[tb[0]][tb[1]] == 'I'){
				map[tb[0]][tb[1]] = 'N';
			}
		}
		//下方向に飛び出た場合
		if(cb[1] * 32 + 11 < nyan_y){	//本当は cb[1] * 32 + 32 < nyan_y + 32だけど高速化のため ;キャラクタのサイズが20のため + 12
			if(map[bb[0]][bb[1]] == 'A' || map[bb[0]][bb[1]] == 'S' || map[bb[0]][bb[1]] == 'I' || map[bb[0]][bb[1]] == 'N'){
				nyan->revisePosition(0, (cb[1] * 32 + 12) - nyan_y);	//位置修正
				nyan->offFall();
				nyan->onground();
			}else{
				nyan->onFall();
				nyan->offground();
			}
		}
		//左に飛び出た
		if(cb[0] * 32 > (nyan_x + screen_x * 32)){
			if(map[lb[0]][lb[1]] == 'A' || map[lb[0]][lb[1]] == 'S' || map[lb[0]][lb[1]] == 'I' || map[lb[0]][lb[1]] == 'N'){
				nyan->revisePosition(1, cb[0] * 32 - (nyan_x + screen_x * 32));	//位置修正
			}
		}
		//右に飛び出た
		if(cb[0] * 32 < (nyan_x + screen_x * 32)){
			if(map[rb[0]][rb[1]] == 'A' || map[rb[0]][rb[1]] == 'S' || map[rb[0]][rb[1]] == 'I' || map[rb[0]][rb[1]] == 'N'){
				nyan->revisePosition(3, (nyan_x + screen_x * 32) - cb[0] * 32);	//位置修正
			}
		}
		//自キャラがブロックにめり込んだ場合　
		if(map[cb[0]][cb[1]] == 'A' || map[cb[0]][cb[1]] == 'S' || map[cb[0]][cb[1]] == 'I' || map[cb[0]][cb[1]] == 'N'){
			float block_pos[2];
			block_pos[0] = cb[0] * 32 + 16;	//ブロックの中心座標 x
			block_pos[1] = cb[1] * 32 + 20;	//ブロックの中心座標 y
		
			if(block_pos[1] > nyan_y + 32){
				nyan->revisePosition(0, block_pos[1] - (nyan_y + 32));
			}else if(block_pos[1] < nyan_y){
				nyan->revisePosition(2, nyan_y - block_pos[1]);
			}else if(block_pos[0] > (nyan_x + screen_x * 32)){
				nyan->revisePosition(3, block_pos[0] - (nyan_x + screen_x * 32));
			}else if(block_pos[0] < (nyan_x + 32 + screen_x * 32)){
				nyan->revisePosition(1, (nyan_x + 32 + screen_x * 32) - block_pos[0]);
			}
		}

		//自キャラがパケットを取得した場合
		if(map[cb[0]][cb[1]] == 'C'){
			map[cb[0]][cb[1]] = 0;	//パケット消える
		}
		
		if(cb[1] > 18){
			nyan->offFall();
			nyan->onground();
		}

		int block_x = ((nyan_x + screen_x * 32) / 32) + 1;
		int block_y = (nyan_y / 32) + 1;

		DrawBox(cb[0] * 32 - screen_x * 32,
			cb[1] * 32, 
			(cb[0] * 32 - screen_x * 32) + 32, 
			(cb[1] * 32) +  32, 
			GetColor(255,0,0), 
			true);

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
void GameMap::screenScroll_x(float value){
	screen_x = screen_x + value;
}

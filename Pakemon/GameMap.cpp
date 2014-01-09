#include "GameMap.h"
#include "Nyancat.h"

#define __DEBUG_	//デバッグ時のみ

GameMap::GameMap(){
		screen_x = 0;
		screen_center_x = 12.0f * 32;
		block_brick		= LoadGraph("./block/brick.png", true);
		block_hatena	= LoadGraph("./block/hatena.png", true);
		block_normal	= LoadGraph("./block/normal.png", true);
		block_packet	= LoadGraph("./block/packet.png", true);
		block_ware		= LoadGraph("./block/ware.png", true);
		MapBuilder builder;
		builder.getMap(map);

	}
void GameMap::render(){
	for(int x = 0; x < MAP_WIDTH; x++){
		for(int y = 0; y < MAP_HEIGHT; y++){
			render_block(map[x][y], x, y);		
		}
	}
	//screenScroll_x(0.015f);
}
void GameMap::render_block(int block_type, int x, int y){
	if(block_type == 0){
		//return;
	}
	int block_x, block_y;
	block_x =  x * 32 - screen_x * 32;
	block_y  = y * 32;
	switch(block_type){
		case ASHIBA:
			DrawGraph(block_x, block_y, block_brick, true);
		break;
		case SHOGAI:
			DrawGraph(block_x, block_y, block_ware, true);
		break;
		case ITEM:
			DrawGraph(block_x, block_y, block_hatena, true);
		break;
		case COIN_FTP:
			DrawGraph(block_x, block_y, block_packet, true);
			DrawString(block_x + 5, block_y + 10, "21", GetColor(255,255,255));
		break;
		case COIN_SSH:
			DrawGraph(block_x, block_y, block_packet, true);
			DrawString(block_x + 5, block_y + 10, "22", GetColor(255,255,255));
		break;
		case COIN_SMTP:
			DrawGraph(block_x, block_y, block_packet, true);
			DrawString(block_x + 5, block_y + 10, "25", GetColor(255,255,255));
		break;
		case COIN_DNS:
			DrawGraph(block_x, block_y, block_packet, true);
			DrawString(block_x + 5, block_y + 10, "53", GetColor(255,255,255));
		break;
		case COIN_HTTP:
			DrawGraph(block_x, block_y, block_packet, true);
			DrawString(block_x + 5, block_y + 10, "80", GetColor(255,255,255));
		break;
		case COIN_HTTPS:
			DrawGraph(block_x, block_y, block_packet, true);
			DrawString(block_x , block_y + 10, "443", GetColor(255,255,255));
		break;
		case ITEM_NORMAL:
			DrawGraph(block_x, block_y, block_normal, true);
		break;
		default:
#ifdef __DEBUG_
			DrawString(block_x + 16, block_y + 16, "1", GetColor(255,255,255));
			DrawFormatString(100, 90, GetColor(255,255,255), "screen_x = %f",screen_x);
#endif
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
#ifdef __DEBUG_
		DrawFormatString(600,70, GetColor(0,0,0), "x = %d",cb[0]);
		DrawFormatString(600,90, GetColor(0,0,0), "y = %d",cb[1]);
#endif
		
		//キャラクターがマップブロックから飛び出た場合

		//上に飛び出てるか
		if(cb[1] * 32 > nyan_y){
			if(map[tb[0]][tb[1]] & ASHIBA || map[tb[0]][tb[1]] & SHOGAI || map[tb[0]][tb[1]] & ITEM || map[tb[0]][tb[1]] & ITEM_NORMAL){
				nyan->revisePosition(2, nyan_y - cb[1] * 32);	//位置修正
			}
			if(map[tb[0]][tb[1]] & ITEM){
				map[tb[0]][tb[1]] = ITEM_NORMAL;
			}
		}
		//下方向に飛び出た場合
		if(cb[1] * 32 + 11 < nyan_y){	//本当は cb[1] * 32 + 32 < nyan_y + 32だけど高速化のため ;キャラクタのサイズが20のため + 12
			if(map[bb[0]][bb[1]] & ASHIBA || map[bb[0]][bb[1]] & SHOGAI || map[bb[0]][bb[1]] & ITEM || map[bb[0]][bb[1]] & ITEM_NORMAL){
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
			if(map[lb[0]][lb[1]] & ASHIBA || map[lb[0]][lb[1]] & SHOGAI || map[lb[0]][lb[1]] & ITEM || map[lb[0]][lb[1]] & ITEM_NORMAL){
				nyan->revisePosition(1, cb[0] * 32 - (nyan_x + screen_x * 32));	//位置修正
			}
		}
		//右に飛び出た
		if(cb[0] * 32 < (nyan_x + screen_x * 32)){
			if(map[rb[0]][rb[1]] & ASHIBA || map[rb[0]][rb[1]] & SHOGAI || map[rb[0]][rb[1]] & ITEM || map[rb[0]][rb[1]] & ITEM_NORMAL){
				nyan->revisePosition(3, (nyan_x + screen_x * 32) - cb[0] * 32);	//位置修正
			}
		}
		//自キャラがブロックにめり込んだ場合　
		if(map[cb[0]][cb[1]] & ASHIBA || map[cb[0]][cb[1]] & SHOGAI || map[cb[0]][cb[1]] & ITEM || map[cb[0]][cb[1]] & ITEM_NORMAL){
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
		if(map[cb[0]][cb[1]] & COIN_ALL){
			nyan->sumScore(50);	//スコア加算

			//自キャラのポート番号変更
			int block = map[cb[0]][cb[1]];
			if(block & COIN_FTP){
				nyan->changePortNumber(21);
			}else if(block & COIN_SSH){
				nyan->changePortNumber(22);
			}else if(block & COIN_SMTP){
				nyan->changePortNumber(25);
			}else if(block & COIN_DNS){
				nyan->changePortNumber(53);
			}else if(block & COIN_HTTP){
				nyan->changePortNumber(80);
			}else if(block & COIN_HTTPS){
				nyan->changePortNumber(443);
			}
			map[cb[0]][cb[1]] = 0;	//パケット消える
		}
		
		if(cb[1] > 18){
			nyan->offFall();
			nyan->onground();
		}

		

		//にゃんキャットと画面のスクロールを連動
		if(nyan_x > screen_center_x){
			int xdiff = nyan_x - screen_center_x;
			screen_x = screen_x + xdiff / 32.0f;
			if(xdiff > 0){
				nyan->revisePosition(3, xdiff);	
			}
		}

		/*DrawBox(cb[0] * 32 - screen_x * 32,
			cb[1] * 32, 
			(cb[0] * 32 - screen_x * 32) + 32, 
			(cb[1] * 32) +  32, 
			GetColor(255,0,0), 
			true);*/
#ifdef __DEBUG_
		if(map[cb[0]][cb[1]] != 0){
			DrawString(500, 100, "接触", GetColor(255,255,255));
		}
#endif
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

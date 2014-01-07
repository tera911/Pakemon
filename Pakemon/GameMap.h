#ifndef __GAME_MAP
#define __GAME_MAP

#include "packet/MapBuilder.h"
#include <math.h>
#include <DxLib.h>
#define MAP_WIDTH		(46)
#define	MAP_HEIGHT		(18)
#define round(fp) (int)((fp) >= 0 ? (fp) + 0.5 : - 0.5)

class Nyancat;

class GameMap{
private:
	float screen_x;
	int block_brick;
	int block_hatena;
	int block_normal;
	int block_packet;
	int block_ware;
public:
	char map[46][18];
	GameMap(){
		screen_x = 0;
		block_brick		= LoadGraph("./block/brick.png", true);
		block_hatena	= LoadGraph("./block/hatena.png", true);
		block_normal	= LoadGraph("./block/normal.png", true);
		block_packet	= LoadGraph("./block/packet.png", true);
		block_ware		= LoadGraph("./block/ware.png", true);
		MapBuilder builder;
		builder.getMap(map);

	}
	void render(){
		int i, j;
		for(i = 0; i < MAP_WIDTH; i++){
			for(j = 0; j < MAP_HEIGHT; j++){
				render_block(map[i][j], i, j);		
			}
		}
	}
	void render_block(int block_type, int x, int y){
		if(block_type == 0){
			//return;
		}
		int block_x, block_y;
		block_x =  x * 32 - screen_x * 4;
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
			default:
				DrawString(block_x + 16, block_y + 16, "1", GetColor(255,255,255));
				return;
			break;
		}
	}
	//自キャラX、自キャラY、　方向、　移動させたい距離
	int checkMapHit1(float nyan_x, float nyan_y, int direction, float value){
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

	int checkMapHit(Nyancat* nyan);
	void screenScroll_x(int value);
};

#endif

#ifndef GAME_MAP
#define GAME_MAP

#include <math.h>
#include <DxLib.h>

#define MAP_WIDTH		(46)
#define	MAP_HEIGHT		(18)
#define round(fp) (int)((fp) >= 0 ? (fp) + 0.5 : - 0.5)

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
	int checkMapHit(Nyancat *nyan){
		float nyan_x = nyan->getNyanX();
		float nyan_y = nyan->getNyanY();
		int tb[2], bb[2], cb[2],lb[2], rb[2];		//上、下、中央、左、右ブロック [x,y] 

		cb[0] = round(nyan_x / 32.0f);
		cb[1] = round(nyan_y / 32.0f);

		//まずは上から

		//下にブロックがあった場合
		if(map[cb[0]][cb[1]+1] == 'A'){
			nyan->offFall();
			nyan->onground();
			
		}else{
			nyan->onFall();
			nyan->offground();
		}

		int block_x = (nyan_x / 32) + 1;
		int block_y = (nyan_y / 32) + 1;
		DrawBox(cb[0] * 32, cb[1] * 32, (cb[0] * 32) + 32,(cb[1] * 32) +  32, GetColor(255,0,0), true);
		if(map[cb[0]][cb[1]] != 0){
			DrawString(500, 100, "接触", GetColor(255,255,255));
		}
		return 0;
	}
	void screenScroll_x(int value);
};

#endif

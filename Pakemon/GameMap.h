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
	int block_brick;
	int block_hatena;
	int block_normal;
	int block_packet;
	int block_ware;
	enum BLOCK {AIR = 0 ,ASHIBA = 0x2 ,SHOGAI = 0x4 ,ITEM = 0x8, ITEM_NORMAL = 0x10 ,SWITCH = 0x20, ROUTER = 0x40 , COIN = 0x80};	
public:
	int map[46][18];
	float screen_x;
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
	void render();
	void render_block(int block_type, int x, int y);
	//自キャラX、自キャラY、　方向、　移動させたい距離
	int checkMapHit1(float nyan_x, float nyan_y, int direction, float value);

	int checkMapHit(Nyancat* nyan);
	void screenScroll_x(float value);
};

#endif

#ifndef __GAME_MAP
#define __GAME_MAP

#include "packet/MapBuilder.h"
#include <math.h>
#include <DxLib.h>
#include <list>
#define MAP_WIDTH		(35)
#define	MAP_HEIGHT		(18)
#define SCREEN_WIDTH	(25)
#define round(fp) (int)((fp) >= 0 ? (fp) + 0.5 : - 0.5)

class Nyancat;

class GameMap{
private:
	enum BLOCK {AIR = 0 ,ASHIBA = 0x2 ,SHOGAI = 0x4 ,ITEM = 0x8, ITEM_NORMAL = 0x10 ,SWITCH = 0x20, ROUTER = 0x40 , 
				COIN_FTP = 0x80, COIN_SSH = 0x100, COIN_SMTP = 0x200, COIN_DNS = 0x400, COIN_HTTP = 0x800, COIN_HTTPS = 0x1000, COIN_ALL = 0x1F80, 
				ROUTER_FLAG = 0x2008, SWITCH_FLAG = 0x4008, /**
															ringo
															*/
															ALL_HIT_BLOCK = 0x1E};

	struct Effect{
		int blocktype;
		Nyancat* nyan;
		float sx,sy;
		float alpha;
	};
	int block_brick;
	int block_hatena;
	int block_normal;
	int block_packet;
	int block_ware;
	int block_router;
	int block_switch;
	float screen_center_x;
	float move_screen;
		std::list<struct Effect> effectList;
public:
	int map[MAP_WIDTH * 6 + 10][MAP_HEIGHT];
	float screen_x;
	GameMap();
	void render();
	void render_block(int block_type, int x, int y);
	//自キャラX、自キャラY、　方向、　移動させたい距離
	int checkMapHit1(float nyan_x, float nyan_y, int direction, float value);

	int checkMapHit(Nyancat* nyan);
	void screenScroll_x(float value);
	void Animation();
	void addAnimation(Effect *effect);
};

#endif

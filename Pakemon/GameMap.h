#ifndef __GAME_MAP
#define __GAME_MAP

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
				ROUTER_FLAG = 0x2008, SWITCH_FLAG = 0x4008,BLOCK_FW = 0x8000, BLOCK_FIRE = 0x8001, ALL_HIT_BLOCK = 0x1E, DROPITEM = 0x60};

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
	int	block_fire32;
	int	block_fire64;
	float screen_center_x;
	float move_screen;
	std::list<struct Effect> effectList;
	int segment;	
public:
	int map[MAP_WIDTH * 6 + 10][MAP_HEIGHT];
	float screen_x;
	GameMap(int);
	void render();
	void render_block(int block_type, int x, int y);
	void render_fw(int block_type, int x, int y);
	int clear_fw(Nyancat*, int x, int y);
	int checkMapHit(Nyancat* nyan);
	void screenScroll_x(float value);
	void Animation();
	void addAnimation(Effect *effect);
	void nextSegment(Nyancat*);		//move to the next Segment!!!!!!!!!!
	void switchAction(Nyancat*);	//スクリーンに映ってるパけっとを取得するん？
	int Digit(int digit);
};
#endif
